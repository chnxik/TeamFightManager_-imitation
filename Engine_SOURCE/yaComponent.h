#pragma once
#include "yaEntity.h"


namespace ya
{
	using namespace ya::enums;

	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		const eComponentType mType;

	};
}
