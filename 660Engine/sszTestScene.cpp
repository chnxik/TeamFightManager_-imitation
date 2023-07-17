#include "sszTestScene.h"
#include "CommonHeader.h"

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
		Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");

		std::shared_ptr<Material> TitleLogo_Mt = std::make_shared<Material>();
		TitleLogo_Mt->SetMaterial(L"SpriteShader", L"TitleLogoTex", eRenderingMode::Transparent);
		Resources::Insert(L"TitleLogoMt", TitleLogo_Mt);

		UIObject* TestObject = Instantiate<UIObject>(Vector3(-50.0f, 0.0f, 1.010f), Vector3(200.f, 200.f, 1.f),Vector3(0.f,0.f,DtoR(30.f)), eLayerType::Player);
		TestObject->SetName(L"Test");
		TestObject->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject->AddComponent<TestScript>()->SetDefault();
		TestObject->AddComponent<Collider2D>()->Initialize();
		//TestObject->GetComponent<Transform>()->SetTransTypeADD();

		UIObject* TestObject2 = Instantiate<UIObject>(Vector3(-300.0f, 0.0f, 1.010f), Vector3(200.f, 200.f, 1.f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		TestObject2->SetName(L"Test2");
		TestObject2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject2->AddComponent<TestScript2>()->SetDefault();
		TestObject2->AddComponent<Collider2D>()->Initialize();

		UIObject* TestObject3 = Instantiate<UIObject>(Vector3(300.0f, 0.0f, 1.010f), Vector3(200.f, 200.f, 1.f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		TestObject3->SetName(L"Test2");
		TestObject3->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject3->AddComponent<TestScript3>()->SetDefault();
		Collider2D* Col = TestObject3->AddComponent<Collider2D>();
		Col->Initialize();
		Col->SetType(eColliderType::Circle);

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
			
			// Init
			Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			std::shared_ptr<Material>CursorMt = std::make_shared<Material>();
			CursorMt->SetMaterial(L"SpriteShader", L"CursorTex", eRenderingMode::Transparent);
			CursorMt = Resources::Insert(L"CursorMt", CursorMt);

			Cursor->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CursorMt");
			Cursor->AddComponent<Collider2D>()->Initialize();
			Cursor->AddComponent<CursorScript>()->Initialize();
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Cursor, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
	}
}