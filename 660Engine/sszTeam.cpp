#pragma once
#include "sszTeam.h"


namespace ssz
{
	Team::Team()
	{
	}
	
	Team::~Team()
	{
	}

	void Team::InitTeamInfo(std::wstring TeamName, std::shared_ptr<Texture> TeamIcon)
	{
		mTeamName = TeamName;
		mTeamIcon= TeamIcon;
	}
}
