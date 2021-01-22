#include "IntroScene.h"
#include "Animations/Animations.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS 5
#define SCENE_SECTION_OBJECTS 6
//#define SCENE_SECTION_MAP 7
//#define SCENE_SECTION_SECTION 8
#define MAX_SCENE_LINE 1024


IntroScene::IntroScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CSceneGameKeyHandlerIntro(this);
	//vector<LPGAMEOBJECT>* introobject = new vector<LPGAMEOBJECT>;
}

void IntroScene::_ParseSection_TEXTURES(std::string line)
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

void IntroScene::_ParseSection_SPRITES(std::string line)
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

void IntroScene::_ParseSection_ANIMATIONS(std::string line)
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

void IntroScene::_ParseSection_ANIMATION_SETS(std::string line)
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

void IntroScene::_ParseSection_OBJECTS(std::string line)
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
	vector<LPGAMEOBJECT>* introobject = new vector<LPGAMEOBJECT>;
	CGameObject *obj = NULL;
	switch (object_type)
	{
	case TYPE_INTRO_OPENING:
	{
		obj = new OpeningScene();
		currentscene = obj;
	}
	default:
		break;
	}
	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);

	introobject->push_back(obj);
}



void IntroScene::Update(DWORD dt)
{
	currentscene->Update(dt);
	if (currentscene->animation_set->at(0)->GetCurrentFrame() == currentscene->animation_set->at(0)->GetFramesSize() - 1) {
		CSceneManager::GetInstance()->SetScene(1);
	}
}

void IntroScene::Render()
{
	currentscene->Render();
}


void IntroScene::Load()
{
	/*if (isLoaded)
	{
		CGrid::GetInstance()->updateObjects(backupObjects);
		CSectionManager::GetInstance()->Sections = backupSections;
		CSectionManager::GetInstance()->ChangeSection(CSectionManager::GetInstance()->GetObjectSectionID(this->currentPlayer), true);
		CCamera::GetInstance()->SetFollow(currentPlayer);
		return;
	}
	isLoaded = true;*/
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
		/*if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP;
			continue;
		}
		if (line == "[SECTION]")
		{
			section = SCENE_SECTION_SECTION;
			continue;
		}*/
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
		/*case SCENE_SECTION_MAP:
			_ParseSection_MAP(line);
			break;
		case SCENE_SECTION_SECTION:
			_ParseSection_SECTION(line);
			break;*/
		}
	}

	f.close();
	/*healthbar = new CHealthBar();
	map->ReadMap();*/
	//CSectionManager::GetInstance()->ChangeSection(CSectionManager::GetInstance()->GetObjectSectionID(this->currentPlayer), true);
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//CCamera::GetInstance()->SetPosition(0.0f, 3024.0f); //Add cam position to scene.txt
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroScene::Unload()
{
	//backupObjects = CGrid::GetInstance()->getAllObjects(map->GetMapWidth(), map->GetMapHeight());
	/*backupSections = CSectionManager::GetInstance()->getAllSections();
	CSectionManager::GetInstance()->clearSections();
	CGrid::GetInstance()->clearGrid();*/
}

void CSceneGameKeyHandlerIntro::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	switch (*states)
	{
		case DIK_S:
		{
			OpeningScene* openingscene = (OpeningScene*)(((CGameObject*)scence)->type);
			
		}
	}
}

void CSceneGameKeyHandlerIntro::OnKeyDown(int KeyCode)
{
	
}

void CSceneGameKeyHandlerIntro::OnKeyUp(int KeyCode)
{
}

IntroScene::~IntroScene()
{
}
