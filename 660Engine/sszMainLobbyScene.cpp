#include "sszMainLobbyScene.h"

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

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"

// Object
#include "sszObject.h"
#include "sszCursor.h"

namespace ssz
{
	using namespace object;

	MainLobbyScene::MainLobbyScene()
		: BgSky(nullptr)
	{
	}

	MainLobbyScene::~MainLobbyScene()
	{
	}

	void MainLobbyScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Texture
			Resources::Load<Texture>(L"SkydayBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_day.png");
			Resources::Load<Texture>(L"SkynightBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_night.png");
			Resources::Load<Texture>(L"SkysunsetBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_sunset.png");
			Resources::Load<Texture>(L"BgGroundTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\Ground\\ground.png");
			Resources::Load<Texture>(L"BgHouseTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\house\\house_bg.png");
			Resources::Load<Texture>(L"UIheaderBarTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header_bg.png");
			
			// Make Material
			std::shared_ptr<Material> Bg_Skyday_Mt = std::make_shared<Material>();
			Bg_Skyday_Mt->SetMaterial(L"SpriteShader", L"SkydayBgTex", eRenderingMode::Transparent);
			Resources::Insert(L"Bg_Skyday_Mt", Bg_Skyday_Mt);

			std::shared_ptr<Material> Bg_Ground_Mt = std::make_shared<Material>();
			Bg_Ground_Mt->SetMaterial(L"SpriteShader", L"BgGroundTex", eRenderingMode::Transparent);
			Resources::Insert(L"Bg_Ground_Mt", Bg_Ground_Mt);

			std::shared_ptr<Material> Bg_House_Mt = std::make_shared<Material>();
			Bg_House_Mt->SetMaterial(L"SpriteShader", L"BgHouseTex", eRenderingMode::Transparent);
			Resources::Insert(L"Bg_House_Mt", Bg_House_Mt);

			std::shared_ptr<Material> UI_headerBar_Mt = std::make_shared<Material>();
			UI_headerBar_Mt->SetMaterial(L"SpriteShader", L"UIheaderBarTex", eRenderingMode::Transparent);
			Resources::Insert(L"UI_headerBar_Mt", UI_headerBar_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// Bg_Sky
			GameObject* Bg_Sky = Instantiate<GameObject>(Vector3(0.0f, 166.f, 1.1f), Vector3(1920.f, 1920.f, 1.f), eLayerType::BackGround);
			Bg_Sky->SetName(L"Bg_Sky");
			Bg_Sky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_Skyday_Mt");
			BgSky = Bg_Sky;

			// Bg_Ground
			GameObject* Bg_Ground = Instantiate<GameObject>(Vector3(0.0f, -445.f, 1.015f), Vector3(1920.f, 256.f, 1.f), eLayerType::BackGround);
			Bg_Ground->SetName(L"Bg_Ground");
			Bg_Ground->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_Ground_Mt");

			// Bg_House
			GameObject* Bg_House = Instantiate<GameObject>(Vector3(0.0f, -30.f, 1.014f), Vector3(668.f, 512.f, 1.f), eLayerType::BackGround);
			Bg_House->SetName(L"Bg_House");
			Bg_House->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_House_Mt");

			// UI_Headerbar
			GameObject* UI_headerBar = Instantiate<GameObject>(Vector3(0.0f, 523.f, 1.015f), Vector3(1920.f, 111.f, 1.f), eLayerType::BackGround);
			UI_headerBar->SetName(L"UI_header_Bar");
			UI_headerBar->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UI_headerBar_Mt");

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = Bg_House->AddComponent<ArrangementScript>();
			ArScript->SetDefault();
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

	void MainLobbyScene::Update()
	{
		Scene::Update();

		static UINT skyBg = 0;

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			switch (skyBg)
			{
			case 0:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture (Resources::Find<Texture>(L"SkysunsetBgTex"));
				skyBg++;
				break;
			case 1:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkynightBgTex"));
				skyBg++;
				break;
			case 2:
				// Next Scene
				SceneManager::LoadScene(L"StadiumScene");
				break;
			}
		}
	}

	void MainLobbyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MainLobbyScene::Render()
	{
		Scene::Render();
	}
}