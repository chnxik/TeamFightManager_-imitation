#pragma once
#include "sszLayer.h"

#include "sszSceneManager.h"
#include "sszScene.h"

// Object
#include "sszGameObject.h"
#include "sszUIObject.h"

// Component
#include "sszTransform.h"
#include "sszRenderer.h"

// Resources
#include "sszResources.h"
#include "sszMaterial.h"

namespace ssz::object
{
	using namespace ssz::graphics;

	// Ȱ��������Ʈ �Ǵ�
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
#pragma region ChildUI Instantiate
		template <typename T>
		static __forceinline T* InstantiateUI(UIObject* pParentUI,bool UseCollider)
		{
			T* gameObj = new T();
			UIObject* UIObj = dynamic_cast<UIObject>(gameObj);
			assert(UIObj);

			Transform* tr = UIObj->AddComponent<Transform>();
			
			if (UseCollider)
				UIObj->AddComponent<Collider2D>()->Initialize();

			UIObj->AddParentUI(pParentUI);
			UIObj->SetState(pParentUI->GetState());

			return UIObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, UIObject* pParentUI, bool UseCollider)
		{
			T* gameObj = new T();
			UIObject* UIObj = dynamic_cast<UIObject>(gameObj);
			assert(UIObj);

			Transform* tr = UIObj->AddComponent<Transform>();

			tr->SetPosition(pos);

			if (UseCollider)
				UIObj->AddComponent<Collider2D>()->Initialize();

			UIObj->AddParentUI(pParentUI);
			UIObj->SetState(pParentUI->GetState());

			return UIObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, UIObject* pParentUI, bool UseCollider)
		{
			T* gameObj = new T();
			UIObject* UIObj = dynamic_cast<UIObject*>(gameObj);
			assert(UIObj);

			Transform* tr = UIObj->AddComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetScale(scale);

			if (UseCollider)
				UIObj->AddComponent<Collider2D>()->Initialize();

			UIObj->AddParentUI(pParentUI);
			UIObj->SetState(pParentUI->GetState());

			return UIObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, Vector3 rotate, UIObject* pParentUI, bool UseCollider)
		{
			T* gameObj = new T();
			UIObject* UIObj = dynamic_cast<UIObject>(gameObj);
			assert(UIObj);

			Transform* tr = UIObj->AddComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);

			if (UseCollider)
				UIObj->AddComponent<Collider2D>()->Initialize();

			UIObj->AddParentUI(pParentUI);
			UIObj->SetState(pParentUI->GetState());

			return UIObj;
		}
#pragma endregion 


	// Material
		static __forceinline std::shared_ptr<Material> LoadMaterial(const std::wstring& MaterialKey, const std::wstring& ShaderKey, const std::wstring& TextureKey, graphics::eRenderingMode type)
		{
			std::shared_ptr<Material> NewMaterial = Resources::Find<Material>(MaterialKey);

			if (nullptr == NewMaterial)
			{
				NewMaterial = std::make_shared<Material>();
				NewMaterial->SetMaterial(ShaderKey, TextureKey, type);
				Resources::Insert(MaterialKey, NewMaterial);
			}

			return NewMaterial;
		}
	 
	// Destory

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(ssz::GameObject::eState::Dead);
	}
}