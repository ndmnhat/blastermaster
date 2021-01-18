#include "Section.h"
#include <stdexcept>
CSectionManager* CSectionManager::_instance = NULL;

void CSectionManager::Add(int id, LPSECTION Section)
{
	Sections[id] = Section;
}

int CSectionManager::GetObjectSectionID(LPGAMEOBJECT Object)
{
	if (Object != NULL)
	{
		for (int i = 0; i < Sections.size(); ++i)
		{
			try
			{
				if (Sections.at(i) != NULL)
				{
					float left, top, right, bottom;
					float Oleft, Otop, Oright, Obottom;
					Sections.at(i)->GetSectionBoundary(left, top, right, bottom);
					Object->GetBoundingBox(Oleft, Otop, Oright, Obottom);
					if (!(Oleft >= right || Oright <= left || Otop <= bottom || Obottom >= top))
						return i;
				}
			}
			catch (const std::out_of_range& e)
			{
				continue;
			}
		}
	}
	return 0;
}

void CSectionManager::ChangeSection(int id, bool isSet)
{
	if (CurrentSection == NULL)
		isSet = true;
	int screen_height = CGlobalVariable::GetInstance()->ScreenHeight;
	int screen_width = CGlobalVariable::GetInstance()->ScreenWidth;

	CurrentSection = Sections[id];
	CurrentSectionID = id;
	float left, top, right, bottom;
	CurrentSection->GetSectionBoundary(left, top, right, bottom);
	if(isSet)
		CCamera::GetInstance()->SetCamBoundary(left, top, right - screen_width, bottom + screen_height);
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
