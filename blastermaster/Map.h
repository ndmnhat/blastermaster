#pragma once
#include "debug.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"
#include "Define.h"

#define ID_TEX_MAP 30

class CMap
{
private:
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	int tileCount, tileColumn;
	int tileMap[200][200];
	LPDIRECT3DTEXTURE9 _texture;
public:
	void ReadMap(char * filename);
	void DrawMap(CCamera * cam);
};


