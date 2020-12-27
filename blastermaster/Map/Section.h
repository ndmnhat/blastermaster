#pragma once
#include "..\Camera\Camera.h"
class CSection
{
private:
	float Left;
	float Top;
	float Right;
	float Bottom;
public:
	void SetSectionBoundary(float left, float top, float right, float bottom) { this->Left = left; this->Top = top; this->Right = right; this->Bottom = bottom; }
	void GetSectionBoundary(float& left, float& top, float& right, float& bottom) { left = this->Left; top = this->Top; right = this->Right; bottom = this->Bottom;}
	CSection();
};
typedef CSection* LPSECTION;

class CSectionManager
{
private:
	static CSectionManager* _instance;
public:
	LPSECTION CurrentSection = NULL;
	int CurrentSectionID;
	unordered_map<int, LPSECTION> Sections;
	static CSectionManager* GetInstance() { if (_instance == NULL) _instance = new CSectionManager(); return _instance; }
	void Add(int id, LPSECTION Section);
	int GetObjectSectionID(LPGAMEOBJECT Object);
	void ChangeSection(int id, bool isSet = false);
	unordered_map<int, LPSECTION> getAllSections() { return Sections; }
	void clearSections() {_instance = NULL;}
	LPSECTION Get(unsigned int id);
};
