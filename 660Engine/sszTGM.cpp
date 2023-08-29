#include "sszTGM.h"

#include "sszChampList.h"
#include "sszPilotList.h"
#include "sszTeamList.h"
#include "sszCursor.h"
#include "sszProjectile.h"

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

		delete mMainCamera;

		delete mCursor;

		for (Projectile* gameObj : vProjectilePool)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
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