#pragma once
#include <d3d9.h>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 264

#define FREE_CAM_WIDTH 50
#define FREE_CAM_HEIGHT 50

#define MAX_FRAME_RATE 60

enum GameObjectID
{

};

enum TextureID
{
	ID_TEXT_ENEMY = 10,
};