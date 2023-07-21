#pragma once
#include "sszEntity.h"

namespace ssz
{
	using namespace ssz::enums;
	using namespace ssz::math;

	class GameObject; // 컴포넌트를 가지고있는 주인객체를 담기 위한 게임오브젝트 클래스 전방선언
	class Component : public Entity
	{
	public:
		Component(eComponentType type); // 이 객체가 어떤 컴포넌트 타입인지 생성단계에서 지정
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void Binds();

		GameObject* GetOwner() { return mOwner; }
		virtual void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
	
	protected:
		GameObject* mOwner;
	};
}