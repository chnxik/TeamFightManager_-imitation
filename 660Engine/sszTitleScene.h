#pragma once
#include "sszScene.h"

namespace ssz
{
	class UIObject;

	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void GameLoad();

		void ExitProgram();

	private:
	};
}