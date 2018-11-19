#include "GameObject.h"
#include <algorithm>

unordered_map<int, Animation* > GameObject::animations;

GameObject::~GameObject()
{
	if (texture != nullptr) texture->Release();
}


void GameObject::renderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	auto texture = TextureManager::getInstance()->get(ID_TEX_BBOX);
	auto game = Game::getInstance();

	float l, t, r, b;
	getBoundingBox(l, t, r, b);

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b- (int)t;

	game->draw(l,t, texture, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void GameObject::addAnimation(int animationId)
{
	auto animation = AnimationManager::getInstance()->get(animationId);
	animations[animationId] = animation;
}


LPCollisionEvent GameObject::sweptAABBEx(LPGameObject coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->getBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->getSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	getBoundingBox(ml, mt, mr, mb);

	sweptAABB(
		ml, mt, mr, mb,
		sl, st, sr, sb,
		dx, dy,
		t, nx, ny
	);

	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
	return e;;

}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
	void GameObject::calcPotentialCollisions
(vector<LPGameObject>* coObjects, vector<LPCollisionEvent>& coEvents)
{
	for (auto& coObject : *coObjects)
	{
		LPCollisionEvent e = sweptAABBEx(coObject);

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void GameObject::filterCollision
(vector<LPCollisionEvent>& coEvents,
	vector<LPCollisionEvent>& coEventsResult,
	float & min_tx, float & min_ty, float & nx, float & ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		auto c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void GameObject::update(const DWORD dt, vector<GameObject*> *coObject)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}