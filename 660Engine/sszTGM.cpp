#pragma once
#include "sszTGM.h"

#include "sszChampList.h"
#include "sszPilotList.h"
#include "sszTeamList.h"
#include "sszCursor.h"
#include "sszProjectile.h"
#include "sszEffect.h"

namespace ssz
{
	const RECT	TGM::mStadiumSize{ -570, 190, 570, -396 }; // Left, Top, Right, Bottme
	float TGM::mGameTime = 0.f;

	TeamList* TGM::gTeamList = nullptr;
	PilotList* TGM::gPilotList = nullptr;
	ChampList* TGM::gChampList = nullptr;

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

		gChampList = new ChampList();
		gPilotList = new PilotList();
		gTeamList = new TeamList();

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
		gChampList->Initialize();
		gPilotList->Initialize();
		gTeamList->Initialize();

		gPlayerTeam = new Team();
	}

	void TGM::Release()
	{
		delete gChampList;
		delete gPilotList;
		delete gTeamList;

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

	Team* TGM::GetTeam(const std::wstring& key)
	{
		// return gTeamList->GetTeam(key);;
		return nullptr;
	}

	Pilot* TGM::GetPilot(const std::wstring& key)
	{
		return gPilotList->GetPilot(key);
	}

	Champ* TGM::GetChamp(const std::wstring& key)
	{
		return gChampList->GetChamp(key);
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
}