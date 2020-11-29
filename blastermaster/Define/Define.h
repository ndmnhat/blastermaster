#pragma once
#include <d3d9.h>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 264

#define FREE_CAM_WIDTH 100
#define FREE_CAM_HEIGHT 75

#define MAX_FRAME_RATE 90

#define GRID_CELL_HEIGHT 100
#define GRID_CELL_WIDTH 150


enum ObjectType {
	TYPE_SOPHIA = 0,
	TYPE_WALL = 1,
	TYPE_ENEMY = 2
};

enum TextureID
{
	ID_TEX_SOPHIA = 0,
	ID_TEX_ENEMY = 10,
	ID_TEX_MAP = 30
};