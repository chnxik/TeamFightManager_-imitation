#include "sszGuageScript.h"

namespace ssz
{
	GuageScript::GuageScript()
		: mType(eGuageType::END)
		, mMax(0.f)
		, mValue(nullptr)
		, fRatio(0.f)
	{
	}

	GuageScript::~GuageScript()
	{
	}

	void GuageScript::Initialize()
	{
	}

	void GuageScript::Update()
	{
	}

	void GuageScript::LateUpdate()
	{
	}

	void GuageScript::Render()
	{
	}

	void GuageScript::Binds()
	{
	}

	void GuageScript::BindsClear()
	{
	}
	
	void GuageScript::SetValue(int Max, int* ValueAddress)
	{
	}
	
	void GuageScript::SetValue(float Max, float* ValueAddress)
	{
	}
}