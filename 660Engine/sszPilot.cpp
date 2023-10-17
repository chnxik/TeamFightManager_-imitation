#pragma once
#include "CommonHeader.h"

#include "sszPilot.h"
#include "sszTeam.h"
#include "sszChamp.h"

namespace ssz
{
	Pilot::Pilot()
		: mTeam(nullptr)
		, iPilotATK(0)
		, iPilotDEF(0)
		, iPilotAge(0)
		, mRegistedChamp(nullptr)
	{
	}

	Pilot::~Pilot()
	{
	}
	
	void Pilot::Initialize()
	{
	}
	
	void Pilot::Update()
	{
	}
	
	void Pilot::LateUpdate()
	{
	}
	
	void Pilot::Render()
	{
	}
	
	void Pilot::SetPilotName(std::wstring PilotName)
	{
		mPilotName = PilotName;
	}

	void Pilot::SetPilotData(UINT ATK, UINT DEF, UINT AGE)
	{
		iPilotATK = ATK;
		iPilotDEF = DEF;
		iPilotAge = AGE;
	}
	void Pilot::RegistTeam(Team* _Team)
	{
		mTeam = _Team;
	}
	
	void Pilot::RegistChamp(Champ* _Champ)
	{
		mRegistedChamp = _Champ;
		_Champ->RegistPilot(this);
	}
	
	void Pilot::ResetSetting()
	{
		mRegistedChamp->ResetInfo();
		mRegistedChamp = nullptr;
	}
	
	std::wstring Pilot::GetTeamName()
	{
		return mTeam->GetTeamName();
	}
}