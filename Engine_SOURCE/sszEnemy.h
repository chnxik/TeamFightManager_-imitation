#pragma once
#include "sszCircle.h"

namespace ssz
{
	class Enemy : public Circle
	{
	public:
		enum eMagnet
		{
			ON,
			OFF
		};

		Enemy();
		virtual ~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		bool IsMagnet();
		void SetMagnet(Circle* Target);

	private:
		eMagnet mMagnet;
		Circle* mTarget;
	};
}