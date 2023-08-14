#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class TeamList
	{
	public:
		TeamList();
		~TeamList();

		void Initialize();

		Team* GetTeam(const std::wstring& key);

	private:
		std::map<std::wstring, Team*> mTeamMap;
	};
}