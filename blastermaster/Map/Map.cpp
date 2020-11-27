#include "Map.h"
#include <iostream>
#include <fstream>
using namespace std;

CMap::CMap(wstring filePath, int TextureID)
{
	this->mapFile = filePath;
	this->_texture = CTextures::GetInstance()->Get(TextureID);
}

//void CMap::SetMapFile(LPCWSTR file)
//{
//	this->mapFile = file;
//}

void CMap::ReadMap()
{
	ifstream fs;
	fs.clear();
	fs.open(mapFile);
	fs >> mapWidth >> mapHeight >> tileWidth >> tileHeight >> tileCount >> tileColumn;
	for (int i = 0; i < mapWidth * mapHeight; ++i)
	{
		fs >> tileMap[i / mapHeight][i % mapWidth];
	}
	fs.close();
}
void CMap::DrawMap(CCamera * cam)
{
	CGame * game = CGame::GetInstance();
	D3DXVECTOR3 camPosition = cam->GetPosition();
	cam->SetCamBoundary(mapWidth*tileWidth - SCREEN_WIDTH, mapHeight*tileHeight - SCREEN_HEIGHT);
	//Origin is left down -> reverse row index
	int firstRow = ((mapHeight * tileHeight) - camPosition.y) / tileHeight;
	int firstColumn = camPosition.x / tileWidth;
	for (int i = 0; i < firstRow + SCREEN_HEIGHT / tileWidth; i++)
	{
		for (int j = 0; j < firstColumn + SCREEN_WIDTH / tileHeight; j++)
		{
			int currentRow = firstRow + i;
			int currentColumn = firstColumn + j;
			int gid = tileMap[currentRow][currentColumn]-1;
			//float tileX = (float)(j * tileWidth - (camPosition.x - (camPosition.x / 16) * 16));
			//float tileY = (float)(i * tileHeight - (camPosition.y - (camPosition.y / 16) * 16));
			float tileX = (float)(j*tileWidth-(int)camPosition.x%tileWidth);
			float tileY = (float)(i*tileHeight- (int)camPosition.y%tileHeight);
			D3DXVECTOR3 tilePosition(tileX, tileY, 0);
			RECT r;
			r.left = (long)((gid % tileColumn) * tileWidth);
			r.right = (gid % tileColumn) * tileWidth + tileWidth;
			r.top = (gid / tileColumn) * tileHeight;
			r.bottom = (gid / tileColumn) * tileHeight + tileHeight;
			game->Draw(tilePosition, _texture, r);
		}
	}
}