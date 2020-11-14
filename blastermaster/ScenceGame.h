#pragma once
#include <fstream>
#include <string>
#include "Sophia.h"
#include "Scence.h"

using namespace std;

class CScenceGame : public CScene
{
protected:
	CSophia *player;					// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CScenceGame(int id, LPCWSTR filePath);

	virtual void Load();

	CSophia * GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

