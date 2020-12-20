#pragma once
#include <d3d9.h>
#include <algorithm>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Blaster Master"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)

#define WINDOW_WIDTH 272
#define WINDOW_HEIGHT 264

#define FREE_CAM_WIDTH 100
#define FREE_CAM_HEIGHT 75

#define MAX_FRAME_RATE 120

#define GRID_CELL_HEIGHT 100
#define GRID_CELL_WIDTH 150


enum ObjectType {
	TYPE_SOPHIA = 0,
	TYPE_WALL = 1,
	TYPE_ENEMY = 2,
	TYPE_ENEMY_WORM = 3,
	TYPE_BULLET = 4,
	TYPE_GATEWAY = 5,
	TYPE_WALLIMAGE = 6
};

enum TextureID
{
	ID_TEX_SOPHIA = 0,
	ID_TEX_ENEMY = 10,
	ID_TEX_MAP = 30
};

enum class BulletType {
	SophiaBullet,
	FloaterBullet,
};

class CGlobalVariable {
private:
	static CGlobalVariable* _instance;
public:
	static CGlobalVariable* GetInstance() { if (_instance == NULL) _instance = new CGlobalVariable(); return _instance; }
	int ScreenHeight;
	int ScreenWidth;
};