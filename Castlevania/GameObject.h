#pragma once
#include "Game.h"
#include "AnimationManager.h"
#include "TextureManager.h"
#include "SweptAABB.h"
using namespace std;

constexpr auto FACE_TO_RIGHT = 1;
constexpr auto FACE_TO_LEFT = -1;

struct CollisionEvent;
typedef CollisionEvent* LPCollisionEvent;
class GameObject;
typedef GameObject* LPGameObject;

class GameObject
{
protected:
	int id;
	int type;

	float x;
	float y;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	float vx;
	float vy;
	float boundingGameX; // gioi han man hinh game x
	float boundingGameY; // gioi han man hinh game y
	DWORD dt;
	int animationId;

	int faceSide;

	int currentState;
	int previousState;
	unordered_map<int, Animation*> animations;
	int previousAmiId;
	bool previousAnimIsOneTimeAnim;

	LPDIRECT3DTEXTURE9 texture;

public:
	GameObject();

	virtual ~GameObject();

	virtual void initAnim()=0;
	void setType(int type) { this->type = type; }
	void setId(int id) { this->id = id; }
	void setPosition(float x, float y) { this->x = x; this->y = y; }
	void setState(int state) { this->previousState = this->currentState; this->currentState = state; }
	void setSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void setBoundingGame(float x, float y) { this->boundingGameX = x; this->boundingGameY = y; }

	int getId() const { return id; }
	int getType() const { return type; }
	int getPreviousState() const { return previousState; }
	int getState() const { return currentState; }
	void getSpeed(float &vx, float &vy) const
	{
		vx = this->vx; vy = this->vy;
	}
	void getPosition(float &x, float &y) const
	{
		x = this->x;
		y = this->y;
	}

	void renderBoundingBox();

	void addAnimation(int animationId);

	LPCollisionEvent sweptAABBEx(LPGameObject coO);
	void calcPotentialCollisions(vector<LPGameObject> *coObjects, vector<LPCollisionEvent> & coEvents);
	void filterCollision(
		vector<LPCollisionEvent> &coEvents,
		vector<LPCollisionEvent> &coEventsResult,
		float &minTx,
		float &minTy,
		float &nx,
		float &ny);

	virtual void update(DWORD dt, vector<GameObject*> *coObjects = nullptr);

	virtual void render() = 0;
	virtual void getBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
};

struct CollisionEvent
{
	GameObject* obj;
	float t, nx, ny;
	CollisionEvent(const float t, const float nx, const float ny, const LPGameObject obj = nullptr)
	{
		this->t = t; this->nx = nx; this->ny = ny; this->obj = obj;
	}

	static bool compare(const LPCollisionEvent &a, LPCollisionEvent &b)
	{
		return a->t < b->t;
	}
};