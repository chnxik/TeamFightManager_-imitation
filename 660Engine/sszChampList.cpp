#include "sszChampList.h"

#include "sszScript_Archer.h"
#include "sszScript_Knight.h"

namespace ssz
{
	ChampList::ChampList()
	{
	}
	
	ChampList::~ChampList()
	{
		std::map<std::wstring, Champ*>::iterator iter = mChampMap.begin();

		while (iter != mChampMap.end())
		{
			delete iter->second;
			iter = mChampMap.erase(iter);
		}
	}

	void ChampList::Initialize()
	{
		Champ* Archer = object::Instantiate<Champ>();
		Archer->SetChampScript(Archer->AddComponent<Script_Archer>());
		mChampMap.insert(make_pair(ARCHER, Archer));

		Champ* Knight = object::Instantiate<Champ>();
		Knight->SetChampScript(Knight->AddComponent<Script_Knight>());
		mChampMap.insert(make_pair(KNIGHT, Knight));
	}

	Champ* ChampList::GetChamp(const std::wstring& key)
	{
		std::map<std::wstring, Champ*>::iterator iter = mChampMap.find(key);

		if (iter != mChampMap.end())
			return iter->second;

		return nullptr;
	}
}