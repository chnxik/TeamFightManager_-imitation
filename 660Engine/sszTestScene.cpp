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

		UIObject* TestObject = Instantiate<UIObject>(Vector3(-50.0f, 0.0f, 1.010f), Vector3(100.f, 100.f, 1.f), eLayerType::UI);
		TestObject->SetName(L"Test");
		TestObject->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject->AddComponent<TestScript>()->SetDefault();
		TestObject->AddComponent<Collider2D>()->Initialize();
		//TestObject->GetComponent<Transform>()->SetTransTypeADD();

		UIObject* TestChildUIObject = new UIObject;
		Transform* tr = TestChildUIObject->AddComponent<Transform>();
		tr->SetPosition(Vector3(100.0f, 0.0f, 1.009f));
		tr->SetScale(Vector3(100.f, 100.f, 0.f));
		TestChildUIObject->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestChildUIObject->SetName(L"TestChildUI");
		TestChildUIObject->AddComponent<Collider2D>()->Initialize();
		TestChildUIObject->GetComponent<Collider2D>()->SetType(eColliderType::Circle);

		TestObject->AddChildUI(TestChildUIObject);

		//UIObject* TestObject2 = Instantiate<UIObject>(Vector3(100.0f, 0.0f, 1.009f), Vector3(100.f, 100.f, 0.f), eLayerType::UI);
		//GameObject* TestObject2 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		//TestObject2->SetName(L"Test2");
		//TestObject2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		//TestObject2->AddComponent<TestScript2>()->SetDefault();
		// TestObject2->SetParent(TestObject);
		//TestObject2->AddComponent<Collider2D>()->Initialize();
		//TestObject2->GetComponent<Collider2D>()->SetType(eColliderType::Circle);
		//TestObject2->GetComponent<Transform>()->SetTransTypeADD();
		
		/*
		GameObject* TestObject3 = Instantiate<GameObject>(Vector3(1.f, 0.0f, 1.009f), Vector3(1.f, 1.f, 0.f), Vector3(0.f, 0.f, DtoR(90.f)), eLayerType::Player);
		// GameObject* TestObject3 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		TestObject3->SetName(L"Test3");
		TestObject3->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject3->AddComponent<TestScript3>()->SetDefault();
		TestObject3->SetParent(TestObject2);
		TestObject3->AddComponent<Collider2D>()->Initialize();
		// TestObject3->GetComponent<Transform>()->SetTransTypeADD();

		*/

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
	}
	void TestScene::Render()
	{
		Scene::Render();
	}
	void TestScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
	}
}