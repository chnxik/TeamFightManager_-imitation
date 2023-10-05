#include "sszPilot.h"
#include "CommonObjHeader.h"
#include "sszTeam.h"

namespace ssz
{
	Pilot::Pilot()
		: mTeam(nullptr)
		, iPilotATK(0)
		, iPilotDEF(0)
		, iPilotAge(0)
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
}