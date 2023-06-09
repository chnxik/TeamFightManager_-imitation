#include "yaGameObject.h"
#include "yaRenderer.h"
#include "yaGraphicDevice_Dx11.h"


namespace ya
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