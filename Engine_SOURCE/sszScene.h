#pragma once
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

	public:
		std::vector<GameObject*> mGameObjects;
		float acc;
		float position;
	};

}