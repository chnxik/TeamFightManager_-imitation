#pragma once
#include <sszScript.h>

namespace ssz
{
	class TestScript3 : public Script
	{
	public:
		TestScript3();
		virtual ~TestScript3();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetDefault();

	private:
		Vector3 OffsetPos;
		Vector3 OffsetScale;
		Vector3 OffsetRotation;

		float fradius;
		float fradiusx;
		float fradiusy;
	};
}