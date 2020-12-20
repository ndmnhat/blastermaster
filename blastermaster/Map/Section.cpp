#include "Section.h"

CSectionManager* CSectionManager::_instance = NULL;

void CSectionManager::Add(int id, LPSECTION Section)
{
	Sections[id] = Section;
}

void CSectionManager::ChangeSection(int id)
{
	bool isSet = false;
	if (CurrentSection == NULL)
		isSet = true;
	int screen_height = CGlobalVariable::GetInstance()->ScreenHeight;
	int screen_width = CGlobalVariable::GetInstance()->ScreenWidth;

	CurrentSection = Sections[id];
	float left, top, right, bottom;
	CurrentSection->GetSectionBoundary(left, top, right, bottom);
	if(isSet)
		CCamera::GetInstance()->SetCamBoundary(left, top, right-screen_width, bottom + screen_height);
	else
		CCamera::GetInstance()->MoveToSection(left, top, right - screen_width, bottom + screen_height);
}

LPSECTION CSectionManager::Get(unsigned int id)
{
	LPSECTION section = Sections[id];
	if(section == NULL)
		DebugOut(L"[ERROR] Failed to find section id: %d\n", id);
	return section;
}

CSection::CSection()
{
}
