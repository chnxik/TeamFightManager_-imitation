#include "sszScene.h"
#include "sszSceneManager.h"

namespace ssz
{
	Scene::Scene()
	{
		mLayers.resize((int)ssz::enums::eLayerType::End);

		int i = 0;

		for (Layer& layer : mLayers)
		{
			layer.SetLayerType((eLayerType)i++);
		}
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destory();
		}
	}

	void Scene::Clear(eLayerType type)
	{
		mLayers[(UINT)type].clear();
	}

	void Scene::Erase(eLayerType type, GameObject* obj)
	{
		mLayers[(UINT)type].EraseGameObject(obj);
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);
	}
	void Scene::ChangeScene(const std::wstring& SceneName)
	{
		SceneManager::LoadScene(SceneName);
	}
}