#pragma once
#include "..\Utils\Utils.h"
#include "..\Animations\Animations.h"
#include "..\Game\Game.h"
#include "..\Camera\Camera.h"
#include "..\Define\Define.h"

//#define ID_TEX_MAP 30

class CMap
{
private:
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	int tileCount, tileColumn;
	int tileMap[200][200];
	LPDIRECT3DTEXTURE9 _texture;
	wstring mapFile;
public:
	CMap(wstring filePath, int TextureID);
	//void SetMapFile(LPCWSTR file);
	void ReadMap();
	void DrawMap(CCamera * cam);
};


