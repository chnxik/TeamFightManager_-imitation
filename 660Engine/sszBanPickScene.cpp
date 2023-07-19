#include "sszBanPickScene.h"
#include "CommonHeader.h"

#include "sszBattleHeader.h"
#include "sszBanLine.h"
#include "sszPlayerCardSlot.h"

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
			Resources::Load<Texture>(L"BanpickBgTex", L"..\\Resources\\useResource\\BanPick\\banpick_ui_bg.png");

			// Make Material
			LoadMaterial(L"BanpickBgMt", L"SpriteShader", L"BanpickBgTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Create Object for this Scene
#pragma region GameObject
		// GameObject
		{
			// BanpickBg
			GameObject* BanpickBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			BanpickBg->SetName(L"BanpickBg");
			BanpickBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BanpickBgMt");
		}
#pragma endregion
#pragma region UI
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.04f), eLayerType::UI, L"BattleHeaderBg");

			// BanLine
			BanLine* BanLineUI = InstantiateUI<BanLine>(Vector3(0.f, 353.f, 1.03f), eLayerType::UI, L"BanLine");

			PlayerCardSlot* RedPlayerCard_1 = InstantiateUI<PlayerCardSlot>(Vector3(843.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1");
			RedPlayerCard_1->SetRed();
			PlayerCardSlot* RedPlayerCard_2 = InstantiateUI<PlayerCardSlot>(Vector3(843.f, 69.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2");
			RedPlayerCard_2->SetRed();
			PlayerCardSlot* BluePlayerCard_1 = InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1");
			BluePlayerCard_1->SetBlue();
			PlayerCardSlot* BluePlayerCard_2 = InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 69.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2");
			BluePlayerCard_2->SetBlue();

			// 오브젝트 배치용 스크립트
			// BattleHeaderBg->AddComponent<ArrangementScript>()->SetDefault();
		}
#pragma endregion

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
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