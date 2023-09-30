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

		static bool ChampInitialize();
		static bool PilotInitialize();
		static bool TeamInitialize();

		static Team* GetTeam(const std::wstring& key);
		static Pilot* GetPilot(const std::wstring& key);
		static Champ* GetChamp(const std::wstring& key);

		static map<std::wstring, Team*> GetTeamList() { return gTeamList; }		// �� ����Ʈ
		static map<std::wstring, Pilot*> GetPilotList() { return gPilotList; }		// ���Ϸ� ����Ʈ
		static map<std::wstring, Champ*> GetChampList() { return gChampList; }		// è�� ����Ʈ

		// �߻�ü
		static Projectile* GetProjectile();

		// ����Ʈ
		static Effect* GetEffectObj();

		// �� ����
		static void SceneClear(); // Scene Exit ȣ��

		static Champ* AddChampScene(eLayerType eType, const std::wstring& ChampKey,Vector3 Pos);

		// �÷��̾� ����
		static Team* GetPlayerTeam() { return gPlayerTeam; }

		static UINT GetPlayerGold() { return mGold; }
		static UINT GetYear() { return mYear; }
		static UINT GetMonth() { return mMonth; }
		static UINT GetWeek() { return mWeek; }

		// ������ ����
		static bool SaveData();
		static bool LoadData();

	private:
		static const RECT mStadiumSize;		// ����� ũ��
		static float mGameTime;				// ��� �ð�

		static Cursor* mCursor;				// Ŀ��
		static GameObject* mMainCamera;		// ī�޶�

		static map<std::wstring,Team*> gTeamList;		// �� ���
		static map<std::wstring,Pilot*> gPilotList;		// ��ü ���� ���
		static map<std::wstring,Champ*> gChampList;		// è�Ǿ� ���

		static vector<Projectile*>	vProjectilePool;
		static vector<Effect*>		vEffectPool;

	private:
		// Player Data
		static Team* gPlayerTeam;

		// ��¥
		static UINT mYear;
		static UINT mMonth;
		static UINT mWeek;

		static UINT mGold;	// ������
	};
}