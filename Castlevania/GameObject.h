#pragma once
#include "Game.h"
#include "AnimationManager.h"
#include "TextureManager.h"
#include "Box.h"
#include "SweptAABB.h"
using namespace std;

#define FACE_TO_RIGHT 1
#define FACE_TO_LEFT -1

struct CollisionEvent;
typedef CollisionEvent* LPCollisionEvent;
class GameObject;
typedef GameObject* LPGameObject;

class GameObject
{
protected:
	float x;
	float y;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	float vx;
	float vy;
	DWORD dt;

	FaceSide faceSide;

	int currentState;
	int previousState;
	static unordered_map<int, Animation*> animations;

	LPDIRECT3DTEXTURE9 texture;

public:
	GameObject() {
		x = y = 0;
		vx = vy = 0;
		faceSide = FaceSide::right; // right side
	}
	~GameObject();

	void setPosition(float x, float y) { this->x = x; this->y = y; }
	void setState(int state) { this->previousState = this->currentState; this->currentState = state; }
	void setSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	int getPreviousState() { return previousState; }
	int getState() { return currentState; }
	void getSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void getPosition(float &x, float &y) {
		x = this->x;
		y = this->y;
	}

	void RenderBoundingBox();

	static void addAnimation(int animationId);

	LPCollisionEvent sweptAABBEx(LPGameObject collisionObject);
	void calcPotentialCollisions(vector<LPGameObject> *coObjects, vector<LPCollisionEvent> & coEvents);
	void filterCollision(
		vector<LPCollisionEvent> &coEvents,
		vector<LPCollisionEvent> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	virtual void update(DWORD dt, vector<GameObject*> *coObjects = NULL);

	virtual void render() = 0;
	virtual Box getBoundingBox() = 0;
};

struct CollisionEvent
{
	GameObject* obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGameObject obj = NULL)
	{
		this->t = t; this->nx = nx; this->ny = ny; this->obj = obj;
	}

	static bool compare(const LPCollisionEvent &a, LPCollisionEvent &b)
	{
		return a->t < b->t;
	}
};