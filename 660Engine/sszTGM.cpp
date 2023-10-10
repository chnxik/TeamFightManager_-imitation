#pragma once
#include "sszTGM.h"

#include "sszTeam.h"
#include "sszPilot.h"
#include "sszChamp.h"

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

	std::map<std::wstring, Team*> TGM::gTeamList;
	std::map<std::wstring, Pilot*> TGM::gPilotList;
	std::map<std::wstring, Champ*> TGM::gChampList;

	Cursor* TGM::mCursor = nullptr;
	GameObject* TGM::mMainCamera = nullptr;

	std::vector<Projectile*> TGM::vProjectilePool;
	std::vector<Effect*> TGM::vEffectPool;

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
		gChampList.insert(std::make_pair(ARCHER, Archer));

		Champ* Knight = object::Instantiate<Champ>();
		Knight->SetChampScript(Knight->AddComponent<Script_Knight>());
		gChampList.insert(std::make_pair(KNIGHT, Knight));

		return true;
	}

	bool TGM::PilotInitialize()
	{
		if (FileManager::OpenLoadFile(L"PilotName.txt") == S_OK)
		{
			// 데이터 불러오기
			std::wstring PilotName = {};

			while (FileManager::DataLoad(PilotName, L'\n') == S_OK)
			{
				Pilot* NewPilot = new Pilot();
				NewPilot->SetPilotName(PilotName);
				gPilotList.insert(std::make_pair(PilotName, NewPilot));
			}

			FileManager::CloseLoadFile();
			return true;
		}

		assert(nullptr);


		// 기초 선수데이터 생성
		
		return true;
	}

	bool TGM::TeamInitialize(std::vector<Pilot*> pilotlist)
	{
		if (0 < gTeamList.size())
			return false;

		// 플레이어 팀 선수 등록
		std::vector<Pilot*>::iterator PilotIter = pilotlist.begin();

		gPlayerTeam->RegistPilot((*PilotIter++));
		gPlayerTeam->RegistPilot((*PilotIter++));

		// 플레이어 제외 팀 로고 랜덤 생성
		std::wstring PlayerTeamTexkey = gPlayerTeam->GetTeamIconTexKey();
		std::vector<std::wstring> TeamLogoTex;

		for (int i = 1; i <= 10; ++i)
		{
			std::wstring Texkey = L"TeamLogoTex_" + std::to_wstring(i);
			
			if (Texkey == PlayerTeamTexkey)
				continue;

			TeamLogoTex.emplace_back(Texkey);
		}
		
		// 팀 로고 셔플
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(TeamLogoTex.begin(), TeamLogoTex.end(), gen);
		
		FileManager::OpenLoadFile(L"TeamName.txt");
		
		for (int i = 0; i < 7; i++)
		{
			Team* NewTeam = new Team;
			std::wstring TeamName = {};
			FileManager::DataLoad(TeamName, L'\n');

			NewTeam->SetIconTex(TeamLogoTex[i]);
			NewTeam->SetTeamName(TeamName);

			NewTeam->RegistPilot((*PilotIter++));
			NewTeam->RegistPilot((*PilotIter++));

			gTeamList.insert(std::make_pair(TeamName, NewTeam));
		}

		FileManager::CloseLoadFile();

		return true;
	}

	Team* TGM::GetTeam(const std::wstring& key)
	{

		std::map<std::wstring, Team*>::iterator iter = gTeamList.find(key);

		if (iter != gTeamList.end())
			return iter->second;

		else if (gPlayerTeam->GetTeamName() == key)
			return gPlayerTeam;

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
		/* 저장 데이터 순서
		플레이어 팀 이름
		플레이어 팀 로고 텍스쳐키
		전체팀 정보(플레이어 팀 제외)
		전체 파일럿 정보 (선수이름, 소속팀, 나이, 능력치)
		
		*/
		
		// Player Team 정보
		FileManager::DataSave(gPlayerTeam->GetTeamName(), L'\n');
		FileManager::DataSave(gPlayerTeam->GetTeamIconTexKey(), L'\n');

		// 전체 팀 정보 저장 (플레이어팀 제외)
		std::map<std::wstring, Team*>::iterator TeamIter = gTeamList.begin();
		for (; TeamIter != gTeamList.end(); TeamIter++)
		{
			Team* tmp = TeamIter->second;
			std::wstring TeamData =
				tmp->GetTeamName() // 팀 이름
				+ L',' + tmp->GetTeamIconTexKey(); // 팀 아이콘 텍스쳐

			FileManager::DataSave(TeamData, '\n');
		}

		// Pilot 정보 저장
		std::map<std::wstring, Pilot*>::iterator PilotIter = gPilotList.begin();
		
		for (; PilotIter != gPilotList.end(); PilotIter++)
		{
			Pilot* tmp = PilotIter->second;
			std::wstring PilotData =
				tmp->GetPilotName() // 파일럿 이름
				+ L',' + tmp->GetTeamName() // 소속 팀 이름
				+ L',' + std::to_wstring(tmp->GetPilotAge()) // 파일럿 나이
				+ L',' + std::to_wstring(tmp->GetPilotATK()) // 파일럿 공격능력치
				+ L',' + std::to_wstring(tmp->GetPilotDEF()); // 파일럿 방어능력치
			
			FileManager::DataSave(PilotData, '\n');
		}

		// 다른 Team 정보

		// 전적 정보
		FileManager::CloseSaveFile();

		return true;
	}
	bool TGM::LoadData()
	{
		if (FileManager::OpenLoadFile(L"SaveFile.sav") == S_OK)
		{
			// 플레이어 데이터 로드
			std::wstring TeamName = {};
			std::wstring TeamIconTexKey = {};
			
			FileManager::DataLoad(TeamName, L'\n');
			FileManager::DataLoad(TeamIconTexKey, L'\n');

			gPlayerTeam->SetTeamName(TeamName);
			gPlayerTeam->SetIconTex(TeamIconTexKey);

			// 팀 정보 로드(생성)
			for (int i = 0; i < 7; i++)
			{
				Team* NewTeam = new Team;
				std::wstring TeamName = {};
				std::wstring TeamIconTexKey = {};
				FileManager::DataLoad(TeamName, L',');
				FileManager::DataLoad(TeamIconTexKey, L'\n');

				NewTeam->SetTeamName(TeamName);
				NewTeam->SetIconTex(TeamIconTexKey);

				gTeamList.insert(std::make_pair(TeamName, NewTeam));
			}

			// 전체 선수 데이터 로드
			for (int i = 0; i < 16; i++)
			{
				std::wstring PilotName = {};
				std::wstring HomeTeamName = {};
				int PilotATK = 0;
				int PilotDEF = 0;
				int PilotAge = 0;

				FileManager::DataLoad(PilotName, L',');
				FileManager::DataLoad(HomeTeamName, L',');
				FileManager::DataLoad(PilotAge, L',');
				FileManager::DataLoad(PilotATK, L',');
				FileManager::DataLoad(PilotDEF, L'\n');

				Pilot* LoadPilot = GetPilot(PilotName);
				LoadPilot->SetPilotData(PilotATK, PilotDEF, PilotAge);
				Team* HomeTeam = GetTeam(HomeTeamName);
				
				if (HomeTeam)	// 팀리스트에서 팀을 찾아온다
				{
					LoadPilot->RegistTeam(HomeTeam);
				}
				else // 없는 경우 플레이어팀.
				{
					LoadPilot->RegistTeam(gPlayerTeam);
				}
			}

			FileManager::CloseLoadFile();
			return true;
		}

		assert(nullptr);
		
		return false;
	}
}