#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team
	{
	public:
		Team();
		virtual ~Team();

		void SetTeamTex(const std::wstring& LogoTexKey);
		void SetTeamName(const std::wstring& name);

	private:
		std::wstring mTeamLogoTexKey;	// 팀 로고
		std::wstring mTeamName;					// 팀 이름
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