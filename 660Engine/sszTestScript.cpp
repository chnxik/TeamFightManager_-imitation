#include "sszTestScript.h"

#include "sszGameObject.h"
#include "sszObject.h"

#include "sszTime.h"

namespace ssz
{
	TestScript::TestScript()
		: facc(0.0f)
		, bDead(false)
	{
	}
	TestScript::~TestScript()
	{
	}

	void TestScript::Update()
	{
		if (!bDead)
		{
			if (facc > 5.f)
			{
				bDead = true;
				ssz::object::Destroy(GetOwner());
			}
			facc += (float)ssz::Time::DeltaTime();
		}
	}
}