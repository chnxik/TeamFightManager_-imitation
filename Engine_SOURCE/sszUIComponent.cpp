#include "sszUIComponent.h"
#include "sszUIObject.h"

namespace ssz
{
	UIComponent::UIComponent()
		: Component(eComponentType::UI)
		, mOwnerUI(nullptr)
	{
	}

	UIComponent::~UIComponent()
	{
	}

	void UIComponent::SetOwner(GameObject* owner)
	{
		mOwner = owner;
		mOwnerUI = dynamic_cast<UIObject*>(owner);
	};
}