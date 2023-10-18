#pragma once
#include "sszScene.h"

namespace ssz
{
	class PlayerCardSlot;
	class ChampDataSlot;
	class BattleHeader;

	class IGStadiumScene : public Scene
	{
	public:
		enum class eGamePhase
		{
			SceneIn,
			Game,
			Finish,
			SceneOut,
		};
		IGStadiumScene();
		virtual ~IGStadiumScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		eGamePhase mCurPhase;
		BattleHeader* mBattleHeader;
		PlayerCardSlot* mPlayerSlot[(UINT)eTeamColor::End][2];
		ChampDataSlot* mChampDataSlot[(UINT)eTeamColor::End][2];

		UINT iGameCnt;
		float fAccTime;

	};
}