#include "sszIGStadiumScene.h"
#include "CommonHeader.h"

#include "sszTGM.h"
#include "sszBattleManager.h"

#include "sszLog.h"

#include "sszBattleHeader.h"

#include "sszChamp.h"

#include "sszObj_IG_Stadium.h"
#include "sszPlayerCardSlot.h"

#include "sszChamp_Script.h"
#include "sszStatusBar.h"

namespace ssz
{
	using namespace object;

	IGStadiumScene::IGStadiumScene()
	{
	}
	IGStadiumScene::~IGStadiumScene()
	{
	}
	void IGStadiumScene::Initialize()
	{
		// ¹è°æ
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.1f), eLayerType::UI, L"BattleHeaderBg");

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
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 69.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1")->SetBlue();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 69.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2")->SetBlue();
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

		// Player
		{	
			Champ* archer = TGM::AddChampScene(eLayerType::Player, ARCHER, Vector3(-100.f, -200.f, 1.0f));
			Champ* knight = TGM::AddChampScene(eLayerType::Enemy, KNIGHT, Vector3(100.f, -250.f, 1.0f));

			archer->RegistPilot(TGM::GetPilot(L"Faker"));
			knight->RegistPilot(TGM::GetPilot(L"Canyon"));

			archer->RegistEnemy(knight);
			knight->RegistEnemy(archer);
		}

		AddGameObject(eLayerType::Cursor, TGM::GetCursor());
		AddGameObject(eLayerType::Camera, TGM::GetCamera());

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyInteraction, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerInteraction, true);
		CollisionManager::SetLayer(eLayerType::BackGroundObj, eLayerType::Cursor, true);
	}
	void IGStadiumScene::OnExit()
	{
		CollisionManager::Clear();
		TGM::SceneClear();
	}
}