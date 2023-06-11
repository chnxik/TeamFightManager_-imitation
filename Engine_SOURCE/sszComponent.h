#pragma once
#include "sszEntity.h"

namespace ssz
{
	using namespace ssz::enums;

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