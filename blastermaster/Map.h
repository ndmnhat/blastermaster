#pragma once
#include "debug.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

#define ID_TEX_MAP 30
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 264

class Map
{
private:
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	int tileCount;
	int tileMap[200][200];
	LPDIRECT3DTEXTURE9 _texture;
public:
	void ReadMap(char * filename);
	void DrawMap();
};

