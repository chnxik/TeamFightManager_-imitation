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

	private:
		Vector4 mColorChange;
	};
}
