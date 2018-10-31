#include "SweptAABB.h"
#include "debug.h"

bool isColliding(const Box& object, const Box& other)
{
	auto left = object.right < other.left;
	auto top = object.left > other.right;
	auto right = object.bottom < other.top;
	auto bottom = object.top > other.bottom;

	return !(left||top||right||bottom);
}

Box getSweptBroadphaseRect(const Box& movingObject,float dx,float dy)
{
	float left = dx > 0 ? movingObject.left : movingObject.left + dx;
	float top = dy > 0 ? movingObject.top : movingObject.top + dy;
	float right = dx > 0 ? movingObject.right+ dx : movingObject.right;
	float bottom = dy > 0 ? movingObject.bottom + dy : movingObject.bottom;
	
	return Box(left,top,right,bottom);
}

void findDistance(float& dxEntry, float& dyEntry,
	float& dxExit, float& dyExit,
	float dx, float dy,
	Box movingObject,
	Box standingObject)
{
	auto ml = movingObject.left, mt = movingObject.top, mr = movingObject.right, mb = movingObject.bottom;
	auto sl = standingObject.left, st = standingObject.top, sr = standingObject.right, sb = standingObject.bottom;

	if (dx > 0)
	{
		dxEntry = sl - mr;
		dxExit = sr - ml;
	}
	else if (dx < 0)
	{
		dxEntry = sr - ml;
		dxExit = sl - mr;
	}


	if (dy > 0)
	{
		dyEntry = st - mb;
		dyExit = sb - mt;
	}
	else if (dy < 0)
	{
		dyEntry = sb - mt;
		dyExit = st - mb;
	}
}

void findCollisonAndExittime(float& txEntry, float& tyEntry,
	float& txExit, float& tyExit,
	float dxEntry, float dxExit,
	float dyEntry, float dyExit,
	float dx, float dy
)
{
	if (dx == 0)
	{
		txEntry = -99999999999;
		txExit = 99999999999;
	}
	else
	{
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0)
	{
		tyEntry = -99999999999;
		tyExit = 99999999999;
	}
	else
	{
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

}

void sweptAABB(
	Box movingObject, Box standingObject,
	float dx, float dy,
	float &t, float &nx, float &ny)
{
	auto ml = movingObject.left, mt = movingObject.top, mr = movingObject.right, mb = movingObject.bottom;
	auto sl = standingObject.left, st = standingObject.top, sr = standingObject.right, sb = standingObject.bottom;

	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;

	float entryTime;
	float exitTime;

	t = -1.0f;			// no collision
	nx = ny = 0;
	// Broad-phase test
	Box broadPhase = getSweptBroadphaseRect(movingObject, dx, dy);
	if (!isColliding(broadPhase, standingObject)) return;

	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	findDistance(dxEntry, dyEntry, dxExit, dyExit, dx,dy,movingObject, standingObject);
	findCollisonAndExittime(txEntry, tyEntry, txExit, tyExit, dxEntry, dxExit, dyEntry, dyExit, dx, dy);

	if ((txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return;

	// get final entry time and exit time
	entryTime = std::max(txEntry, tyEntry);
	exitTime = std::min(txExit, tyExit);

	bool notCollision = (entryTime > exitTime
		|| (txEntry < 0.0f && tyEntry < 0.0f)
		|| txEntry > 1.0f
		|| tyEntry > 1.0f
		);
	if (notCollision) return ;

	// time collison = entry time
	t = entryTime;

	// find direction result
	if (txEntry > tyEntry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}