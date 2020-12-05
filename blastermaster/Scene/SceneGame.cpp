#include "SceneGame.h"
#include "..\Object\OutdoorEnemy\OutdoorEnemy.h"
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define OBJECT_TYPE_SOPHIA	0

#define MAX_SCENE_LINE 1024

CSceneGame::CSceneGame(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	//map = new CMap();
	key_handler = new CSceneGameKeyHandler(this);
	grid = new CGrid();
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::_ParseSection_TEXTURES(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

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

	if (tokens.size() < 1) return; // skip invalid lines
	wstring path = ToWSTR(tokens[0]);
	int mapTexID = atoi(tokens[1].c_str());
	//map->ReadMap(path.c_str());
	//map->ReadMap(L"map2.txt");
	//map->SetMapFile(path.c_str());
	map = new CMap(path, mapTexID);
}

void CSceneGame::_ParseSection_SPRITES(std::string line)
{
	vector<std::string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

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

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CSceneGame::_ParseSection_OBJECTS(std::string line)
{
	vector<std::string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case TYPE_SOPHIA:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CSophia();
		player = (CSophia*)obj;
		CCamera::GetInstance()->SetFollow(obj);
		DebugOut(L"[INFO] Player object created!\n");
		break;

	case TYPE_WALL:
	{
		obj = new CWall();

		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());

		((CWall*)obj)->SetSize(width, height);
		obj->SetPosition(x, y);

		goto addObjectToGrid;
	}

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
	grid->addObject(obj);
}

void CSceneGame::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		std::string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	map->ReadMap();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	CCamera::GetInstance()->SetPosition(0.0f, 2048.0f); //Add cam position to scene.txt
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CSceneGame::Unload()
{
}

void CSceneGame::Update(DWORD dt)
{
	objects.clear();
	for (auto& GameObject : grid->ObjectsInCam(CCamera::GetInstance()))
	{
		objects.push_back(GameObject);
	}
	for (auto& GameObject : objects)
	{
		GameObject->Update(dt, &objects);
	}
	CCamera::GetInstance()->Update(dt);
	grid->updateObjects(objects);
}

void CSceneGame::Render()
{
	map->DrawMap(CCamera::GetInstance());
	for (auto& GameObject : objects)
	{
		GameObject->Render();
	}
}

void CSceneGameKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSophia* sophia = ((CSceneGame*)scence)->GetPlayer();

	if (sophia->GetState() == SOPHIA_STATE_DIE) return;
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
}

void CSceneGameKeyHandler::OnKeyDown(int KeyCode)
{
	CSophia* sophia = ((CSceneGame*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		sophia->SetState(SOPHIA_STATE_JUMP);
		break;
	case DIK_A:
		break;
	}
	return;
}

void CSceneGameKeyHandler::OnKeyUp(int KeyCode)
{

}
