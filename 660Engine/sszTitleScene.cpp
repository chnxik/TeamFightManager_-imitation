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
			std::shared_ptr<Texture> stadiumtSkyTex = Resources::Load<Texture>(L"StadiumSkyTex", L"..\\Resources\\useResource\\stadium\\stadium_sky_bg.png");
			std::shared_ptr<Texture> stadiumTex = Resources::Load<Texture>(L"StadiumTex", L"..\\Resources\\useResource\\stadium\\stadium.png");
			std::shared_ptr<Texture> TitleLogoTex = Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");

			// Make Material
			std::shared_ptr<Material> TitleBg_1_Mt = std::make_shared<Material>();
			TitleBg_1_Mt->SetShader(SpriteShader);
			TitleBg_1_Mt->SetTexture(TitleBgTex);
			TitleBg_1_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TitleBgMt", TitleBg_1_Mt);

			std::shared_ptr<Material> stadiumtSky_Mt = std::make_shared<Material>();
			stadiumtSky_Mt->SetShader(SpriteShader);
			stadiumtSky_Mt->SetTexture(stadiumtSkyTex);
			stadiumtSky_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"StadiumSkyMt", stadiumtSky_Mt);

			std::shared_ptr<Material> stadium_Mt = std::make_shared<Material>();
			stadium_Mt->SetShader(SpriteShader);
			stadium_Mt->SetTexture(stadiumTex);
			stadium_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"StadiumMt", stadium_Mt);

			std::shared_ptr<Material> TitleLogo_Mt = std::make_shared<Material>();
			TitleLogo_Mt->SetShader(SpriteShader);
			TitleLogo_Mt->SetTexture(TitleLogoTex);
			TitleLogo_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TitleLogoMt", TitleLogo_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			GameObject* TitleBg = new GameObject();
			TitleBg->SetName(L"TitleBg");
			AddGameObject(eLayerType::Player, TitleBg);

			MeshRenderer* TitleBg_mr = TitleBg->AddComponent<MeshRenderer>();
			TitleBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TitleBg_mr->SetMaterial(Resources::Find<Material>(L"TitleBgMt"));
			TitleBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			TitleBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.f));


			GameObject* Stadium = new GameObject();
			Stadium->SetName(L"Stadium");
			AddGameObject(eLayerType::Player, Stadium);

			MeshRenderer* Stadium_Mr = Stadium->AddComponent<MeshRenderer>();
			Stadium_Mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Stadium_Mr->SetMaterial(Resources::Find<Material>(L"StadiumMt"));
			Stadium->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.044f, 1.021f));
			Stadium->GetComponent<Transform>()->SetScale(Vector3(2.235f, 1.46f, 1.f));

			GameObject* StadiumSky = new GameObject();
			StadiumSky->SetName(L"StadiumSky");
			AddGameObject(eLayerType::Player, StadiumSky);

			MeshRenderer* StadimSky_mr = StadiumSky->AddComponent<MeshRenderer>();
			StadimSky_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			StadimSky_mr->SetMaterial(Resources::Find<Material>(L"StadiumSkyMt"));
			StadiumSky->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.053f, 1.022f));
			StadiumSky->GetComponent<Transform>()->SetScale(Vector3(2.144f, 1.429f, 1.f));


			GameObject* TitleLogo = new GameObject();
			TitleLogo->SetName(L"TitleLogo");
			AddGameObject(eLayerType::Player, TitleLogo);

			MeshRenderer* TitleLogo_mr = TitleLogo->AddComponent<MeshRenderer>();
			TitleLogo_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TitleLogo_mr->SetMaterial(Resources::Find<Material>(L"TitleLogoMt"));
			TitleLogo->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.242f, 1.011f));
			TitleLogo->GetComponent<Transform>()->SetScale(Vector3(0.738f, 0.271f, 1.f));

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = TitleLogo->AddComponent<ArrangementScript>();
			// ArScript->SetDefault();
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
#pragma endregion
	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (ssz::Input::GetKeyDown(eKeyCode::SPACE))
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