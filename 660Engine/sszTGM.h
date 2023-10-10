#pragma once
#include "CommonHeader.h"

namespace ssz
{
	class TeamList;
	class PilotList;
	class ChampList;

	class Team;
	class Pilot;
	class Champ;

	class Cursor;
	class Projectile;
	class Effect;

	class TGM
	{
	public:
		static void Initialize();
		static void Release();

		// 공용 오브젝트
		static GameObject* GetCursor() { return (GameObject*)mCursor; }
		static GameObject* GetCamera() { return (GameObject*)mMainCamera; }
		static const RECT& GetStadiumSize() { return mStadiumSize; }
		static Vector3 GetStaidumPos()
		{
			return Vector3(
				(float)(mStadiumSize.left + (mStadiumSize.right - mStadiumSize.left) / 2.f), 
				(float)(mStadiumSize.bottom + (mStadiumSize.top - mStadiumSize.bottom) / 2.f), 0.f);
		}
		static Vector3 GetStadiumScale() 
		{
			return Vector3(
				(float)(mStadiumSize.right - mStadiumSize.left), 
				(float)(mStadiumSize.top - mStadiumSize.bottom), 0.f);
		}

		// 게임 정보
		static void	SetGameTime(float time) { mGameTime = time; }
		static float& GetGameTime() { return mGameTime; }

		static bool ChampInitialize();
		static bool PilotInitialize();
		static bool TeamInitialize(std::vector<Pilot*> pilotlist);

		static Team* GetTeam(const std::wstring& key);
		static Pilot* GetPilot(const std::wstring& key);
		static Champ* GetChamp(const std::wstring& key);

		static std::map<std::wstring, Team*> GetTeamList() { return gTeamList; }		// 팀 리스트
		static std::map<std::wstring, Pilot*> GetPilotList() { return gPilotList; }		// 파일럿 리스트
		static std::map<std::wstring, Champ*> GetChampList() { return gChampList; }		// 챔프 리스트

		// 발사체
		static Projectile* GetProjectile();

		// 이펙트
		static Effect* GetEffectObj();

		// 씬 관리
		static void SceneClear(); // Scene Exit 호출

		static Champ* AddChampScene(eLayerType eType, const std::wstring& ChampKey,Vector3 Pos);

		// 플레이어 정보
		static Team* GetPlayerTeam() { return gPlayerTeam; }

		static UINT GetPlayerGold() { return mGold; }
		static UINT GetYear() { return mYear; }
		static UINT GetMonth() { return mMonth; }
		static UINT GetWeek() { return mWeek; }

		// 데이터 관리
		static bool SaveData();
		static bool LoadData();

	private:
		static const RECT mStadiumSize;		// 경기장 크기
		static float mGameTime;				// 경기 시간

		static Cursor* mCursor;				// 커서
		static GameObject* mMainCamera;		// 카메라

		static std::map<std::wstring,Team*> gTeamList;		// 상대 팀 목록
		static std::map<std::wstring,Pilot*> gPilotList;		// 전체 선수 목록
		static std::map<std::wstring,Champ*> gChampList;		// 챔피언 목록

		static std::vector<Projectile*>	vProjectilePool;
		static std::vector<Effect*>		vEffectPool;

	private:
		// Player Data
		static Team* gPlayerTeam;

		// 날짜
		static UINT mYear;
		static UINT mMonth;
		static UINT mWeek;

		static UINT mGold;	// 소지금
	};
}