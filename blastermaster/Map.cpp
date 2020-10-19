#include "Map.h"
#include <iostream>
#include <fstream>
using namespace std;

void Map::ReadMap(char* filename)
{
	fstream fs;
	fs.open(filename, ios::in | ios::out);
	fs >> mapWidth >> mapHeight >> tileWidth >> tileHeight >> tileCount;
	for (int i = 0; i < mapWidth * mapHeight; ++i)
	{
		fs >> tileMap[i / mapHeight][i % mapWidth];
	}
	_texture = CTextures::GetInstance()->Get(ID_TEX_MAP);
}
void Map::DrawMap()
{
	CGame * game = CGame::GetInstance();
	float xcam, ycam;
	xcam = 1024;
	ycam = 1040;
	int firstRow = ycam / tileHeight;
	int firstColumn = xcam / tileWidth;
	for (int i = 0; i < firstRow + SCREEN_HEIGHT / tileWidth; i++)
	{
		for (int j = 0; j < firstColumn + SCREEN_WIDTH / tileHeight; j++)
		{
			int currentRow = firstRow + i;
			int currentColumn = firstColumn + j;
			int gid = tileMap[currentRow][currentColumn]-1;
			game->Draw((float)(j * tileWidth-(int)xcam%16), (float)(i * tileHeight-(int)ycam%16), _texture, (gid%13) * tileWidth, (gid / 13) * tileHeight, (gid % 13) * tileWidth + tileWidth, (gid / 13) * tileHeight + tileHeight);
		}
	}
}