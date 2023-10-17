#pragma once
#include "CommonHeader.h"

namespace ssz
{
	class Team;

	class League
	{
	public:
		enum class eRound
		{
			Round1,
			Round2,
			Round3,
			END
		};
		
		enum class eGroup
		{
			A,
			B,
			END
		};

		struct tGame
		{
			Team* RedTeam;
			Team* BlueTeam;
			
			UINT RedTeamTotalKill;
			UINT BlueTeamTotalKill;
		};

		League();
		~League();

		eRound GetCurRound() { return mCurRound; }
		Team* GetPlayerTeam() {	return mLeagueSchedule[(UINT)mCurRound][(UINT)eGroup::A].BlueTeam; }
		Team* GetEnemyTeam() { return mLeagueSchedule[(UINT)mCurRound][(UINT)eGroup::A].RedTeam; }
		tGame	GetGame(eRound round, eGroup group) { return mLeagueSchedule[(UINT)round][(UINT)group]; }

		void RoundExit();

		void NextRound();
		
		void CreateNewEntry();

	private:
		eRound mCurRound;
		tGame mLeagueSchedule[(UINT)eRound::END][(UINT)eGroup::END];

		std::queue<Team*> mEntry;
		
	};
}