#include "sszBanPickScene.h"

#include "sszInput.h"
#include "sszSceneManager.h"
#include "sszCollisionManager.h"

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

namespace ssz
{
	using namespace object;

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
			// Texture Loading
			Resources::Load<Texture>(L"BanpickBgTex", L"..\\Resources\\useResource\\GameScene\\BanPick\\banpick_ui_bg.png");
			Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\GameScene\\header_bg.png");

			// Make Material
			std::shared_ptr<Material> BanpickBg_Mt = std::make_shared<Material>();
			BanpickBg_Mt->SetMaterial(L"SpriteShader", L"BanpickBgTex", eRenderingMode::Transparent);
			Resources::Insert(L"BanpickBgMt", BanpickBg_Mt);

			std::shared_ptr<Material> BattleHeader_Mt = std::make_shared<Material>();
			BattleHeader_Mt->SetMaterial(L"SpriteShader", L"BattleHeaderTex", eRenderingMode::Transparent);
			Resources::Insert(L"BattleHeaderMt", BattleHeader_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// BanpickBg
			GameObject* BanpickBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			BanpickBg->SetName(L"BanpickBg");
			BanpickBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BanpickBgMt");

			// Battle Header
			GameObject* BattleHeaderBg = Instantiate<GameObject>(Vector3(0.0f, 478.5f, 1.04f), Vector3(1920.f, 123.f, 1.f), eLayerType::BackGround);
			BattleHeaderBg->SetName(L"BattleHeaderBg");
			BattleHeaderBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BattleHeaderMt");

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = BattleHeaderBg->AddComponent<ArrangementScript>();
			ArScript->SetDefault();
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
	void BanPickScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::ENTER))
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
	void BanPickScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void BanPickScene::OnExit()
	{
		CollisionManager::Clear();
	}
}