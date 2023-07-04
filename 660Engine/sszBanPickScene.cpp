#include "sszBanPickScene.h"

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
	BanPickScene::BanPickScene()
	{
	}
	BanPickScene::~BanPickScene()
	{
	}
	void BanPickScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> BanpickBgTex = Resources::Load<Texture>(L"BanpickBgTex", L"..\\Resources\\useResource\\GameScene\\BanPick\\banpick_ui_bg.png");

			std::shared_ptr<Texture> BattleHeaderTex = Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\GameScene\\header_bg.png");


			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> BanpickBg_Mt = std::make_shared<Material>();
			BanpickBg_Mt->SetShader(SpriteShader);
			BanpickBg_Mt->SetTexture(BanpickBgTex);
			BanpickBg_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"BanpickBgMt", BanpickBg_Mt);

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
			// BanpickBg
			GameObject* BanpickBg = new GameObject();
			BanpickBg->SetName(L"BanpickBg");
			AddGameObject(eLayerType::BackGround, BanpickBg);

			MeshRenderer* BanpickBg_mr = BanpickBg->AddComponent<MeshRenderer>();
			BanpickBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BanpickBg_mr->SetMaterial(Resources::Find<Material>(L"BanpickBgMt"));
			BanpickBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.1f));
			BanpickBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.f));
			
			// Battle Header
			GameObject* BattleHeaderBg = new GameObject();
			BattleHeaderBg->SetName(L"BattleHeaderBg");
			AddGameObject(eLayerType::BackGround, BattleHeaderBg);

			MeshRenderer* BattleHeaderBg_mr = BattleHeaderBg->AddComponent<MeshRenderer>();
			BattleHeaderBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BattleHeaderBg_mr->SetMaterial(Resources::Find<Material>(L"BattleHeaderMt"));
			BattleHeaderBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.4785f, 1.04f));
			BattleHeaderBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 0.123f, 1.f));

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = Stadium_frame_Bg->AddComponent<ArrangementScript>();
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
	void BanPickScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			SceneManager::LoadScene(L"IGStadiumScene");
		}
	}
	void BanPickScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void BanPickScene::Render()
	{
		Scene::Render();
	}
}