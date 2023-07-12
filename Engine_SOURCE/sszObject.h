#pragma once
#include "sszLayer.h"
#include "sszGameObject.h"
#include "sszScene.h"
#include "sszSceneManager.h"
#include "sszTransform.h"

namespace ssz::object
{
	// 활성오브젝트 판단
	static __forceinline bool IsValid(GameObject*& pTarget)
	{
		if (nullptr == pTarget)
		{
			return false;
		}
		else if (pTarget->IsDead())
		{
			pTarget = nullptr;
			return false;
		}

		return true;
	}

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetLocalPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetLocalPosition(pos);
		tr->SetLocalScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetLocalPosition(pos);
		tr->SetLocalRotation(rotate);
		tr->SetLocalScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(ssz::GameObject::eState::Dead);
	}
}