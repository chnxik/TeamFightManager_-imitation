#include "sszTeamList.h"

namespace ssz
{
	TeamList::TeamList()
	{
	}

	TeamList::~TeamList()
	{
		std::map<std::wstring, Team*>::iterator iter = mTeamMap.begin();

		while (iter != mTeamMap.end())
		{
			delete iter->second;
			iter = mTeamMap.erase(iter);
		}
	}

	void TeamList::Initialize()
	{

	}

	Team* TeamList::GetTeam(const std::wstring& key)
	{
		std::map<std::wstring, Team*>::iterator iter = mTeamMap.find(key);

		if (iter != mTeamMap.end())
			return iter->second;

		return nullptr;
	}
}