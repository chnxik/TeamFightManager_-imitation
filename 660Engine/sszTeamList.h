#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team;

	class TeamList
	{
	public:
		TeamList();
		~TeamList();

		void Initialize();

	private:
		Team* mTeamList[4];
	};
}