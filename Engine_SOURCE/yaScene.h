#pragma once
#include "yaEntity.h"
#include "yaGameObject.h"

namespace ya
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

	public:
		std::vector<GameObject*> mGameObjects;
	};

}