#include "sszTestScene.h"

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
#include "sszMasking.h"

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"

namespace ssz
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			std::shared_ptr<Shader> MaskShader = ssz::Resources::Find<Shader>(L"MaskShader");
			

			// Get Using Texture
			std::shared_ptr<Texture> TestUI = Resources::Load<Texture>(L"TestUI", L"..\\Resources\\useResource\\GameScene\\BanPick\\banpick_ui_bg.png");
			
			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> TestUI_Mt = std::make_shared<Material>();
			TestUI_Mt->SetShader(MaskShader);
			TestUI_Mt->SetTexture(TestUI);
			TestUI_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TestUI_Mt", TestUI_Mt);

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
			GameObject* TestUI = new GameObject();
			TestUI->SetName(L"TitleBg");
			AddGameObject(eLayerType::BackGround, TestUI);

			MeshRenderer* TestUI_mr = TestUI->AddComponent<MeshRenderer>();
			TestUI_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TestUI_mr->SetMaterial(Resources::Find<Material>(L"TestUI_Mt"));
			TestUI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));

			Vector2 TextureSize = TestUI_mr->GetMaterial()->GetTexture()->GetTextureSize() / 1000.f * 3.f;
			TestUI->GetComponent<Transform>()->SetScale(Vector3(TextureSize.x, TextureSize.y, 1.f));
			TestUI->AddComponent<Masking>();

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = TestUI->AddComponent<ArrangementScript>();
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
			Cursor->AddComponent<CursorScript>()->Initialize();
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