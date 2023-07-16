#pragma once
#include "sszLayer.h"
#include "sszGameObject.h"
#include "sszUIObject.h"
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

	
#pragma region GameObject Instantiate
		template <typename T>
		static __forceinline T* Instantiate(enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->AddComponent<Transform>();

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->AddComponent<Transform>();
			tr->SetPosition(pos);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, Vector3 scale, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->AddComponent<Transform>();
			tr->SetPosition(pos);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, Vector3 scale, Vector3 rotate, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->AddComponent<Transform>();
			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			return gameObj;
		}
#pragma endregion
	// Destory

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(ssz::GameObject::eState::Dead);
	}
}