#include "sszPilot.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Pilot::Pilot()
		: iPilotATK(0)
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
	
	void Pilot::CreatePilot(std::wstring Name, UINT ATK, UINT DEF, UINT AGE)
	{
		mPilotName = Name;
		iPilotATK = ATK;
		iPilotDEF = DEF;
		iPilotAge = AGE;
	}
}