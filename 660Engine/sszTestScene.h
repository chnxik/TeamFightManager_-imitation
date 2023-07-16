#pragma once
#include "sszScene.h"

namespace ssz
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}