#include "Grid.h"

void CGrid::initGrid(vector<LPGAMEOBJECT> objects)
{
	for (auto& object : objects)
	{
		Cell[object->GetX() / GRID_CELL_WIDTH][object->GetY() / GRID_CELL_HEIGHT].push_back(object);
	}
}

void CGrid::addObject(LPGAMEOBJECT object)
{
	int CellColumnIndex = object->GetX() / GRID_CELL_WIDTH;
	int CellRowIndex = object->GetY() / GRID_CELL_HEIGHT;
	Cell[CellColumnIndex][CellRowIndex].push_back(object);
}
void CGrid::removeObject(LPGAMEOBJECT object)
{
	int CellColumnIndex = object->GetX() / GRID_CELL_WIDTH;
	int CellRowIndex = object->GetY() / GRID_CELL_HEIGHT;
	for (int i = 0; i < Cell[CellColumnIndex][CellRowIndex].size(); ++i)
	{
		if (Cell[CellColumnIndex][CellRowIndex].at(i) == object)
		{
			Cell[CellColumnIndex][CellRowIndex].erase(Cell[CellColumnIndex][CellRowIndex].begin() + i);
		}
	}
}

void CGrid::updateObjects(vector<LPGAMEOBJECT> objects)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		removeObject(objects[i]);
		addObject(objects[i]);
	}
}

vector<LPGAMEOBJECT> CGrid::ObjectsInCam(CCamera* cam)
{
	int firstRow = cam->GetPosition().y / GRID_CELL_HEIGHT;
	int firstColumn = cam->GetPosition().x / GRID_CELL_WIDTH;
	vector<LPGAMEOBJECT> objects;
	for (int i = 0; i < firstRow + SCREEN_HEIGHT / GRID_CELL_HEIGHT; ++i)
	{
		for (int j = 0; j < firstColumn + SCREEN_WIDTH / GRID_CELL_WIDTH; ++j)
		{
			for (auto& GameObject : Cell[firstRow + i][firstRow + j])
			{
				objects.push_back(GameObject);
			}
		}
	}
	return objects;
}
