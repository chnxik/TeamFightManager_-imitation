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

// Object
#include "sszObject.h"
#include "sszCursor.h"

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
	void BanPickScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
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
	}
	void BanPickScene::OnExit()
	{
	}
}