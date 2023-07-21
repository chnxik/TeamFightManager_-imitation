#pragma once
#include "sszEntity.h"

namespace ssz
{
	using namespace ssz::enums;
	using namespace ssz::math;

	class GameObject; // ������Ʈ�� �������ִ� ���ΰ�ü�� ��� ���� ���ӿ�����Ʈ Ŭ���� ���漱��
	class Component : public Entity
	{
	public:
		Component(eComponentType type); // �� ��ü�� � ������Ʈ Ÿ������ �����ܰ迡�� ����
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