#pragma once
#include "..\Animations\Animations.h"
#include "Scene.h"
#include "..\Object\Player\Sophia.h"
#include "..\Object\Player\Jason.h"
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
#include "..\Object\Player\BigJason.h"
#include "CSceneManager.h"
#include "..\Object\OutdoorEnemy\Insect.h"
#include "..\Object\OutdoorEnemy\Skull.h"
#include "..\Object\OutdoorEnemy\Orb1.h"
#include "..\Object\OutdoorEnemy\Orb2.h"
#include "..\Object\OutdoorEnemy\BossCrabullus.h"
#include <fstream>
#include "..\Map\Map.h"
#include "..\Grid\Grid.h"
#include "..\Map\Section.h"
#include "..\HUD\HealthBar.h"

using namespace std;
class CMap; //forward declaration to temporarily fix circular include
class CSceneGame : public CScene
{
protected:
	bool isLoaded = false;
	unordered_map<int, LPSECTION> backupSections;
	vector<LPGAMEOBJECT> backupObjects;
	CHealthBar *healthbar;
	//CSophia *sophia;
	//CJason* jason;
	//CPlayer* currentPlayer;
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
	CMap *map;
	CPlayer *currentPlayer;
	CSceneGame(int id, LPCWSTR filePath);
	CPlayer *GetPlayer() { return currentPlayer; }
	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();
	void StartBossStage();
	void BossStageStarted();
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
