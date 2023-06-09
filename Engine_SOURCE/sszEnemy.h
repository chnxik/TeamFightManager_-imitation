#pragma once
#include "sszCircle.h"

namespace ssz
{
	class Enemy : public Circle
	{
	public:
		Enemy();
		virtual ~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	};
}