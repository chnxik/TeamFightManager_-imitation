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
#include "sszChampDataSlot.h"

#include "sszChamp_Script.h"
#include "sszStatusBar.h"

namespace ssz
{
	using namespace object;

	IGStadiumScene::IGStadiumScene()
		: mBattleHeader(nullptr)
		, mPlayerSlot{}
		, mChampDataSlot{}
		, fAccTime(0.f)
		, iGameCnt(0)
		, mCurPhase(eGamePhase::SceneIn)
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

			// ChampDataSlot
			mChampDataSlot[(UINT)eTeamColor::Red][0] = InstantiateUI <ChampDataSlot>(Vector3(843.f, 308.f, 1.03f), eLayerType::UI, L"RedChampData_1");
			mChampDataSlot[(UINT)eTeamColor::Red][1] = InstantiateUI <ChampDataSlot>(Vector3(843.f, 69.f, 1.03f), eLayerType::UI, L"RedChampData_2");
			mChampDataSlot[(UINT)eTeamColor::Blue][0] = InstantiateUI<ChampDataSlot>(Vector3(-843.f, 308.f, 1.03f), eLayerType::UI, L"BlueChampData_1");
			mChampDataSlot[(UINT)eTeamColor::Blue][1] = InstantiateUI<ChampDataSlot>(Vector3(-843.f, 69.f, 1.03f), eLayerType::UI, L"BlueChampData_2");
			
			mChampDataSlot[(UINT)eTeamColor::Red][0]->RegistPlayerCardSlot(mPlayerSlot[(UINT)eTeamColor::Red][0]);
			mChampDataSlot[(UINT)eTeamColor::Red][1]->RegistPlayerCardSlot(mPlayerSlot[(UINT)eTeamColor::Red][1]);
			mChampDataSlot[(UINT)eTeamColor::Blue][0]->RegistPlayerCardSlot(mPlayerSlot[(UINT)eTeamColor::Blue][0]);
			mChampDataSlot[(UINT)eTeamColor::Blue][1]->RegistPlayerCardSlot(mPlayerSlot[(UINT)eTeamColor::Blue][1]);

		}
#pragma endregion
	}
	void IGStadiumScene::Update()
	{
		switch (mCurPhase)
		{
		case ssz::IGStadiumScene::eGamePhase::SceneIn:
		{
			fAccTime += (float)DT;

			// DataSlot
			Transform* RedSlotTr1 = mChampDataSlot[(UINT)eTeamColor::Red][0]->GetComponent<Transform>();
			Transform* RedSlotTr2 = mChampDataSlot[(UINT)eTeamColor::Red][1]->GetComponent<Transform>();
			Transform* BlueSlotTr1 = mChampDataSlot[(UINT)eTeamColor::Blue][0]->GetComponent<Transform>();
			Transform* BlueSlotTr2 = mChampDataSlot[(UINT)eTeamColor::Blue][1]->GetComponent<Transform>();

			float Xpos = (119.f / 2.f) + (235.f / 2.f);

			Vector3 RSlotPos1 = RedSlotTr1->GetPosition();
			Vector3 RSlotPos2 = RedSlotTr2->GetPosition();
			Vector3 BSlotPos1 = BlueSlotTr1->GetPosition();
			Vector3 BSlotPos2 = BlueSlotTr2->GetPosition();

			// RSlot
			if (667.f < RSlotPos1.x)
			{
				float fForce = RSlotPos1.x - 667.f;
				RSlotPos1.x -= fForce * 4.f * (float)Time::DeltaTime();
				RSlotPos2.x -= fForce * 4.f * (float)Time::DeltaTime();

				RedSlotTr1->SetPosition(RSlotPos1);
				RedSlotTr2->SetPosition(RSlotPos2);
			}

			// BSlot
			if (-667.f > BSlotPos1.x)
			{
				float fForce = RSlotPos1.x - 667.f;
				BSlotPos1.x += fForce * 4.f * (float)Time::DeltaTime();
				BSlotPos2.x += fForce * 4.f * (float)Time::DeltaTime();

				BlueSlotTr1->SetPosition(BSlotPos1);
				BlueSlotTr2->SetPosition(BSlotPos2);
			}

			if (1.f < fAccTime)
			{
				fAccTime = 0.f;
				if (iGameCnt == 0)
				{
					RSlotPos1.x = 666.f;
					RSlotPos2.x = 666.f;
					BSlotPos1.x = -666.f;
					BSlotPos2.x = -666.f;

					RedSlotTr1->SetPosition(RSlotPos1);
					RedSlotTr2->SetPosition(RSlotPos2);
					BlueSlotTr1->SetPosition(BSlotPos1);
					BlueSlotTr2->SetPosition(BSlotPos2);

					TGM::GameStart();
					mCurPhase = eGamePhase::Game;
					return;
				}
				iGameCnt--;
			}

			break;
		}
		case ssz::IGStadiumScene::eGamePhase::Game:
		{
			float gametime = TGM::GetGameTime() - (float)DT;

			if (gametime < 0.f)
			{
				TGM::GameSet();
				mCurPhase = eGamePhase::Finish;
			}

			TGM::SetGameTime(gametime);
			break;

		}
		case ssz::IGStadiumScene::eGamePhase::Finish:
		{
			break;
		}
		case ssz::IGStadiumScene::eGamePhase::SceneOut:
		{

			break;
		}
		}

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

		mCurPhase = eGamePhase::SceneIn;

		mChampDataSlot[(UINT)eTeamColor::Red][0]->GetComponent<Transform>()->SetPosition(Vector3(843.f, 308.f, 1.03f));
		mChampDataSlot[(UINT)eTeamColor::Red][1]->GetComponent<Transform>()->SetPosition(Vector3(843.f, 69.f, 1.03f));
		mChampDataSlot[(UINT)eTeamColor::Blue][0]->GetComponent<Transform>()->SetPosition(Vector3(-843.f, 308.f, 1.03f));
		mChampDataSlot[(UINT)eTeamColor::Blue][1]->GetComponent<Transform>()->SetPosition(Vector3(-843.f, 69.f, 1.03f));

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
				Champ* BlueTeamChamp = PPilotList[i]->GetChamp();
				Champ* RedTeamChamp = EPilotList[i]->GetChamp();;

				RegistChamp[(UINT)eCampType::Player][i] = BlueTeamChamp;
				RegistChamp[(UINT)eCampType::Enemy][i] = RedTeamChamp;
				mChampDataSlot[(UINT)eTeamColor::Blue][i]->RegistChamp(BlueTeamChamp);
				mChampDataSlot[(UINT)eTeamColor::Red][i]->RegistChamp(RedTeamChamp);
				mPlayerSlot[(UINT)eTeamColor::Blue][i]->RegistChamp(BlueTeamChamp);
				mPlayerSlot[(UINT)eTeamColor::Red][i]->RegistChamp(RedTeamChamp);
			}

			// Champ Spawn
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					Vector3 SpawnPoint = { (float)(rand() % 300), (float)(rand() % 400), 1.0f };
					SpawnPoint.y -= 300.f;
					if (i == (UINT)eCampType::Player)
						SpawnPoint.x = -SpawnPoint.x - 200.f;
					else
						SpawnPoint.x = SpawnPoint.x + 200.f;


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

		TGM::PlayBGM(L"BattleBGM");
		iGameCnt = 5;

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