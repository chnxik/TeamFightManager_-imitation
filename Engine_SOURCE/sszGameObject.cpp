#include "sszGameObject.h"
#include "sszRenderer.h"
#include "sszGraphicDevice_Dx11.h"


namespace ssz
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		
		
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// 공 움직임 구현
		
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render()
	{
	}
}