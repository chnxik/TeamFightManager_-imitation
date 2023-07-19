#pragma once
#include "sszScene.h"

namespace ssz
{
	class StadiumScene : public Scene
	{
	public:
		StadiumScene();
		virtual ~StadiumScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* LineUpWin;
	};
}