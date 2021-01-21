#pragma once
#include <d3d9.h>
#include <algorithm>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Blaster Master"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)

#define WINDOW_WIDTH 270
#define WINDOW_HEIGHT 263

#define FREE_CAM_WIDTH 100
#define FREE_CAM_HEIGHT 75

#define MAX_FRAME_RATE 200

#define GRID_CELL_HEIGHT 100
#define GRID_CELL_WIDTH 150

enum ObjectType
{
	TYPE_WALL = 0,
	TYPE_SOPHIA = 1,
	TYPE_ENEMY = 2,
	TYPE_ENEMY_WORM = 3,
	TYPE_BULLET = 4,
	TYPE_GATEWAY = 5,
	TYPE_WALLIMAGE = 6,
	TYPE_ENEMY_FLOATER = 7,
	TYPE_ENEMY_DOME = 8,
	TYPE_ENEMY_JUMPER = 9,
	TYPE_ENEMY_INSECT = 10,

	TYPE_JASON = 24,
	TYPE_BIGJASON = 21,
	TYPE_ITEM = 22,
	TYPE_PORTAL = 23,
	TYPE_ENEMY_SKULL = 11,
	TYPE_ENEMY_ORB_1 = 12,
	TYPE_ENEMY_CANNON = 13,
	TYPE_ENEMY_EYEBALL = 14,
	TYPE_ENEMY_TELEPORTER = 15,
	TYPE_ENEMY_CRABULLUS = 16,
	TYPE_ENEMY_ORB_2 = 17,
	TYPE_EFFECT = 25
};

enum TextureID
{
	ID_TEX_SOPHIA = 0,
	ID_TEX_ENEMY = 10,
	ID_TEX_MAP = 30
};

enum class BulletType
{
	SophiaBullet,
	FloaterBullet,
	JasonBullet,
	BigJasonBullet,
	SkullBullet
};

class CGlobalVariable
{
private:
	static CGlobalVariable *_instance;

public:
	static CGlobalVariable *GetInstance()
	{
		if (_instance == NULL)
			_instance = new CGlobalVariable();
		return _instance;
	}
	int ScreenHeight;
	int ScreenWidth;
};

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif