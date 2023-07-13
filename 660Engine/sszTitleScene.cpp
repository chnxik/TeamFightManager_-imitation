#include "sszTitleScene.h"

#include "sszInput.h"
#include "sszSceneManager.h"

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

	TitleScene::TitleScene()
		: TestObject(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"TitleBg", L"..\\Resources\\useResource\\Title\\teamfight_manager_title_bg.png");
			Resources::Load<Texture>(L"IGStadiumSkyTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium_sky_bg.png");
			Resources::Load<Texture>(L"IGStadiumTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium.png");
			Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");
		}
		{
			std::shared_ptr<Material> TitleBgMt = std::make_shared<Material>();
			TitleBgMt->SetMaterial(L"SpriteShader", L"TitleBg", eRenderingMode::Transparent);
			Resources::Insert(L"TitleBgMt", TitleBgMt);

			std::shared_ptr<Material> IG_stadium_Mt = std::make_shared<Material>();
			IG_stadium_Mt->SetMaterial(L"SpriteShader", L"IGStadiumTex", eRenderingMode::Transparent);
			Resources::Insert(L"IGStadiumMt", IG_stadium_Mt);

			std::shared_ptr<Material> IG_stadiumtSky_Mt = std::make_shared<Material>();
			IG_stadiumtSky_Mt->SetMaterial(L"SpriteShader", L"IGStadiumSkyTex", eRenderingMode::Opaque);
			Resources::Insert(L"IGStadiumSkyMt", IG_stadiumtSky_Mt);

			std::shared_ptr<Material> TitleLogo_Mt = std::make_shared<Material>();
			TitleLogo_Mt->SetMaterial(L"SpriteShader", L"TitleLogoTex", eRenderingMode::Transparent);
			Resources::Insert(L"TitleLogoMt", TitleLogo_Mt);
		}
#pragma region Create Object for this Scene
		// GameObject
		{
			GameObject* TitleBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			TitleBg->SetName(L"TitleBg");
			TitleBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleBgMt");

			GameObject* IG_Stadium = Instantiate<GameObject>(Vector3(0.0f, -44.0f, 1.021f), Vector3(2235.f, 1460.f, 1.f), eLayerType::BackGroundObj);
			IG_Stadium->SetName(L"IG_Stadium");
			IG_Stadium->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* TitleLogo = Instantiate<GameObject>(Vector3(0.0f, 242.0f, 1.011f), Vector3(738.f, 271.f, 1.f), eLayerType::BackGroundObj);
			TitleLogo->SetName(L"TitleLogo");
			TitleLogo->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");

			TestObject = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.010f), Vector3(300.f, 300.f, 1.f), eLayerType::Player);
			TestObject->SetName(L"Test");
			TestObject->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
			TestObject->AddComponent<TestScript>()->SetDefault();
			TestObject->AddComponent<Collider2D>()->Initialize();

			GameObject* TestObject2 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
			TestObject2->SetName(L"Test2");
			TestObject2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
			TestObject2->AddComponent<TestScript2>()->SetDefault();
			TestObject2->SetParent(TestObject);
			TestObject2->AddComponent<Collider2D>()->Initialize();

			GameObject* TestObject3 = Instantiate<GameObject>(Vector3(1.0f, 0.0f, 1.009f), Vector3(0.f, 0.f, 0.f), eLayerType::Player);
			TestObject3->SetName(L"Test2");
			TestObject3->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
			TestObject3->AddComponent<TestScript3>()->SetDefault();
			TestObject3->SetParent(TestObject2);
			TestObject3->AddComponent<Collider2D>()->Initialize();

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = TestObject->AddComponent<ArrangementScript>();
			// ArScript->SetDefault();
		}

		// MouseCursor
		{
			Cursor* CursorObj = Instantiate<Cursor>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			CursorObj->SetName(L"Cursor");
		}

		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::UI);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
		}
#pragma endregion
	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			SceneManager::LoadScene(L"PrlgScene");
		}
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
}