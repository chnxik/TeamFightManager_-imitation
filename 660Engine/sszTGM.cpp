#include "sszTGM.h"

#include "sszChampList.h"
#include "sszPilotList.h"
#include "sszTeamList.h"
#include "sszCursor.h"

namespace ssz
{
	TeamList* TGM::gTeamList = nullptr;
	PilotList* TGM::gPilotList = nullptr;
	ChampList* TGM::gChampList = nullptr;

	Cursor* TGM::mCursor = nullptr;

	void TGM::Initialize()
	{
		mCursor = new Cursor(); 

		gChampList = new ChampList();
		gPilotList = new PilotList();
		gTeamList = new TeamList();

		mCursor->Initialize();
		gChampList->Initialize();
		gPilotList->Initialize();
		gTeamList->Initialize();
	}

	void TGM::Release()
	{
		delete gChampList;
		delete gPilotList;
		delete gTeamList;

		delete mCursor;
	}

	Team* TGM::GetTeam(const std::wstring& key)
	{
		return gTeamList->GetTeam(key);;
	}

	Pilot* TGM::GetPilot(const std::wstring& key)
	{
		return gPilotList->GetPilot(key);
	}

	Champ* TGM::GetChamp(const std::wstring& key)
	{
		return gChampList->GetChamp(key);
	}

	void TGM::SceneClear()
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		
		ActiveScene->Clear(eLayerType::Cursor);
		ActiveScene->Clear(eLayerType::Player);
		ActiveScene->Clear(eLayerType::PlayerInteraction);
		ActiveScene->Clear(eLayerType::Enemy);
		ActiveScene->Clear(eLayerType::EnemyInteraction);
	}

	Champ* TGM::AddChampScene(eLayerType eType, const std::wstring& ChampKey, Vector3 Pos)
	{
		Champ* champ = GetChamp(ChampKey);
		SceneManager::GetActiveScene()->AddGameObject(eType, champ);
		champ->ColObjSetLayer(eColObjType::ATKAREA);
		champ->GetComponent<Transform>()->SetPosition(Pos);

		return champ;
	}
}