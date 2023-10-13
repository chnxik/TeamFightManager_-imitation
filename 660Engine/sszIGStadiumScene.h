#pragma once
#include "sszScene.h"

namespace ssz
{

	class BattleHeader;

	class IGStadiumScene : public Scene
	{
	public:
		IGStadiumScene();
		virtual ~IGStadiumScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		BattleHeader* mBattleHeader;
	};
}