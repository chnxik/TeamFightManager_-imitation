#pragma once
#include "sszScene.h"

namespace ssz
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		GameObject* TestObject;
	};
}