#pragma once
#include "sszEntity.h"
#include "sszLayer.h"

namespace ssz
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();
		virtual void Erase(eLayerType type);

		virtual void Clear(eLayerType type);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(eLayerType type, GameObject* gameObj);

		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (Layer* layer : mLayers)
			{
				auto gameObjs = layer->GetGameObjects();
				for (GameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						findObjs.push_back(buff);
				}
			}

			return findObjs;
		}
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		void ChangeScene(const std::wstring& SceneName);

	private:
		std::vector<Layer> mLayers;
	};
}