#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team
	{
	public:
		Team();
		virtual ~Team();

		void InitTeamInfo(std::wstring TeamName, std::shared_ptr<Texture> TeamIcon);


		std::wstring GetTeamName() { return mTeamName; }
		std::shared_ptr<Texture>  GetTeamIcon() { return mTeamIcon;	}

	private:
		std::wstring mTeamName;					// 팀 이름
		std::shared_ptr<Texture> mTeamIcon;		// 팀 아이콘
		// 팀 전적
		
		// 팀별 챔피언 정보 (챔피언 리스트에서 받아온다)
		// 선택횟수
		// 승리
		// 패배
		// 승률
		// 평점
		
		// 보유중인 선수 Pilot Map

	};
}