#pragma once
#include "sszTGM.h"

#include "sszCursor.h"
#include "sszProjectile.h"
#include "sszEffect.h"

// ChampScript
#include "sszScript_Archer.h"
#include "sszScript_Knight.h"

namespace ssz
{
	const RECT	TGM::mStadiumSize{ -570, 190, 570, -396 }; // Left, Top, Right, Bottme
	float TGM::mGameTime = 0.f;

	map<std::wstring, Team*> TGM::gTeamList;
	map<std::wstring, Pilot*> TGM::gPilotList;
	map<std::wstring, Champ*> TGM::gChampList;

	Cursor* TGM::mCursor = nullptr;
	GameObject* TGM::mMainCamera = nullptr;

	vector<Projectile*> TGM::vProjectilePool;
	vector<Effect*> TGM::vEffectPool;

	// player
	Team* TGM::gPlayerTeam = nullptr;
	
	UINT TGM::mYear = 2023;
	UINT TGM::mMonth = 9;
	UINT TGM::mWeek = 3;


	UINT TGM::mGold = 200;

	void TGM::Initialize()
	{
		mCursor = new Cursor();

		mMainCamera = Instantiate<GameObject>();
		mMainCamera->SetName(L"MainCamera");
		mMainCamera->AddComponent<Camera>();
		mMainCamera->AddComponent<AudioListener>();
		
		ChampInitialize(); // Champ 설정
		PilotInitialize(); // Pilot 설정
		TeamInitialize(); // Team 설정

		for (int i = 0; i < 100; ++i)
		{
			Projectile* newproj = new Projectile();
			newproj->Initialize();
			vProjectilePool.push_back(newproj);
		}

		for (int i = 0; i < 3; ++i)
		{
			Effect* neweffect = new Effect();
			neweffect->Initialize();
			vEffectPool.push_back(neweffect);
		}

		mCursor->Initialize();
		

		gPlayerTeam = new Team();
	}

	void TGM::Release()
	{
		// ChampList
		
		std::map<std::wstring, Champ*>::iterator champiter = gChampList.begin();
		while (champiter != gChampList.end())
		{
			delete champiter->second;
			champiter = gChampList.erase(champiter);
		}

		// gPilotList

		std::map<std::wstring, Pilot*>::iterator pilotiter = gPilotList.begin();
		while (pilotiter != gPilotList.end())
		{
			delete pilotiter->second;
			pilotiter = gPilotList.erase(pilotiter);
		}

		// gTeamList

		std::map<std::wstring, Team*>::iterator teamiter = gTeamList.begin();
		while (teamiter != gTeamList.end())
		{
			delete teamiter->second;
			teamiter = gTeamList.erase(teamiter);
		}

		delete mMainCamera;

		delete mCursor;

		for (Projectile* gameObj : vProjectilePool)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
		
		for (Effect* gameObj : vEffectPool)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}

		delete gPlayerTeam;
	}

	bool TGM::ChampInitialize()
	{
		Champ* Archer = object::Instantiate<Champ>();
		Archer->SetChampScript(Archer->AddComponent<Script_Archer>());
		gChampList.insert(make_pair(ARCHER, Archer));

		Champ* Knight = object::Instantiate<Champ>();
		Knight->SetChampScript(Knight->AddComponent<Script_Knight>());
		gChampList.insert(make_pair(KNIGHT, Knight));

		return true;
	}

	bool TGM::PilotInitialize()
	{
		Pilot* NewPilot = object::Instantiate<Pilot>();

		return true;
	}

	bool TGM::TeamInitialize()
	{

		return true;
	}

	Team* TGM::GetTeam(const std::wstring& key)
	{

		std::map<std::wstring, Team*>::iterator iter = gTeamList.find(key);

		if (iter != gTeamList.end())
			return iter->second;

		return nullptr;
	}

	Pilot* TGM::GetPilot(const std::wstring& key)
	{
		std::map<std::wstring, Pilot*>::iterator iter = gPilotList.find(key);

		if (iter != gPilotList.end())
			return iter->second;

		return nullptr;
	}

	Champ* TGM::GetChamp(const std::wstring& key)
	{
		std::map<std::wstring, Champ*>::iterator iter = gChampList.find(key);

		if (iter != gChampList.end())
			return iter->second;

		return nullptr;
	}

	Projectile* TGM::GetProjectile()
	{
		Projectile* Proj = nullptr;

		while (Proj == nullptr)
		{
			for (Projectile* tmp : vProjectilePool)
			{
				if (tmp->IsProjCanUse())
				{
					Proj = tmp;
					break;
				}
			}
		}

		return Proj;
	}

	Effect* TGM::GetEffectObj()
	{
		Effect* Eff = nullptr;

		while (Eff == nullptr)
		{
			for (Effect* tmp : vEffectPool)
			{
				if (!(tmp->IsPlay()))
				{
					Eff = tmp;
					break;
				}
			}
		}

		return Eff;
	}

	void TGM::SceneClear()
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		
		ActiveScene->Clear(eLayerType::Cursor);
		ActiveScene->Clear(eLayerType::Camera);
		ActiveScene->Clear(eLayerType::Effect);
		ActiveScene->Clear(eLayerType::Player);
		ActiveScene->Clear(eLayerType::PlayerInteraction);
		ActiveScene->Clear(eLayerType::Enemy);
		ActiveScene->Clear(eLayerType::EnemyInteraction);
	}

	Champ* TGM::AddChampScene(eLayerType eType, const std::wstring& ChampKey, Vector3 Pos)
	{
		Champ* champ = GetChamp(ChampKey);
		SceneManager::GetActiveScene()->AddGameObject(eType, champ);
		champ->ColObjSetLayer(eColObjType::RANGE);
		champ->GetComponent<Transform>()->SetPosition(Pos);

		return champ;
	}
	bool TGM::SaveData()
	{
		FileManager::OpenSaveFile(L"SaveFile.sav");
		
		// 데이터 저장
		
		// Player Team 정보
		FileManager::DataSave(gPlayerTeam->GetTeamName(), L'\n');
		FileManager::DataSave(gPlayerTeam->GetTeamIconTexKey(), L'\n');

		// 다른 Team 정보

		// 전적 정보
		FileManager::CloseSaveFile();

		return true;
	}
	bool TGM::LoadData()
	{
		if (FileManager::OpenLoadFile(L"SaveFile.sav") == S_OK)
		{
			// 데이터 불러오기
			wstring TeamName = {};
			wstring TeamIconTexKey = {};
			
			FileManager::DataLoad(TeamName, L'\n');
			FileManager::DataLoad(TeamIconTexKey, L'\n');

			gPlayerTeam->SetTeamName(TeamName);
			gPlayerTeam->SetIconTex(TeamIconTexKey);

			FileManager::CloseLoadFile();
			return true;
		}

		assert(nullptr);
		
		return false;
	}
}