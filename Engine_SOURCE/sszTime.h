#pragma once
#include "sszEngine.h"

#define DT (float)ssz::Time::DeltaTime();

namespace ssz
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();

		static void TimeAcceleration(float ratio) { fAcceleration = ratio; }
		static void DefaultAcceleration() { fAcceleration = 1.f; }

		__forceinline static double DeltaTime() { return mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float fAcceleration;
	};
}
