#include "Grid.h"
#include "..\Utils\Utils.h"

CGrid* CGrid::_instance = NULL;

void CGrid::addObject(LPGAMEOBJECT object)
{
	if (object == NULL)
		return;
	float left, right, top, bottom;
	object->GetBoundingBox(left, top, right, bottom);
	int firstRow = top / GRID_CELL_HEIGHT;
	int lastRow = bottom / GRID_CELL_HEIGHT;
	int firstColumn = left / GRID_CELL_WIDTH;
	int lastColumn = right / GRID_CELL_WIDTH;
	for (int i = lastRow; i <= firstRow; ++i)
	{
		for (int j = firstColumn; j <= lastColumn; ++j)
		{
			//DebugOut(L"%d , %d , %d\n", object->type, i, j);
			Cell[i][j].push_back(object);
		}
	}
}
void CGrid::removeObject(LPGAMEOBJECT object)
{
	float left, right, top, bottom;
	object->GetBoundingBox(left, top, right, bottom);
	int firstRow = top / GRID_CELL_HEIGHT + 1;
	int lastRow = bottom / GRID_CELL_HEIGHT - 1;
	int firstColumn = left / GRID_CELL_WIDTH - 1;
	int lastColumn = right / GRID_CELL_WIDTH + 1;
	for (int CellRowIndex = lastRow; CellRowIndex <= firstRow; ++CellRowIndex)
	{
		for (int CellColumnIndex = firstColumn; CellColumnIndex <= lastColumn; ++CellColumnIndex)
		{
			for (int i = 0; i < Cell[CellRowIndex][CellColumnIndex].size(); ++i)
			{
				Cell[CellRowIndex][CellColumnIndex].erase(std::remove(Cell[CellRowIndex][CellColumnIndex].begin(), Cell[CellRowIndex][CellColumnIndex].end(), object), Cell[CellRowIndex][CellColumnIndex].end());
			}
		}
	}

}

void CGrid::updateObjects(vector<LPGAMEOBJECT> objects)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		removeObject(objects[i]);
		if (objects[i]->isDestroyed == true)
			SAFE_DELETE(objects[i]);
		addObject(objects[i]);
	}
}

vector<LPGAMEOBJECT> CGrid::ObjectsInCam(CCamera* cam)
{
	int firstRow = cam->GetPosition().y / GRID_CELL_HEIGHT;
	int firstColumn = cam->GetPosition().x / GRID_CELL_WIDTH;
	int lastRow = firstRow - ceil((double)SCREEN_HEIGHT / GRID_CELL_HEIGHT);
	int lastColumn = firstColumn + ceil((double)SCREEN_WIDTH / GRID_CELL_WIDTH);
	vector<LPGAMEOBJECT> objects;
	for (int i = lastRow; i <= firstRow; ++i)
	{
		for (int j = firstColumn; j <= lastColumn; ++j)
		{
			for (auto& GameObject : Cell[i][j])
			{
				if (GameObject->isInCam == false)
				{
					objects.push_back(GameObject);
					GameObject->isInCam = true;
				}
			}
		}
	}

	for (auto& GameObject : objects)
	{
		GameObject->isInCam = false;
	}

	return objects;
}
