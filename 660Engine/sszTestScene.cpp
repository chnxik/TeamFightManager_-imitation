#include "sszTestScene.h"
#include "CommonHeader.h"

#include "sszBattleHeader.h"

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
		// ¹è°æ
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.019f), eLayerType::UI, L"BattleHeaderBg");

			// IG Stadium
			GameObject* IG_Stadium = Instantiate<GameObject>(Vector3(0.0f, -139.0f, 1.021f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGround);
			IG_Stadium->SetName(L"IG_Stadium");
			IG_Stadium->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");
		}

		// Player
		{
			

			GameObject* TestObj = Instantiate<GameObject>(Vector3(0.f, 0.f, 1.01f), Vector3(128.f, 128.f, 1.f), eLayerType::Player);
			Animator* AniComp = TestObj->AddComponent<Animator>();
			
			TestObj->AddComponent<TestScript>();
			Collider2D* TestCol = TestObj->AddComponent<Collider2D>();
			TestCol->SetOffsetSize(Vector3(-32.f, -32.f, 0.f));
			
			TestObj->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"archer_spriteMt");


			
		}

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
			Cursor->AddComponent<CursorScript>();
		}

		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::Camera);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
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
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
	}
}