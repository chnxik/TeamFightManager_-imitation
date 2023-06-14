#pragma once
#include "sszCircle.h"

using namespace ssz::math;

namespace ssz
{
	class Player : public Circle
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetFinalColor(float R, float G, float B) { mFinalColor = Vector4(R, G, B, 1.f); }
		void SetFinalColor(Vector4 Color) { mFinalColor = Color; }
		void GetEffect() { mfColorAcc = 1.f; }
		void SetFinalRadius(float radius);
		void AddRadius(float radius);

	private:
		Vector4 mColorChange;
		Vector4 mFinalColor;
		float	mFinalRadius;
		float	mfColorAcc;
	};
}
