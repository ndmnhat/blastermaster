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

void CGrid::safeRemoveObject(LPGAMEOBJECT object)
{
	int firstRow = 0;
	int lastRow = Cell.size()-1;
	int firstColumn = 0;
	int lastColumn;
	for (int CellRowIndex = firstRow; CellRowIndex <= lastRow; ++CellRowIndex)
	{
		lastColumn = Cell[CellRowIndex].size()-1;
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
		{
			SAFE_DELETE(objects[i]);
			return;
		}
		addObject(objects[i]);
	}
}

void CGrid::clearGrid()
{
	_instance = NULL;
}

vector<LPGAMEOBJECT> CGrid::getAllObjects(int MapWidth, int MapHeight)
{
	vector<LPGAMEOBJECT> objects;
	int firstRow = 0;
	int lastRow = MapHeight / GRID_CELL_HEIGHT;
	int firstColumn = 0;
	int lastColumn = MapWidth / GRID_CELL_WIDTH;
	for (int CellRowIndex = firstRow; CellRowIndex <= lastRow; ++CellRowIndex)
	{
		//lastColumn = Cell[CellRowIndex].size();
		for (int CellColumnIndex = firstColumn; CellColumnIndex <= lastColumn; ++CellColumnIndex)
		{
			for (int i = 0; i < Cell[CellRowIndex][CellColumnIndex].size(); ++i)
			{
				if(Cell[CellRowIndex][CellColumnIndex].at(i)!=NULL)
					objects.push_back(Cell[CellRowIndex][CellColumnIndex].at(i));
			}
		}
	}

	return objects;
}

vector<LPGAMEOBJECT> CGrid::ObjectsToRender()
{
	CCamera* cam = CCamera::GetInstance();
	int firstRow = cam->GetPosition().y / GRID_CELL_HEIGHT;
	int firstColumn = cam->GetPosition().x / GRID_CELL_WIDTH;
	int lastRow = firstRow - ceil((double)WINDOW_HEIGHT / GRID_CELL_HEIGHT);
	int lastColumn = firstColumn + ceil((double)WINDOW_WIDTH / GRID_CELL_WIDTH);
	vector<LPGAMEOBJECT> objects;
	WallImageInCam.clear();
	for (int i = lastRow; i <= firstRow; ++i)
	{
		for (int j = firstColumn; j <= lastColumn; ++j)
		{
			for (auto& GameObject : Cell[i][j])
			{
				if (GameObject->isInCam == false && GameObject->isEnabled)
				{
					if (GameObject->type == TYPE_WALLIMAGE)
						WallImageInCam.push_back((CWallImage*)GameObject);
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

vector<LPGAMEOBJECT> CGrid::ObjectsInCam(CCamera* cam)
{
	int firstRow = cam->GetPosition().y / GRID_CELL_HEIGHT;
	int firstColumn = cam->GetPosition().x / GRID_CELL_WIDTH;
	int lastRow = firstRow - ceil((double)WINDOW_HEIGHT / GRID_CELL_HEIGHT);
	int lastColumn = firstColumn + ceil((double)WINDOW_WIDTH / GRID_CELL_WIDTH);
	vector<LPGAMEOBJECT> objects;
	WallImageInCam.clear();
	for (int i = lastRow; i <= firstRow; ++i)
	{
		for (int j = firstColumn; j <= lastColumn; ++j)
		{
			for (auto& GameObject : Cell[i][j])
			{
				if (GameObject->isInCam == false && GameObject->isEnabled && GameObject->isFreezing == false)
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
