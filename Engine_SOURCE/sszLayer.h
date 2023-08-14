#pragma once
#include "sszGameObject.h"


namespace ssz
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();
		virtual void SetLayerType(eLayerType eType) { mType = eType; }

		virtual void clear();

		void AddGameObject(GameObject* gameObj);
		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}

	private:
		eLayerType mType;
		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mGarbageObjects;
	};
}