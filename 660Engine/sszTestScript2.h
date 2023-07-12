#pragma once
#include <sszScript.h>

namespace ssz
{
	class TestScript2 : public Script
	{
	public:
		TestScript2();
		virtual ~TestScript2();

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