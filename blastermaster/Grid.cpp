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
	float left, right, top, bottom;
	object->GetBoundingBox(left, top, right, bottom);
	int firstRow = top / GRID_CELL_HEIGHT;
	int lastRow = bottom / GRID_CELL_HEIGHT;
	int firstColumn = left / GRID_CELL_WIDTH;
	int lastColumn = right / GRID_CELL_WIDTH;
	for (int i = firstRow; i <= lastRow; ++i)
	{
		for (int j = firstColumn; j < lastColumn; ++j)
		{

			Cell[i][j].push_back(object);
		}
	}
}
void CGrid::removeObject(LPGAMEOBJECT object)
{
	float left, right, top, bottom;
	object->GetBoundingBox(left, top, right, bottom);
	int firstRow = top / GRID_CELL_HEIGHT - 1;
	int lastRow = bottom / GRID_CELL_HEIGHT - 1;
	int firstColumn = left / GRID_CELL_WIDTH - 1;
	int lastColumn = right / GRID_CELL_WIDTH - 1;
	for (int CellRowIndex = firstRow; CellRowIndex < lastRow; ++CellRowIndex)
	{
		for (int CellColumnIndex = firstColumn; CellColumnIndex < lastColumn; ++CellColumnIndex)
		{
			for (int i = 0; i < Cell[CellRowIndex][CellColumnIndex].size(); ++i)
			{
				if (Cell[CellRowIndex][CellColumnIndex].at(i) == object)
				{
					Cell[CellRowIndex][CellColumnIndex].erase(Cell[CellRowIndex][CellColumnIndex].begin() + i);
				}
			}
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
