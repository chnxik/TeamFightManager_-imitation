#include "sszGameObject.h"
#include "sszRenderer.h"
#include "sszGraphicDevice_Dx11.h"
#include "sszTransform.h"

namespace ssz
{

	GameObject::GameObject()
		: mState(eState::Active)
		, mLayerType(eLayerType::End)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}

	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}

		for (Script* script : mScripts)
		{
			script->Render();
		}
	}

	void GameObject::SetParent(GameObject* parent)
	{
		Transform* parentTransform = parent->GetComponent<Transform>();
		GetComponent<Transform>()->SetParent(parentTransform);
	}
}