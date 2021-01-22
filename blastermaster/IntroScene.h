#pragma once

#include "d3dx9.h"
#include "Object/GameObject.h"
#include "Scene/Scene.h"
#include "Scene/CSceneManager.h"
#include "OpeningScene.h"



class IntroScene : public CScene
{
	/*bool isLoaded = false;
	unordered_map<int, LPSECTION> backupSections;
	vector<LPGAMEOBJECT> backupObjects;*/
	//vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT>* introobject;
	CGameObject* currentscene;

	void _ParseSection_TEXTURES(std::string line);
	void _ParseSection_SPRITES(std::string line);
	void _ParseSection_ANIMATIONS(std::string line);
	void _ParseSection_ANIMATION_SETS(std::string line);
	void _ParseSection_OBJECTS(std::string line);

public:
	/*CPlayer *currentPlayer;
	CPlayer *GetPlayer() { return currentPlayer; }*/
	IntroScene(int id, LPCWSTR filePath);

	virtual void Update(DWORD dt);
	virtual void Render();
	
	virtual void Load();
	virtual void Unload();
	~IntroScene();
};
class CSceneGameKeyHandlerIntro : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSceneGameKeyHandlerIntro(CScene *s) : CSceneKeyHandler(s) {};
};


