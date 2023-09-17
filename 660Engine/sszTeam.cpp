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

	void Team::InitTeamInfo(const std::wstring& TeamName, std::shared_ptr<Texture> TeamLogo)
	{
		mTeamName = TeamName;
		mTeamLogo = TeamLogo;
	}

	std::shared_ptr<Texture> Team::GetTeamLogo()
	{
		return std::shared_ptr<Texture>();
	}
}
