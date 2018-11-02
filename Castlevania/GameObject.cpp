#include "GameObject.h"


unordered_map<int, Animation* > GameObject::animations;

GameObject::~GameObject()
{
	if (texture != NULL) texture->Release();
}


void GameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	auto texture = TextureManager::getInstance()->get(ID_TEX_BBOX);
	auto game = Game::getInstance();

	auto box = getBoundingBox();
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)box.right - (int)box.left;
	rect.bottom = (int)box.bottom - (int)box.top;

	game->draw(x, y, texture, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void GameObject::addAnimation(int animationId)
{
	auto animation = AnimationManager::getInstance()->get(animationId);
	animations[animationId] = animation;
}


LPCollisionEvent GameObject::sweptAABBEx(LPGameObject coO)
{
	Box staticBox, movingBox;
	float t, normalX, normalY;

	staticBox = coO->getBoundingBox();
	float svx, svy;
	coO->getSpeed(svx, svy);
	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	movingBox = getBoundingBox();

	sweptAABB(movingBox, staticBox,
		dx, dy,
		t, normalX, normalY
	);
	if (normalX != 0) DebugOut(L"collision");

	auto collisonEvent = new CollisionEvent(t, normalX, normalY, coO);

	return collisonEvent;

}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void GameObject::calcPotentialCollisions
(vector<LPGameObject>* coObjects, vector<LPCollisionEvent>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCollisionEvent e = sweptAABBEx(coObjects->at(i));

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


void GameObject::update(DWORD dt, vector<GameObject*> *coObject)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

