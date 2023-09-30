#pragma once
#include "sszTeam.h"
#include "CommonObjHeader.h"

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
	void Team::SetTeamName(std::wstring TeamName)
	{
		mTeamName = TeamName;
	}
	void Team::SetIconTex(std::wstring TexKey)
	{
		mTeamIcon = Resources::Find<Texture>(TexKey);
		mTeamIconTexKey = TexKey;
	}
	void Team::AddPilot(Pilot* pilot)
	{
		mPilotList.emplace_back(pilot);
	}
}
