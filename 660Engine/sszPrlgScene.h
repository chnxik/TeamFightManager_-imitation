#pragma once
#include "sszScene.h"

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

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		std::vector<GameObject*> CutScenes;
		UINT CutSceneIdx;
	};
}