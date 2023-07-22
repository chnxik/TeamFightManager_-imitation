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

// UI Component
#include "sszPanelUI.h"

// Resources
#include "sszResources.h"
#include "sszMaterial.h"

namespace ssz::object
{
	using namespace ssz::graphics;

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

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->GetComponent<Transform>();
			tr->SetPosition(pos);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, Vector3 scale, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->GetComponent<Transform>();
			tr->SetPosition(pos);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector3 pos, Vector3 scale, Vector3 rotate, enums::eLayerType layer)
		{
			T* gameObj = new T();
			Transform* tr = gameObj->GetComponent<Transform>();
			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}
#pragma endregion
#pragma region UI Instantiate
		template <typename T>
		static __forceinline T* InstantiateUI(enums::eLayerType layer, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);

			Transform* tr = gameObj->GetComponent<Transform>();

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, enums::eLayerType layer, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);

			Transform* tr = gameObj->GetComponent<Transform>();

			tr->SetPosition(pos);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();


			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, enums::eLayerType layer, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);

			Transform* tr = gameObj->GetComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, Vector3 rotate, enums::eLayerType layer, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);

			Transform* tr = gameObj->GetComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);

			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(layer, gameObj);

			gameObj->Initialize();

			return gameObj;
		}
#pragma endregion
#pragma region ChildUI Instantiate
		template <typename T>
		static __forceinline T* InstantiateUI(UIObject* pParentUI,const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);
			
			PanelUI* Panel = pParentUI->GetComponent<PanelUI>();
			assert(Panel);
			
			// UIObject 부모자식 설정
			Panel->AddChildUI(gameObj);
			gameObj->SetState(pParentUI->GetState());

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, UIObject* pParentUI, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);


			PanelUI* Panel = pParentUI->GetComponent<PanelUI>();
			assert(Panel);

			// UIObject 부모자식 설정
			Panel->AddChildUI(gameObj);
			gameObj->SetState(pParentUI->GetState());
			
			Transform* tr = gameObj->GetComponent<Transform>();
			
			tr->SetPosition(pos);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, UIObject* pParentUI, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);

			PanelUI* Panel = pParentUI->GetComponent<PanelUI>();
			assert(Panel);

			// UIObject 부모자식 설정
			Panel->AddChildUI(gameObj);
			gameObj->SetState(pParentUI->GetState());

			Transform* tr = gameObj->GetComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetScale(scale);

			gameObj->Initialize();

			return gameObj;
		}

		template <typename T>
		static __forceinline T* InstantiateUI(Vector3 pos, Vector3 scale, Vector3 rotate, UIObject* pParentUI, const std::wstring& objKey)
		{
			T* gameObj = new T(objKey);
			
			PanelUI* Panel = pParentUI->GetComponent<PanelUI>();
			assert(Panel);

			// UIObject 부모자식 설정
			Panel->AddChildUI(gameObj);
			gameObj->SetState(pParentUI->GetState());

			Transform* tr = gameObj->GetComponent<Transform>();

			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);

			gameObj->Initialize();

			return gameObj;
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