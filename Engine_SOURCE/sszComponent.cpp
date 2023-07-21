#include "sszComponent.h"

namespace ssz
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void ssz::Component::Initialize()
	{
	}

	void ssz::Component::Update()
	{
	}

	void ssz::Component::LateUpdate()
	{
	}

	void ssz::Component::Render()
	{
	}
	void Component::Binds()
	{
	}
}