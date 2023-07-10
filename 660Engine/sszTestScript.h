#pragma once
#include <sszScript.h>

namespace ssz
{
	class TestScript : public Script
	{
	public:
		TestScript();
		virtual ~TestScript();

		virtual void Update() override;

	private:
		float facc;
		bool bDead;
	};
}