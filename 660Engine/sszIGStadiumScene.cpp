#include "sszIGStadiumScene.h"
#include "CommonHeader.h"

#include "sszTGM.h"
#include "sszBattleManager.h"
#include "sszLeague.h"

#include "sszLog.h"

#include "sszBattleHeader.h"

#include "sszChamp.h"
#include "sszTeam.h"
#include "sszPilot.h"

#include "sszObj_IG_Stadium.h"
#include "sszPlayerCardSlot.h"

#include "sszChamp_Script.h"
#include "sszStatusBar.h"

namespace ssz
{
	using namespace object;

	IGStadiumScene::IGStadiumScene()
		: mBattleHeader(nullptr)
		, mPlayerSlot{}
	{
	}
	
	IGStadiumScene::~IGStadiumScene()
	{
	}

	void IGStadiumScene::Initialize()
	{
		// 배경
		{
			// Battle Header
			mBattleHeader = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.1f), eLayerType::UI, L"BattleHeaderBg");

			// IG Stadium
			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -139.0f, 1.5f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGround);

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.6f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* StadiumArea = Instantiate<GameObject>(TGM::GetStaidumPos(), TGM::GetStadiumScale(), eLayerType::BackGroundObj);
			StadiumArea->AddComponent<Collider2D>();
		}

#pragma region Create Object for this Scene
		// GameObject
		{
			// PlayerCard
			mPlayerSlot[(UINT)eTeamColor::Red][0] = InstantiateUI <PlayerCardSlot>(Vector3(843.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1");
			mPlayerSlot[(UINT)eTeamColor::Red][1] = InstantiateUI <PlayerCardSlot>(Vector3(843.f, 69.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2");
			mPlayerSlot[(UINT)eTeamColor::Blue][0] = InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1");
			mPlayerSlot[(UINT)eTeamColor::Blue][1] = InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 69.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2");

			mPlayerSlot[(UINT)eTeamColor::Red][0]->SetRed();
			mPlayerSlot[(UINT)eTeamColor::Red][1]->SetRed();
			mPlayerSlot[(UINT)eTeamColor::Blue][0]->SetBlue();
			mPlayerSlot[(UINT)eTeamColor::Blue][1]->SetBlue();
		}
#pragma endregion
	}
	void IGStadiumScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			SceneManager::LoadScene(L"MainLobbyScene");
		}

		BattleManager::Update();

		// 게임종료 후 모든애니메이션 동작 정지
		// 렌더없이 시뮬레이션으로 GroupB 경기 진행 후 데이터 입력.
		// 
	}
	void IGStadiumScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (25 <= Log::GetLogCnt())
			Log::Clear();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			Log::Clear();
			// SceneManager::LoadScene(L"TitleScene");
		}

		BattleManager::LateUpdate();
	}
	void IGStadiumScene::Render()
	{
		Scene::Render();
	}
	void IGStadiumScene::OnEnter()
	{
		Log::Clear();
		TGM::SetGameTime(60.f);

		mBattleHeader->RegistTeam();
		mBattleHeader->SetTimeType();

		// PlayerCard Init
		Team* PlayerTeam = TGM::GetPlayerTeam();
		Team* EnemyTeam = TGM::GetLeagueManage()->GetEnemyTeam();

		std::vector<Pilot*> PlayerTeamPilotList = PlayerTeam->GetPilotList();
		std::vector<Pilot*> EnemyTeamPilotList = EnemyTeam->GetPilotList();

		for (int i = 0; i < 2; ++i)
		{
			mPlayerSlot[(UINT)eTeamColor::Blue][i]->RegistPilot(PlayerTeamPilotList[i]);
			mPlayerSlot[(UINT)eTeamColor::Red][i]->RegistPilot(EnemyTeamPilotList[i]);
		}

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);

		// Spawn Champ
		{	
			League* LeagueManager = TGM::GetLeagueManage();

			std::vector<Pilot*> PPilotList = LeagueManager->GetPlayerTeam()->GetPilotList();
			std::vector<Pilot*> EPilotList = LeagueManager->GetEnemyTeam()->GetPilotList();

			Champ* RegistChamp[(UINT)eCampType::End][2];

			// Champ Regist
			for (int i = 0; i < 2; ++i)
			{
				RegistChamp[(UINT)eCampType::Player][i] = PPilotList[i]->GetChamp();
				RegistChamp[(UINT)eCampType::Enemy][i] = EPilotList[i]->GetChamp();
			}

			// Champ Spawn
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					Vector3 SpawnPoint = { (float)(rand() % 50), (float)(rand() % 150), 1.0f };
					SpawnPoint.y -= 100.f;
					if (i == (UINT)eCampType::Player)
						SpawnPoint.x = -SpawnPoint.x - 100.f;
					else
						SpawnPoint.x = SpawnPoint.x + 100.f;

					TGM::AddChampScene((eLayerType)(i + 2), RegistChamp[i][j], SpawnPoint);
				}
			}

			// Enemy Set
			for (int i = 0; i < 2; ++i)
			{
				RegistChamp[(UINT)eCampType::Player][0]->RegistEnemy(RegistChamp[(UINT)eCampType::Enemy][i]);
				RegistChamp[(UINT)eCampType::Player][1]->RegistEnemy(RegistChamp[(UINT)eCampType::Enemy][i]);
				RegistChamp[(UINT)eCampType::Enemy][0]->RegistEnemy(RegistChamp[(UINT)eCampType::Player][i]);
				RegistChamp[(UINT)eCampType::Enemy][1]->RegistEnemy(RegistChamp[(UINT)eCampType::Player][i]);
			}

			// Friendly Set
			RegistChamp[(UINT)eCampType::Player][0]->RegistFriendly(RegistChamp[(UINT)eCampType::Player][1]);
			RegistChamp[(UINT)eCampType::Player][1]->RegistFriendly(RegistChamp[(UINT)eCampType::Player][0]);
			RegistChamp[(UINT)eCampType::Enemy][0]->RegistFriendly(RegistChamp[(UINT)eCampType::Enemy][1]);
			RegistChamp[(UINT)eCampType::Enemy][1]->RegistFriendly(RegistChamp[(UINT)eCampType::Enemy][0]);
		}

		AddGameObject(eLayerType::Cursor, TGM::GetCursor());
		AddGameObject(eLayerType::Camera, TGM::GetCamera());

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyInteraction, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerInteraction, true);
		CollisionManager::SetLayer(eLayerType::BackGroundObj, eLayerType::Cursor, true);

		Time::TimeAcceleration(1.f);
	}
	void IGStadiumScene::OnExit()
	{
		TGM::GetLeagueManage()->RoundExit();

		CollisionManager::Clear();
		TGM::SceneClear();
		TGM::GetLeagueManage()->NextRound();
		
		Time::DefaultAcceleration();
	}
}