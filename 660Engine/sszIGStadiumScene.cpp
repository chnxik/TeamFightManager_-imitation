#include "sszIGStadiumScene.h"

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
	IGStadiumScene::IGStadiumScene()
	{
	}
	IGStadiumScene::~IGStadiumScene()
	{
	}
	void IGStadiumScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> BattleHeaderTex = Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\GameScene\\header_bg.png");

			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> BattleHeader_Mt = std::make_shared<Material>();
			BattleHeader_Mt->SetShader(SpriteShader);
			BattleHeader_Mt->SetTexture(BattleHeaderTex);
			BattleHeader_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"BattleHeaderMt", BattleHeader_Mt);

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
			// Battle Header
			GameObject* BattleHeaderBg = new GameObject();
			BattleHeaderBg->SetName(L"BattleHeaderBg");
			AddGameObject(eLayerType::BackGround, BattleHeaderBg);

			MeshRenderer* BattleHeaderBg_mr = BattleHeaderBg->AddComponent<MeshRenderer>();
			BattleHeaderBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BattleHeaderBg_mr->SetMaterial(Resources::Find<Material>(L"BattleHeaderMt"));
			BattleHeaderBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.4785f, 1.04f));
			BattleHeaderBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 0.123f, 1.f));

			// IG Stadium
			GameObject* IG_Stadium = new GameObject();
			IG_Stadium->SetName(L"Stadium");
			AddGameObject(eLayerType::BackGround, IG_Stadium);

			MeshRenderer* IG_Stadium_Mr = IG_Stadium->AddComponent<MeshRenderer>();
			IG_Stadium_Mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_Stadium_Mr->SetMaterial(Resources::Find<Material>(L"IGStadiumMt"));
			IG_Stadium->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.119f, 1.11f));
			IG_Stadium->GetComponent<Transform>()->SetScale(Vector3(2.235f, 1.46f, 1.f));

			// IG StadiumSky
			GameObject* IG_StadiumSky = new GameObject();
			IG_StadiumSky->SetName(L"StadiumSky");
			AddGameObject(eLayerType::BackGround, IG_StadiumSky);

			MeshRenderer* IG_StadimSky_mr = IG_StadiumSky->AddComponent<MeshRenderer>();
			IG_StadimSky_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_StadimSky_mr->SetMaterial(Resources::Find<Material>(L"IGStadiumSkyMt"));
			IG_StadiumSky->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.136f, 1.12f));
			IG_StadiumSky->GetComponent<Transform>()->SetScale(Vector3(2.144f, 1.429f, 1.f));

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = IG_Stadium->AddComponent<ArrangementScript>();
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
	void IGStadiumScene::Update()
	{
		Scene::Update();
	}
	void IGStadiumScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void IGStadiumScene::Render()
	{
		Scene::Render();
	}
}