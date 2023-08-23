#include "sszTestScene.h"
#include "CommonHeader.h"

#include "sszBattleManager.h"

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
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::Camera);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();

			GameObject* Sound = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -1.0f), eLayerType::Light);
			Sound->AddComponent<AudioListener>();
		}

		// ¹è°æ
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.019f), eLayerType::UI, L"BattleHeaderBg");

			// IG Stadium
			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -139.0f, 1.021f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGround);

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* BgmPlayer = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::Light);
			AudioSource* as = BgmPlayer->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"TestBgm", L"..\\Resources\\useResource\\Audio\\0.mp3"));
			as->Play();

			GameObject* TestText = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), Vector3(200.f,200.f,1.f), eLayerType::BackGroundObj);
			TestText->AddComponent<ArrangementScript>();
			TestText->AddComponent<Collider2D>();
			Text* tx = TestText->AddComponent<Text>();
			tx->SetString(L"Test");
			tx->SetFontSize(100.f);
			tx->SetFontColor(255, 0, 255, 255);
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

		BattleManager::Update();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			// SceneManager::LoadScene(L"TitleScene");
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
		CollisionManager::SetLayer(eLayerType::BackGroundObj, eLayerType::Cursor, true);
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
		TGM::SceneClear();
	}
}