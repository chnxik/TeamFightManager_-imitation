#pragma once
#include "sszScene.h"
#include "CommonDefine.h"
#include "GameEnums.h"

namespace ssz
{
	class ChampSelectSlot;
	class PlayerCardSlot;
	class BanPickWindow;
	class BattleHeader;
	class BanLine;
	class Text;

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
			SceneOut
		};
		
		BanPickScene();
		virtual ~BanPickScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void NextPhase();

		void Reset();

	private:
		eBanPickPhase mPhase;
		BattleHeader* mBattleHeader;
		PlayerCardSlot* mPlayerSlot[(UINT)eTeamColor::End][2];
		ChampSelectSlot* mChampSlot[(UINT)eChamp::NONE];
		BanPickWindow* mBanPickWindow;
		BanLine* mBanLine;

		Text* mBanLineCenterText;
		Text* mBanLineSideText;

		float mAccTime;
	};
}

