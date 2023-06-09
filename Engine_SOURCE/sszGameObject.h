#pragma once
#include "sszEntity.h"
#include "sszComponent.h"
#include "sszConstantBuffer.h"


namespace ssz
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		eState mState;
	};

}