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
			SceneIn1,	// �� ����
			SceneIn2,
			BP_1,	// �����ܰ� 1
			BP_2,	// �����ܰ� 2
			PP_1,	// ���ôܰ� 1
			PP_2,	// ���ôܰ� 2
			PP_3,	// ���ôܰ� 3
			PP_4,	// ���ôܰ� 4
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

