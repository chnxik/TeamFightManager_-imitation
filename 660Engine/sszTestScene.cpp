#include "sszTestScene.h"
#include "CommonHeader.h"

#include "sszBattleHeader.h"
#include "sszObj_IG_Stadium.h"

namespace ssz
{
	using namespace object;

	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::Camera);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
		}

		// ���
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.019f), eLayerType::UI, L"BattleHeaderBg");

			// IG Stadium
			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -139.0f, 1.021f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGround);

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");
		}
#pragma endregion
	}

	void TestScene::Update()
	{
		Scene::Update();
	}
	void TestScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void TestScene::Render()
	{
		Scene::Render();
	}
	void TestScene::OnEnter()
	{
		// Player
		{
			Champ* archer = TGM::AddChampScene(eLayerType::Player, ARCHER, Vector3(-100.f, 50.f, 1.0f));
			Champ* knight = TGM::AddChampScene(eLayerType::Enemy, KNIGHT, Vector3(100.f, -50.f, 1.0f));

			archer->RegistEnemy(knight);
			knight->RegistEnemy(archer);
		}

		AddGameObject(eLayerType::Cursor, TGM::GetCursor());

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyInteraction, true);
		CollisionManager::SetLayer(eLayerType::Enemy, eLayerType::PlayerInteraction, true);
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
		TGM::SceneClear();
	}
}