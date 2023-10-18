#pragma once
#include "sszTexture.h"

namespace ssz
{
	class Pilot;

	class Team
	{
	public:
		Team();
		virtual ~Team();

		void InitTeamInfo(std::wstring TeamName, std::shared_ptr<Texture> TeamIcon);
		void SetTeamName(std::wstring TeamName);
		void SetIconTex(std::wstring TexKey);

		std::wstring GetTeamName() { return mTeamName; }
		std::shared_ptr<Texture>  GetTeamIcon() { return mTeamIcon;	}
		std::wstring GetTeamIconTexKey() { return mTeamIconTexKey; }

		void RegistPilot(Pilot* pilot);

		const UINT* GetTKScoreAddress() { return &mCurGameTKScore; }
		void AddKillScore() { mCurGameTKScore++; }
		void ResetGameInfo() { mCurGameTKScore = 0; }

		std::vector<Pilot*> GetPilotList() { return mPilotList; }

	private:
		std::wstring mTeamName;					// 팀 이름
		std::shared_ptr<Texture> mTeamIcon;		// 팀 아이콘
		std::wstring mTeamIconTexKey;
		// 팀 전적
		UINT mCurGameTKScore;

		// 팀별 챔피언 정보 (챔피언 리스트에서 받아온다)
		// 선택횟수
		// 승리
		// 패배
		// 승률
		// 평점
		
		// 보유중인 선수 Pilot Map
		std::vector<Pilot*> mPilotList;

	};
}