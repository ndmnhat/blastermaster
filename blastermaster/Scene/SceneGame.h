#pragma once
#include "..\Animations\Animations.h"
#include "Scene.h"
#include "..\Object\Player\Sophia.h"
#include "..\Object\Wall.h"
#include "..\Object\OutdoorEnemy\OutdoorEnemy.h"
#include "..\Object\OutdoorEnemy\Worm.h"
#include "..\Object\Gateway.h"
#include "..\Object\WallImage.h"
#include "..\Object\OutdoorEnemy\Floater.h"
#include "..\Object\OutdoorEnemy\Dome.h"
#include "..\Object\OutdoorEnemy\Jumper.h"
#include "..\Object\IndoorEnemy\Eyeball.h"
#include "..\Object\IndoorEnemy\IndoorEnemy.h"
#include "..\Object\IndoorEnemy\Teleporter.h"
#include "..\Object\IndoorEnemy\Cannon.h"

#include <fstream>
#include "..\Map\Map.h"
#include "..\Grid\Grid.h"
#include "..\Map\Section.h"

using namespace std;
class CMap; //forward declaration to temporarily fix circular include
class CSceneGame : public CScene
{
protected:
	CMap *map;
	CSophia *player;
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_TEXTURES(std::string line);
	void _ParseSection_SPRITES(std::string line);
	void _ParseSection_ANIMATIONS(std::string line);
	void _ParseSection_ANIMATION_SETS(std::string line);
	void _ParseSection_OBJECTS(std::string line);
	void _ParseSection_MAP(std::string line);
	void _ParseSection_SECTION(std::string line);
	friend class CSceneGameKeyHandler;

public:
	CSceneGame(int id, LPCWSTR filePath);

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();

	CSophia *GetPlayer() { return player; }
	~CSceneGame();
	//friend class CPlayScenceKeyHandler;
};

class CSceneGameKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSceneGameKeyHandler(CScene *s) : CSceneKeyHandler(s){};
};
