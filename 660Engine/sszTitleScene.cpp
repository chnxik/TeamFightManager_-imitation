#include "sszTitleScene.h"

#include "sszInput.h"
#include "sszSceneManager.h"
#include "sszCollisionManager.h"

#include "sszUIObject.h"

// Resources
#include "sszResources.h"
#include "sszMaterial.h"
#include "sszMesh.h"

// Component
#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszCollider2D.h"

// Script
#include "sszTestScript.h"
#include "sszTestScript2.h"
#include "sszTestScript3.h"

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"

// Object
#include "sszObject.h"


namespace ssz
{
	using namespace object;

	TitleScene::TitleScene()
		: NewGameUI(nullptr)
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

			Resources::Load<Texture>(L"NewGameUITex", L"..\\Resources\\useResource\\Title\\NewGame\\new_game_ui_bg.png");
			Resources::Load<Texture>(L"ImportantBtn_IdleTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_0.png");
			Resources::Load<Texture>(L"ImportantBtn_OnTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_1.png");
			Resources::Load<Texture>(L"ImportantBtn_DownTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_2.png");
			Resources::Load<Texture>(L"DefaultBtn_IdleTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_0.png");
			Resources::Load<Texture>(L"DefaultBtn_OnTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_1.png");
			Resources::Load<Texture>(L"DefaultBtn_DownTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_2.png");
		}
		{
			/*
			// 배경
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
			
			// UI
			std::shared_ptr<Material> NewGameUI_Mt = std::make_shared<Material>();
			NewGameUI_Mt->SetMaterial(L"SpriteShader", L"NewGameUITex", eRenderingMode::Transparent);
			Resources::Insert(L"NewGameUIMt", NewGameUI_Mt);

			std::shared_ptr<Material> ImportantBtn_Mt = std::make_shared<Material>();
			ImportantBtn_Mt->SetMaterial(L"SpriteShader", L"ImportantBtn_IdleTex", eRenderingMode::Transparent);
			*/
			
			LoadMaterial(L"TitleBgMt", L"SpriteShader", L"TitleBg", eRenderingMode::Transparent);
			LoadMaterial(L"IGStadiumMt", L"SpriteShader", L"IGStadiumTex", eRenderingMode::Transparent);
			LoadMaterial(L"IGStadiumSkyMt", L"SpriteShader", L"IGStadiumSkyTex", eRenderingMode::Transparent);
			LoadMaterial(L"TitleLogoMt", L"SpriteShader", L"TitleLogoTex", eRenderingMode::Transparent);
			LoadMaterial(L"NewGameUIMt", L"SpriteShader", L"NewGameUITex", eRenderingMode::Transparent);
			LoadMaterial(L"InportantBtnMt", L"SpriteShader", L"ImportantBtn_IdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"DefaultUIMt", L"SpriteShader", L"DefaultBtn_IdleTex", eRenderingMode::Transparent);

		}
#pragma region Create Object for this Scene
		// Bagk Ground
		{
			GameObject* TitleBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			TitleBg->SetName(L"TitleBg");
			TitleBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleBgMt");

			GameObject* IG_Stadium = Instantiate<GameObject>(Vector3(0.0f, -44.0f, 1.121f), Vector3(2235.f, 1460.f, 1.f), eLayerType::BackGroundObj);
			IG_Stadium->SetName(L"IG_Stadium");
			IG_Stadium->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.122f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* TitleLogo = Instantiate<GameObject>(Vector3(0.0f, 242.0f, 1.111f), Vector3(738.f, 271.f, 1.f), eLayerType::BackGroundObj);
			TitleLogo->SetName(L"TitleLogo");
			TitleLogo->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = TestObject->AddComponent<ArrangementScript>();
			// ArScript->SetDefault();
		}

		// UI
		{
			NewGameUI = Instantiate<UIObject>(Vector3(0.f, 50.f, 1.01f), 
				Vector3(1350.f, 786.f, 1.f), eLayerType::UI);
			NewGameUI->SetName(L"NewGameUIPanel");
			NewGameUI->AddComponent<MeshRenderer>()->
				SetMeshRenderer(L"RectMesh", L"NewGameUIMt");
			NewGameUI->AddComponent<Collider2D>()->Initialize();
			NewGameUI->SetState(ssz::GameObject::eState::Paused);

			UIObject* BtnUI = InstantiateUI<UIObject>(Vector3(-123.f, -285.f, 1.009f), 
				Vector3(207.f, 75.f, 1.f), NewGameUI, true);
			BtnUI->SetName(L"InportantUI");
			BtnUI->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"InportantBtnMt");

			UIObject* BtnUI2 = InstantiateUI<UIObject>(Vector3(123.f, -285.f, 1.009f),
				Vector3(207.f, 75.f, 1.f), NewGameUI, true);
			BtnUI2->SetName(L"DefaultUI");
			BtnUI2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"DefaultUIMt");
			
		}

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
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (NewGameUI->GetState() == GameObject::eState::Paused)
			{
				NewGameUI->SetActive();
		//		std::vector<UIObject*> BtnUI = NewGameUI->GetChildUI();
		//		
		//		for (int i = 0; i < (UINT)BtnUI.size(); ++i)
		//		{
		//			BtnUI[i]->SetState(GameObject::eState::Active);
		//		}
			}
		}

		if (Input::GetKeyDown(eKeyCode::ENTER))
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
	void TitleScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void TitleScene::OnExit()
	{
		CollisionManager::Clear();
	}
}