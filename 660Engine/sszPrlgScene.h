#pragma once
#include "..\Engine_SOURCE\sszScene.h"

namespace ssz
{
	class PrlgScene : public Scene
	{
	public:
		PrlgScene();
		virtual ~PrlgScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		std::vector<GameObject*> CutScenes;
		UINT CutSceneIdx;
	};
}