#pragma once
#include "..\Animations\Animations.h"
#include "Scene.h"
#include "..\Object\Player\Sophia.h"
#include <fstream>
#include <iostream>


using namespace std;

class CSceneGame : public CScene
{
protected:
	CSophia *player;					// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(std::string line);
	void _ParseSection_SPRITES(std::string line);
	void _ParseSection_ANIMATIONS(std::string line);
	void _ParseSection_ANIMATION_SETS(std::string line);
	void _ParseSection_OBJECTS(std::string line);


public:
	CSceneGame(int id, LPCWSTR filePath);

	void Load();
	void Unload();
	void Update(DWORD dt);
	void Render();

	CSophia * GetPlayer() { return player; }
	~CSceneGame();
	//friend class CPlayScenceKeyHandler;
};

class CSceneGameKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {}
	CSceneGameKeyHandler(CScene *s) : CSceneKeyHandler(s) {};
	
};
