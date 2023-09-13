#pragma once
#include "CommonObjHeader.h"
#include "sszTeam.h"
#include "sszPilot.h"
#include "sszChamp.h"

namespace ssz
{
	class TeamList;
	class PilotList;
	class ChampList;
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

		static Team* GetTeam(const std::wstring& key);
		static Pilot* GetPilot(const std::wstring& key);
		static Champ* GetChamp(const std::wstring& key);

		static TeamList* GetTeamList() { return gTeamList; }		// 팀 리스트
		static PilotList* GetPilotList() { return gPilotList; }		// 파일럿 리스트
		static ChampList* GetChampList() { return gChampList; }		// 챔프 리스트

		// 발사체
		static Projectile* GetProjectile();

		// 이펙트
		static Effect* GetEffectObj();

		// 씬 관리
		static void SceneClear(); // Scene Exit 호출

		static Champ* AddChampScene(eLayerType eType, const std::wstring& ChampKey,Vector3 Pos);

	private:
		static const RECT mStadiumSize;
		static float mGameTime;

		static Cursor* mCursor;
		static GameObject* mMainCamera;

		static TeamList* gTeamList;
		static PilotList* gPilotList;
		static ChampList* gChampList;

		static vector<Projectile*>	vProjectilePool;
		static vector<Effect*>		vEffectPool;
		
		// Player Data

	public:
		void SetPlayerTeamName(const std::wstring& name);

	private:
		static Team* gPlayerTeam;
		// 코치

		static UINT mGold;	// 소지금

		
	};
}