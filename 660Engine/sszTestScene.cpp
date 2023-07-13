#include "sszTestScene.h"

#include "sszInput.h"
#include "sszSceneManager.h"
#include "sszRenderer.h"

// Resources
#include "sszResources.h"
#include "sszMaterial.h"
#include "sszMesh.h"

// Component
#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszCollider2D.h"
#include "sszTestScript.h"
#include "sszTestScript2.h"
#include "sszTestScript3.h"

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"

// Object
#include "sszObject.h"
#include "sszCursor.h"

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

		GameObject* TestObject = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.010f), Vector3(300.f, 300.f, 1.f), eLayerType::Player);
		TestObject->SetName(L"Test");
		TestObject->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject->AddComponent<TestScript>()->SetDefault();
		TestObject->AddComponent<Collider2D>()->Initialize();
		TestObject->GetComponent<Collider2D>()->SetType(eColliderType::Circle);
		//TestObject->GetComponent<Transform>()->SetTransTypeADD();

		GameObject* TestObject2 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		//GameObject* TestObject2 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		TestObject2->SetName(L"Test2");
		TestObject2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject2->AddComponent<TestScript2>()->SetDefault();
		TestObject2->SetParent(TestObject);
		TestObject2->AddComponent<Collider2D>()->Initialize();
		//TestObject2->GetComponent<Transform>()->SetTransTypeADD();
		
		GameObject* TestObject3 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		//GameObject* TestObject3 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
		TestObject3->SetName(L"Test2");
		TestObject3->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		TestObject3->AddComponent<TestScript3>()->SetDefault();
		TestObject3->SetParent(TestObject2);
		TestObject3->AddComponent<Collider2D>()->Initialize();
		//TestObject3->GetComponent<Transform>()->SetTransTypeADD();

		// MouseCursor
		{
			Cursor* CursorObj = Instantiate<Cursor>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			CursorObj->SetName(L"Cursor");
			CursorObj->AddComponent<Collider2D>()->Initialize();
		}

		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::UI);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			renderer::cameras.push_back(cameraComp);
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
}