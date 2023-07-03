#pragma once
#include "..\Engine_SOURCE\sszScene.h"
#include "..\Engine_SOURCE\sszGameObject.h"

namespace ssz
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		GameObject* Title;
	};
}