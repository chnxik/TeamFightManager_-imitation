#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class TeamList;
	class PilotList;
	class ChampList;
	class Cursor;

	class TGM
	{
	public:
		static void Initialize();
		static void Release();

		static GameObject* GetCursor() { return (GameObject*)mCursor; }

		static Team* GetTeam(const std::wstring& key);
		static Pilot* GetPilot(const std::wstring& key);
		static Champ* GetChamp(const std::wstring& key);

		static TeamList* GetTeamList() { return gTeamList; }		// �� ����Ʈ
		static PilotList* GetPilotList() { return gPilotList; }		// ���Ϸ� ����Ʈ
		static ChampList* GetChampList() { return gChampList; }		// è�� ����Ʈ

		// �� ����
		static void SceneClear(); // Scene Exit ȣ��

		static Champ* AddChampScene(eLayerType eType, const std::wstring& ChampKey,Vector3 Pos);

	private:
		static Cursor* mCursor;

		static TeamList* gTeamList;
		static PilotList* gPilotList;
		static ChampList* gChampList;
	};
}