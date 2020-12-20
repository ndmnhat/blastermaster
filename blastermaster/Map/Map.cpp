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
	fs >> mapColumnCount >> mapRowCount >> tileWidth >> tileHeight >> tileCount >> tileColumn;
	for (int i = 0; i < mapColumnCount * mapRowCount; ++i)
	{
		fs >> tileMap[i / mapColumnCount][i % mapColumnCount];
	}
	fs.close();
	//CCamera::GetInstance()->SetCamBoundary(mapColumnCount * tileWidth - WINDOW_WIDTH, mapRowCount * tileHeight);
}
void CMap::DrawMap(CCamera * cam)
{
	CGame * game = CGame::GetInstance();
	D3DXVECTOR3 camPosition = cam->GetPosition();
	//Origin is left down -> reverse row index
	int firstRow = ((GetMapHeight() - camPosition.y) / tileHeight);
	//DebugOut(L"%d\n", firstRow);
	int firstColumn = camPosition.x / tileWidth;
	for (int i = 0; i < WINDOW_HEIGHT / tileHeight; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / tileWidth; j++)
		{
			int currentRow = firstRow + i;
			int currentColumn = firstColumn + j;
			int gid = tileMap[currentRow][currentColumn]-1;
			//float tileX = (float)(j * tileWidth - (camPosition.x - (camPosition.x / 16) * 16));
			//float tileY = (float)(i * tileHeight - (camPosition.y - (camPosition.y / 16) * 16));
			float tileX = (float)(j*tileWidth - (int)camPosition.x%tileWidth);
			float tileY = (float)((i-1)*tileHeight + (int)camPosition.y%tileHeight);
			//if ((int)camPosition.y % tileHeight == 0)
			//	DebugOut(L"%d\n", firstRow);
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
