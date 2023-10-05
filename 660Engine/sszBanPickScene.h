#pragma once
#include "sszScene.h"

namespace ssz
{
	class PlayerCardSlot;
	class BanPickWindow;
	class BattleHeader;

	class BanPickScene : public Scene
	{
	public:
		enum class eBanPickPhase
		{
			SceneIn,	// 씬 입장
			Ban,		// 금지단계
			Pick,		// 선택단계
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

		float mAccTime;
	};
}

