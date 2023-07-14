#pragma once
#include "sszScene.h"

namespace ssz
{
	class BanPickScene : public Scene
	{
	public:
		BanPickScene();
		virtual ~BanPickScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};
}

