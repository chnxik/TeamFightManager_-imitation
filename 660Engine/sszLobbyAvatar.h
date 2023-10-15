#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class LobbyAvatar : public GameObject
    {
	public:
		LobbyAvatar();
		virtual ~LobbyAvatar();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		GameObject* mHair;
		GameObject* mGlasses;

    };
}

