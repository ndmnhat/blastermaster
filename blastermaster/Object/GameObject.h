#pragma once
#include "..\Define\Define.h"
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "..\Utils\Utils.h"
#include "..\Animations\Animations.h"

class CBullet; //forward declaration
typedef CBullet* LPBULLET;

#define ID_TEX_BBOX -1		// special texture to draw object bounding box


using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:
	int Health;
	int Damage;

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;

	int ID;

	int width;
	int height;
	float gravity;

	bool isInCam = false;
	bool isDestroyed = false;
	bool isAttacked;
	DWORD dt;
	ObjectType type;
	LPANIMATION animation;

	LPANIMATION_SET animation_set;


public:
	bool isEnabled = true;
	bool isFreezing = false;
	bool hasGun = false;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int Getnx() { return this->nx; }
	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	void SetAnimation(LPANIMATION ani) { animation = ani; }
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	bool isCollidingWith(LPGAMEOBJECT coObject, float &space, int &direction);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
	void SetHealth(int health) { this->Health = health; }
	int GetHealth() { return this->Health; }
	void SetDamage(int damage) { this->Damage = damage; }
	void Attack(LPGAMEOBJECT object) { object->Attacked(this->Damage); }
	void Attacked(int damage) { this->Health -= damage; isAttacked = true; }
	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; };

	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;