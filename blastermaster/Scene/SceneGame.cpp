#include "SceneGame.h"
#include "..\Object\OutdoorEnemy\OutdoorEnemy.h"
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS 5
#define SCENE_SECTION_OBJECTS 6
#define SCENE_SECTION_MAP 7
#define SCENE_SECTION_SECTION 8
#define OBJECT_TYPE_SOPHIA 0

#define MAX_SCENE_LINE 1024

CSceneGame::CSceneGame(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	//map = new CMap();
	key_handler = new CSceneGameKeyHandler(this);
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::_ParseSection_TEXTURES(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 5)
		return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CSceneGame::_ParseSection_MAP(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 1)
		return; // skip invalid lines
	wstring path = ToWSTR(tokens[0]);
	int mapTexID = atoi(tokens[1].c_str());
	//map->ReadMap(path.c_str());
	//map->ReadMap(L"map2.txt");
	//map->SetMapFile(path.c_str());
	map = new CMap(path, mapTexID);
}

void CSceneGame::_ParseSection_SECTION(std::string line)
{
	vector<std::string> tokens = split(line);
	if (tokens.size() < 5)
		return; // skip invalid lines

	int id = atoi(tokens[0].c_str());

	float Left = atof(tokens[1].c_str());
	float Top = atof(tokens[2].c_str());
	float Right = atof(tokens[3].c_str());
	float Bottom = atof(tokens[4].c_str());

	LPSECTION section = new CSection();
	section->SetSectionBoundary(Left, Top, Right, Bottom);

	CSectionManager::GetInstance()->Add(id, section);
}

void CSceneGame::_ParseSection_SPRITES(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 6)
		return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		//DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CSceneGame::_ParseSection_ANIMATIONS(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 3)
		return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2) // why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CSceneGame::_ParseSection_ANIMATION_SETS(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 2)
		return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
		//DebugOut(L"[INFO] Animation added: %d\n", ani_id);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CSceneGame::_ParseSection_OBJECTS(std::string line)
{
	vector<std::string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3)
		return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets *animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case TYPE_SOPHIA:
		if (CSceneManager::GetInstance()->Sophia != NULL)
		{
			DebugOut(L"[ERROR] SOPHIA object was created before!\n");
			return;
		}
		obj = new CSophia();
		CSceneManager::GetInstance()->Sophia = (CSophia*)obj;
		currentPlayer = CSceneManager::GetInstance()->Sophia;
		CCamera::GetInstance()->SetFollow(obj);
		DebugOut(L"[INFO] Sophia object created!\n");
		break;

	case TYPE_JASON:
		if (CSceneManager::GetInstance()->Jason != NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}
		obj = new CJason();
		CSceneManager::GetInstance()->Jason = (CJason*)obj;
		DebugOut(L"[INFO] Jason object created!\n");
		break;
	case TYPE_BIGJASON:
		if (CSceneManager::GetInstance()->BigJason != NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}
		obj = new CBigJason();
		CSceneManager::GetInstance()->BigJason = (CBigJason*)obj;
		currentPlayer = CSceneManager::GetInstance()->BigJason;
		CCamera::GetInstance()->SetFollow(obj); 
		DebugOut(L"[INFO] Bigjason object created!\n");
		break;
	case TYPE_WALL:
	{
		obj = new CWall();

		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());

		((CWall *)obj)->SetSize(width, height);
		obj->SetPosition(x, y);

		goto addObjectToGrid;
	}
	break;
	case TYPE_ENEMY_WORM:
		obj = new CWorm();
		//CCamera::GetInstance()->SetFollow(obj);
		break;
	case TYPE_GATEWAY:
	{
		obj = new CGateway();
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		float DestinationX = atof(tokens[6].c_str());
		float DestinationY = atof(tokens[7].c_str());
		((CGateway *)obj)->SetSize(width, height);
		((CGateway *)obj)->SetDestination(DestinationX, DestinationY);
		((CGateway *)obj)->newSectionID = atoi(tokens[8].c_str());
		obj->SetPosition(x, y);

		goto addObjectToGrid;
	}
	break;
	case TYPE_PORTAL:
		obj = new CPortal();
		((CPortal*)obj)->SceneID = atoi(tokens[4].c_str());
		obj->SetPosition(x, y);
		goto addObjectToGrid;
	case TYPE_WALLIMAGE:
	{
		obj = new CWallImage();
		int sprite_id = atoi(tokens[3].c_str());
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		((CWallImage *)obj)->SetImage(CSprites::GetInstance()->Get(sprite_id));
		((CWallImage *)obj)->SetSize(width, height);
		obj->SetPosition(x, y);

		goto addObjectToGrid;
	}
	break;
	case TYPE_ENEMY_FLOATER:
		obj = new CFloater();
		//CCamera::GetInstance()->SetFollow(obj);
		break;
	case TYPE_ENEMY_DOME:
		obj = new CDome();
		//CCamera::GetInstance()->SetFollow(obj);
		break;
	case TYPE_ENEMY_JUMPER:
		obj = new CJumper();
		//CCamera::GetInstance()->SetFollow(obj);
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);

addObjectToGrid:
	//objects.push_back(obj);
	CGrid::GetInstance()->addObject(obj);
}

void CSceneGame::Load()
{
	if (isLoaded)
	{
		CGrid::GetInstance()->updateObjects(backupObjects);
		CSectionManager::GetInstance()->Sections = backupSections;
		CSectionManager::GetInstance()->ChangeSection(CSectionManager::GetInstance()->GetObjectSectionID(this->currentPlayer), true);
		CCamera::GetInstance()->SetFollow(currentPlayer);
		return;
	}
	isLoaded = true;
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		std::string line(str);

		if (line[0] == '#')
			continue; // skip comment lines

		if (line == "[TEXTURES]")
		{
			section = SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]")
		{
			section = SCENE_SECTION_SPRITES;
			continue;
		}
		if (line == "[ANIMATIONS]")
		{
			section = SCENE_SECTION_ANIMATIONS;
			continue;
		}
		if (line == "[ANIMATION_SETS]")
		{
			section = SCENE_SECTION_ANIMATION_SETS;
			continue;
		}
		if (line == "[OBJECTS]")
		{
			section = SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP;
			continue;
		}
		if (line == "[SECTION]")
		{
			section = SCENE_SECTION_SECTION;
			continue;
		}
		if (line[0] == '[')
		{
			section = SCENE_SECTION_UNKNOWN;
			continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES:
			_ParseSection_TEXTURES(line);
			break;
		case SCENE_SECTION_SPRITES:
			_ParseSection_SPRITES(line);
			break;
		case SCENE_SECTION_ANIMATIONS:
			_ParseSection_ANIMATIONS(line);
			break;
		case SCENE_SECTION_ANIMATION_SETS:
			_ParseSection_ANIMATION_SETS(line);
			break;
		case SCENE_SECTION_OBJECTS:
			_ParseSection_OBJECTS(line);
			break;
		case SCENE_SECTION_MAP:
			_ParseSection_MAP(line);
			break;
		case SCENE_SECTION_SECTION:
			_ParseSection_SECTION(line);
			break;
		}
	}

	f.close();
	healthbar = new CHealthBar();
	map->ReadMap();
	CSectionManager::GetInstance()->ChangeSection(CSectionManager::GetInstance()->GetObjectSectionID(this->currentPlayer),true);
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//CCamera::GetInstance()->SetPosition(0.0f, 3024.0f); //Add cam position to scene.txt
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CSceneGame::Unload()
{
	backupObjects = CGrid::GetInstance()->getAllObjects(map->GetMapWidth(), map->GetMapHeight());
	backupSections = CSectionManager::GetInstance()->getAllSections();
	CSectionManager::GetInstance()->clearSections();
	CGrid::GetInstance()->clearGrid();
}

void CSceneGame::Update(DWORD dt)
{
	objects.clear();
	objects = CGrid::GetInstance()->ObjectsInCam(CCamera::GetInstance());

	for (auto &GameObject : objects)
	{
		GameObject->Update(dt, &objects);
	}
	//for (int i = 0; i < objects.size(); ++i)
	//{
	//	if (objects[i]->isDestroyed == true)
	//		SAFE_DELETE(objects[i]);
	//}
	if(currentPlayer->type == TYPE_JASON)
		if (((CJason*)currentPlayer)->state == JASON_STATE_INSOPHIA)
		{
			float jasonx = currentPlayer->x;
			float jasony = currentPlayer->y;
			currentPlayer = CSceneManager::GetInstance()->Sophia;
			CCamera::GetInstance()->SetFollow(currentPlayer);
			currentPlayer->isFreezing = false;
			((CSophia*)currentPlayer)->StartOpening();
			objects.push_back(currentPlayer);
		}
	CCamera::GetInstance()->Update(dt);
	CGrid::GetInstance()->updateObjects(objects);
	healthbar->Update(currentPlayer);
	//DebugOut(L"%d\n", CSectionManager::GetInstance()->CurrentSectionID);
	//DebugOut(L"%f\n",CCamera::GetInstance()->GetPosition().y);
	//CCamera::GetInstance()->SetPosition(0.0f,2048.0f);
}

void CSceneGame::Render()
{
	map->DrawMap(CCamera::GetInstance());
	vector<LPGAMEOBJECT> objecttorender = CGrid::GetInstance()->ObjectsToRender();
	for (int i = 0; i < objecttorender.size(); ++i)
	{
		if (objecttorender[i] != NULL)
			objecttorender[i]->Render();
	}
	vector<CWallImage *> wallimages = CGrid::GetInstance()->WallImageInCam;
	//DebugOut(L"wall size: %d\n", wallimages.size());
	for (int i = 0; i < wallimages.size(); ++i)
	{
		wallimages.at(i)->Render();
	}
	healthbar->Render();
}

void CSceneGameKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	switch (((CSceneGame*)scence)->currentPlayer->type)
	{
	case TYPE_SOPHIA:
	{
		CSophia* sophia = (CSophia*)(((CSceneGame*)scence)->currentPlayer);

		if (sophia->GetState() == SOPHIA_STATE_DIE)
			return;
		if (game->IsKeyDown(DIK_RIGHT))
			sophia->SetState(SOPHIA_STATE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			sophia->SetState(SOPHIA_STATE_WALKING_LEFT);
		else
		{
			int nx = sophia->Getnx();
			if (nx > 0)
				sophia->SetState(SOPHIA_STATE_IDLE_RIGHT);
			else
				sophia->SetState(SOPHIA_STATE_IDLE_LEFT);
		}
		if (game->IsKeyDown(DIK_UP))
		{
			sophia->isPressingUp = true;
		}
	}
	break;
	case TYPE_JASON:
	{
		CJason* jason = (CJason*)(((CSceneGame*)scence)->currentPlayer);

		if (jason->GetState() == JASON_STATE_DIE || jason->isJumpingIn)
			return;
		if (game->IsKeyDown(DIK_RIGHT))
			jason->SetState(JASON_STATE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			jason->SetState(JASON_STATE_WALKING_LEFT);
		else
		{
			int nx = jason->Getnx();
			if (nx > 0)
				jason->SetState(JASON_STATE_IDLE_RIGHT);
			else
				jason->SetState(JASON_STATE_IDLE_LEFT);
		}
	}
	break;
	case TYPE_BIGJASON:
		CBigJason* bigjason = (CBigJason*)(((CSceneGame*)scence)->currentPlayer);
		if (bigjason->GetState() == BIGJASON_STATE_DIE || bigjason->isAutoGoX || bigjason->isAutoGoY)
			return;
		int nx = bigjason->Getnx();
		int ny = bigjason->Getny();
		//if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN))
		//{
		if (game->IsKeyDown(DIK_RIGHT))
			bigjason->SetState(BIGJASON_STATE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			bigjason->SetState(BIGJASON_STATE_WALKING_LEFT);
		
		if (game->IsKeyDown(DIK_UP))
			bigjason->SetState(BIGJASON_STATE_WALKING_UP);
		else if (game->IsKeyDown(DIK_DOWN))
			bigjason->SetState(BIGJASON_STATE_WALKING_DOWN);
		//else
		//{
		//	if (ny > 0)
		//		bigjason->SetState(BIGJASON_STATE_IDLE_UP);
		//	else if (ny < 0)
		//		bigjason->SetState(BIGJASON_STATE_IDLE_DOWN);
		//}
		if (!game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_RIGHT))
		{
			if (nx > 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_RIGHT);
			else
				bigjason->SetState(BIGJASON_STATE_IDLE_LEFT);
		}
		if (!game->IsKeyDown(DIK_UP) && !game->IsKeyDown(DIK_DOWN))
		{
			//DebugOut(L"OK\n");
			if (ny > 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_UP);
			else
				bigjason->SetState(BIGJASON_STATE_IDLE_DOWN);
		}
		/*else
		{

			if (nx > 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_RIGHT);
			else if (nx < 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_LEFT);
			else if (ny > 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_UP);
			else if (ny < 0)
				bigjason->SetState(BIGJASON_STATE_IDLE_DOWN);
		}*/
	}
}

void CSceneGameKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_T)
	{
		if (CSceneManager::GetInstance()->GetCurrentSceneID() == 1)
			CSceneManager::GetInstance()->SetScene(2);
		else
			CSceneManager::GetInstance()->SetScene(1);
	}
	switch (((CSceneGame*)scence)->currentPlayer->type)
	{
	case TYPE_SOPHIA:
		{
			CSophia* sophia = (CSophia*)(((CSceneGame*)scence)->currentPlayer);
			switch (KeyCode)
			{
			case DIK_S:
				sophia->SetState(SOPHIA_STATE_JUMP);
				break;
			case DIK_A:
				if (sophia->isPressingUp == true)
					sophia->Fire(90);
				else
				{
					if (sophia->nx > 0)
						sophia->Fire(180);
					else
						sophia->Fire(0);
				}
				break;
			case DIK_Q:
				if (sophia->isJumping || sophia->isFalling)
					return;
				sophia->StartOpening();
				CJason* jason = CSceneManager::GetInstance()->Jason;
				((CSceneGame*)scence)->currentPlayer = jason;
				jason->isEnabled = true;
				jason->SetState(JASON_STATE_IDLE_RIGHT);
				jason->SetPosition(sophia->x+9, sophia->y+9);
				CCamera::GetInstance()->SetFollow(jason);
				CGrid::GetInstance()->safeRemoveObject(jason);
				CGrid::GetInstance()->addObject(jason);
				break;
			}
			return;
		}
	break;
	case TYPE_JASON:
		{
			CJason* jason = (CJason*)(((CSceneGame*)scence)->currentPlayer);
			if (jason->isJumpingIn)
				return;
			switch (KeyCode)
			{
			case DIK_S:
				jason->SetState(JASON_STATE_JUMP);
				break;
			case DIK_A:
				if (jason->nx > 0)
						jason->Fire(180);
				else
						jason->Fire(0);
				break;
			case DIK_Q:
				CSophia* sophia = CSceneManager::GetInstance()->Sophia;
				int direction;
				float space;
				if (jason->isCollidingWith(sophia, space, direction))
					jason->SetState(JASON_STATE_JUMPIN);
				break;
			}
			return;
		}
	break;
	case TYPE_BIGJASON:
	{
		CBigJason* bigjason = (CBigJason*)(((CSceneGame*)scence)->currentPlayer);
		if (bigjason->GetState() == BIGJASON_STATE_DIE || bigjason->isAutoGoX || bigjason->isAutoGoY)
			return;
		int nx = bigjason->Getnx();
		int ny = bigjason->Getny();
		if (bigjason->GetState() == BIGJASON_STATE_DIE)
			return;
		switch (KeyCode)
		{
		case DIK_S:
			break;
		case DIK_A:
			if (nx > 0)
				bigjason->Fire(180);
			else if (nx < 0)
				bigjason->Fire(0);
			else if (ny > 0)
				bigjason->Fire(90);
			else if (ny < 0)
				bigjason->Fire(-90);
			break;
		case DIK_Q:
			bigjason->SetState(BIGJASON_STATE_DIE);
			break;
		}
		return;
	}
	}

}

void CSceneGameKeyHandler::OnKeyUp(int KeyCode)
{


	switch (((CSceneGame*)scence)->currentPlayer->type)
	{
	case TYPE_SOPHIA:
	{
		CSophia* sophia = (CSophia*)(((CSceneGame*)scence)->currentPlayer);
		switch (KeyCode)
		{
		case DIK_UP:
			sophia->isPressingUp = false;
		}
		return;
	}
	break;
	case TYPE_JASON:
	break;
	}


}
