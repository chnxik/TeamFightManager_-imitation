#pragma once
#include "sszScene.h"
#include "CommonDefine.h"
#include "GameEnums.h"

namespace ssz
{
	class PlayerCardSlot;
	class BanPickWindow;
	class BattleHeader;
	class BanLine;

	class BanPickScene : public Scene
	{
	public:
		enum class eBanPickPhase
		{
			SceneIn1,	// 씬 입장
			SceneIn2,
			BP_1,	// 금지단계 1
			BP_2,	// 금지단계 2
			PP_1,	// 선택단계 1
			PP_2,	// 선택단계 2
			PP_3,	// 선택단계 3
			PP_4,	// 선택단계 4
			SecenOut
		};
		
		BanPickScene();
		virtual ~BanPickScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void Reset();

	private:
		eBanPickPhase mPhase;
		BattleHeader* mBattleHeader;
		PlayerCardSlot* mPlayerSlot[(UINT)eTeamColor::End][2];
		BanPickWindow* mBanPickWindow;
		BanLine* mBanLine;

		float mAccTime;
	};
}

