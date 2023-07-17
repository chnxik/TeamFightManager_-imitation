#pragma once
#include "sszComponent.h"

class UIObject;

namespace ssz
{
	class UIComponent : public Component
	{
	public:
		UIComponent();
		virtual ~UIComponent();

		virtual void Initialize() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual void BindConstantBuffer() {};

		virtual void MouseLbtnDown() {};
		virtual void MouseLbtnUp() {};
		virtual void MouseLbtnClicked() {};
		virtual void MouseOn() {};

		UIObject* GetOwnerUI() { return mOwnerUI; }
		virtual void SetOwner(GameObject* owner) override;

	private:
		UIObject* mOwnerUI;
	};
}