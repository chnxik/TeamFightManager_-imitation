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

		// ���� ������Ʈ
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

		// ���� ����
		static void	SetGameTime(float time) { mGameTime = time; }
		static float& GetGameTime() { return mGameTime; }

		static Team* GetTeam(const std::wstring& key);
		static Pilot* GetPilot(const std::wstring& key);
		static Champ* GetChamp(const std::wstring& key);

		static TeamList* GetTeamList() { return gTeamList; }		// �� ����Ʈ
		static PilotList* GetPilotList() { return gPilotList; }		// ���Ϸ� ����Ʈ
		static ChampList* GetChampList() { return gChampList; }		// è�� ����Ʈ

		// �߻�ü
		static Projectile* GetProjectile();

		// ����Ʈ
		static Effect* GetEffectObj();

		// �� ����
		static void SceneClear(); // Scene Exit ȣ��

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
		// ��ġ

		static UINT mGold;	// ������

		
	};
}