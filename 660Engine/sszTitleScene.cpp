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

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"


namespace ssz
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> TitleBgTex = Resources::Load<Texture>(L"TitleBg", L"..\\Resources\\useResource\\Title\\teamfight_manager_title_bg.png");
			std::shared_ptr<Texture> IG_stadiumtSkyTex = Resources::Load<Texture>(L"IGStadiumSkyTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium_sky_bg.png");
			std::shared_ptr<Texture> IG_stadiumTex = Resources::Load<Texture>(L"IGStadiumTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium.png");
			std::shared_ptr<Texture> TitleLogoTex = Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");
			
			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> TitleBg_1_Mt = std::make_shared<Material>();
			TitleBg_1_Mt->SetShader(SpriteShader);
			TitleBg_1_Mt->SetTexture(TitleBgTex);
			TitleBg_1_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TitleBgMt", TitleBg_1_Mt);

			std::shared_ptr<Material> IG_stadiumtSky_Mt = std::make_shared<Material>();
			IG_stadiumtSky_Mt->SetShader(SpriteShader);
			IG_stadiumtSky_Mt->SetTexture(IG_stadiumtSkyTex);
			IG_stadiumtSky_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"IGStadiumSkyMt", IG_stadiumtSky_Mt);

			std::shared_ptr<Material> IG_stadium_Mt = std::make_shared<Material>();
			IG_stadium_Mt->SetShader(SpriteShader);
			IG_stadium_Mt->SetTexture(IG_stadiumTex);
			IG_stadium_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"IGStadiumMt", IG_stadium_Mt);

			std::shared_ptr<Material> TitleLogo_Mt = std::make_shared<Material>();
			TitleLogo_Mt->SetShader(SpriteShader);
			TitleLogo_Mt->SetTexture(TitleLogoTex);
			TitleLogo_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TitleLogoMt", TitleLogo_Mt);

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
			GameObject* TitleBg = new GameObject();
			TitleBg->SetName(L"TitleBg");
			AddGameObject(eLayerType::BackGround, TitleBg);

			MeshRenderer* TitleBg_mr = TitleBg->AddComponent<MeshRenderer>();
			TitleBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TitleBg_mr->SetMaterial(Resources::Find<Material>(L"TitleBgMt"));
			TitleBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			TitleBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.f));


			GameObject* IG_Stadium = new GameObject();
			IG_Stadium->SetName(L"Stadium");
			AddGameObject(eLayerType::BackGround, IG_Stadium);

			MeshRenderer* IG_Stadium_Mr = IG_Stadium->AddComponent<MeshRenderer>();
			IG_Stadium_Mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_Stadium_Mr->SetMaterial(Resources::Find<Material>(L"IGStadiumMt"));
			IG_Stadium->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.044f, 1.021f));
			IG_Stadium->GetComponent<Transform>()->SetScale(Vector3(2.235f, 1.46f, 1.f));

			GameObject* IG_StadiumSky = new GameObject();
			IG_StadiumSky->SetName(L"StadiumSky");
			AddGameObject(eLayerType::BackGround, IG_StadiumSky);

			MeshRenderer* IG_StadimSky_mr = IG_StadiumSky->AddComponent<MeshRenderer>();
			IG_StadimSky_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_StadimSky_mr->SetMaterial(Resources::Find<Material>(L"IGStadiumSkyMt"));
			IG_StadiumSky->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.053f, 1.022f));
			IG_StadiumSky->GetComponent<Transform>()->SetScale(Vector3(2.144f, 1.429f, 1.f));


			GameObject* TitleLogo = new GameObject();
			TitleLogo->SetName(L"TitleLogo");
			AddGameObject(eLayerType::BackGround, TitleLogo);

			MeshRenderer* TitleLogo_mr = TitleLogo->AddComponent<MeshRenderer>();
			TitleLogo_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TitleLogo_mr->SetMaterial(Resources::Find<Material>(L"TitleLogoMt"));
			TitleLogo->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.242f, 1.011f));
			TitleLogo->GetComponent<Transform>()->SetScale(Vector3(0.738f, 0.271f, 1.f));

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = Cursor->AddComponent<ArrangementScript>();
			// ArScript->SetDefault();
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