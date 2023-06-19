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

		void AddGameObject(GameObject* gameObj);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}