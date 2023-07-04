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

namespace ssz
{
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
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> Bg_SkydayTex = Resources::Load<Texture>(L"SkydayBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_day.png");
			std::shared_ptr<Texture> Bg_SkynightTex = Resources::Load<Texture>(L"SkynightBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_night.png");
			std::shared_ptr<Texture> Bg_SkysunsetTex = Resources::Load<Texture>(L"SkysunsetBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_sunset.png");
			std::shared_ptr<Texture> Bg_GroundTex = Resources::Load<Texture>(L"BgGroundTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\Ground\\ground.png");
			std::shared_ptr<Texture> Bg_HouseTex = Resources::Load<Texture>(L"BgHouseTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\house\\house_bg.png");
			std::shared_ptr<Texture> UIheaderBarTex = Resources::Load<Texture>(L"UIheaderBarTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header_bg.png");
			
			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> Bg_Skyday_Mt = std::make_shared<Material>();
			Bg_Skyday_Mt->SetShader(SpriteShader);
			Bg_Skyday_Mt->SetTexture(Bg_SkydayTex);
			Bg_Skyday_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Bg_Skyday_Mt", Bg_Skyday_Mt);

			std::shared_ptr<Material> Bg_Ground_Mt = std::make_shared<Material>();
			Bg_Ground_Mt->SetShader(SpriteShader);
			Bg_Ground_Mt->SetTexture(Bg_GroundTex);
			Bg_Ground_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Bg_Ground_Mt", Bg_Ground_Mt);

			std::shared_ptr<Material> Bg_House_Mt = std::make_shared<Material>();
			Bg_House_Mt->SetShader(SpriteShader);
			Bg_House_Mt->SetTexture(Bg_HouseTex);
			Bg_House_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Bg_House_Mt", Bg_House_Mt);

			std::shared_ptr<Material> UI_headerBar_Mt = std::make_shared<Material>();
			UI_headerBar_Mt->SetShader(SpriteShader);
			UI_headerBar_Mt->SetTexture(UIheaderBarTex);
			UI_headerBar_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"UI_headerBar_Mt", UI_headerBar_Mt);

			// Mouse Cursor Material
			std::shared_ptr<Material> Cursor_Mt = std::make_shared<Material>();
			Cursor_Mt->SetShader(SpriteShader);
			Cursor_Mt->SetTexture(CursorTex);
			Cursor_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"CursorMt", Cursor_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// Bg_Sky
			GameObject* Bg_Skyday = new GameObject();
			Bg_Skyday->SetName(L"Bg_Skyday");
			AddGameObject(eLayerType::BackGround, Bg_Skyday);
			BgSky = Bg_Skyday;

			MeshRenderer* Bg_Skyday_mr = Bg_Skyday->AddComponent<MeshRenderer>();
			Bg_Skyday_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Bg_Skyday_mr->SetMaterial(Resources::Find<Material>(L"Bg_Skyday_Mt"));
			Bg_Skyday->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.166f, 1.1f));
			Bg_Skyday->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.92f, 1.f));

			// Bg_Ground
			GameObject* Bg_Ground = new GameObject();
			Bg_Ground->SetName(L"Bg_Ground");
			AddGameObject(eLayerType::BackGround, Bg_Ground);

			MeshRenderer* Bg_Ground_mr = Bg_Ground->AddComponent<MeshRenderer>();
			Bg_Ground_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Bg_Ground_mr->SetMaterial(Resources::Find<Material>(L"Bg_Ground_Mt"));
			Bg_Ground->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.412f, 1.001f));
			Bg_Ground->GetComponent<Transform>()->SetScale(Vector3(1.92f, 0.256f, 1.f));

			// Bg_House
			GameObject* Bg_House = new GameObject();
			Bg_House->SetName(L"Bg_House");
			AddGameObject(eLayerType::BackGround, Bg_House);

			MeshRenderer* Bg_House_mr = Bg_House->AddComponent<MeshRenderer>();
			Bg_House_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Bg_House_mr->SetMaterial(Resources::Find<Material>(L"Bg_House_Mt"));
			Bg_House->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.028f, 1.0001f));
			Bg_House->GetComponent<Transform>()->SetScale(Vector3(0.668f, 0.512f, 1.f));

			// UI_Headerbar
			GameObject* UI_headerBar = new GameObject();
			UI_headerBar->SetName(L"UI_header_Bar");
			AddGameObject(eLayerType::BackGround, UI_headerBar);
			
			MeshRenderer* UI_headerBar_mr = UI_headerBar->AddComponent<MeshRenderer>();
			UI_headerBar_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			UI_headerBar_mr->SetMaterial(Resources::Find<Material>(L"UI_headerBar_Mt"));
			UI_headerBar->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.4845f, 1.001f));
			UI_headerBar->GetComponent<Transform>()->SetScale(Vector3(1.92f, 0.111f, 1.f));

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = Bg_House->AddComponent<ArrangementScript>();
			ArScript->SetDefault();
		}

		// MouseCursor
		{
			GameObject* Cursor = new GameObject();
			Cursor->SetName(L"Cursor");
			AddGameObject(eLayerType::Cursor, Cursor);

			MeshRenderer* Cursor_mr = Cursor->AddComponent<MeshRenderer>();
			Cursor_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Cursor_mr->SetMaterial(Resources::Find<Material>(L"CursorMt"));
			Cursor->GetComponent<Transform>()->SetPosition(Vector3(-0.9f, 0.0f, 0.01f));
			Cursor->GetComponent<Transform>()->SetScale(Vector3(0.032f, 0.032f, 1.0f));
			Cursor->AddComponent<CursorScript>();
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::UI, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
		}


		// UI Camera
		{
			GameObject* UIcamera = new GameObject();
			UIcamera->SetName(L"UICamera");
			AddGameObject(eLayerType::UI, UIcamera);
			UIcamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			Camera* cameraComp = UIcamera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			cameraComp->TurnLayerMask(eLayerType::Cursor, true);
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
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture  (Resources::Find<Texture>(L"SkysunsetBgTex"));
				skyBg++;
				break;
			case 1:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkynightBgTex"));
				skyBg++;
				break;
			case 2:
				// Next Scene
				//SceneManager::LoadScene(L"MainLobbyScene");
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