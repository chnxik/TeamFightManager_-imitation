#pragma once
#include "sszEngine.h"
#include "sszEntity.h"
#include "sszGameObject.h"

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

	private:
		GameObject* mPlayer;
		std::vector<GameObject*> mGameObjects;
	};
}