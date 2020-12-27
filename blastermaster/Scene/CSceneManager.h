#pragma once
#include "..\Define\Define.h"
#include "Scene.h"
#include "..\Game\Game.h"
//#include "..\Object\Player\Jason.h"
//#include "..\Object\Player\Sophia.h"
#include <unordered_map>

class CSophia;
class CJason;
class CBigJason;
using namespace std;


class CSceneManager
{
	static CSceneManager* __instance;
	unordered_map<int, CScene*> scenes;
	int CurrentSceneID = -1;
public:
	CSophia* Sophia;
	CJason* Jason;
	CBigJason* BigJason;
	CSceneManager();
	CScene* GetCurrentScene();
	int GetCurrentSceneID() { return CurrentSceneID; }
	void SetScene(int id);
	void AddScene(CScene * scene);
	void Update(DWORD dt);
	void Render();
	static CSceneManager* GetInstance();
};

