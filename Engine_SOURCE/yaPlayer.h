#pragma once
#include "yaCircle.h"

using namespace ya::math;

namespace ya
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
	};
}
