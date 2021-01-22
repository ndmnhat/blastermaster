#pragma once
#include "..\Utils\Utils.h"
#include "..\Animations\Animations.h"
#include "..\Game\Game.h"
#include "..\Camera\Camera.h"
#include "..\Define\Define.h"
#include "..\Scene\CSceneManager.h"
//#define ID_TEX_MAP 30

class CMap
{
private:
	int dcolor = 1;
	int GlowTime = 3;
	int r = 255, g = 255, b = 255;
	int mapColumnCount, mapRowCount;
	int tileWidth, tileHeight;
	int tileCount, tileColumn;
	int tileMap[200][200];
	LPDIRECT3DTEXTURE9 _texture;
	wstring mapFile;
public:
	bool isStartingBossStage = false;
	CMap(wstring filePath, int TextureID);
	//void SetMapFile(LPCWSTR file);
	void ReadMap();
	void Update(DWORD dt);
	void DrawMap(CCamera * cam);
	int GetMapWidth() { return mapColumnCount * tileWidth; };
	int GetMapHeight() { return mapRowCount * tileHeight; };
	void StartBossStage();
};


