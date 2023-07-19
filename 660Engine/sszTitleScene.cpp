#include "sszTitleScene.h"
#include "CommonHeader.h"

#include "sszNewGameWindow.h"
#include "sszDefaultBtn.h"
#include "sszImportantBtn.h"

namespace ssz
{
	using namespace object;

	TitleScene::TitleScene()
		: NewGameUI(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"TitleBg", L"..\\Resources\\useResource\\Title\\teamfight_manager_title_bg.png");
			Resources::Load<Texture>(L"IGStadiumSkyTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium_sky_bg.png");
			Resources::Load<Texture>(L"IGStadiumTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium.png");
			Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");

			LoadMaterial(L"TitleBgMt", L"SpriteShader", L"TitleBg", eRenderingMode::Transparent);
			LoadMaterial(L"IGStadiumMt", L"SpriteShader", L"IGStadiumTex", eRenderingMode::Transparent);
			LoadMaterial(L"IGStadiumSkyMt", L"SpriteShader", L"IGStadiumSkyTex", eRenderingMode::Transparent);
			LoadMaterial(L"TitleLogoMt", L"SpriteShader", L"TitleLogoTex", eRenderingMode::Transparent);
		}
#pragma region Create Object for this Scene
		// Bagk Ground
		{
			GameObject* TitleBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			TitleBg->SetName(L"TitleBg");
			TitleBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleBgMt");

			GameObject* IG_Stadium = Instantiate<GameObject>(Vector3(0.0f, -44.0f, 1.121f), Vector3(2235.f, 1460.f, 1.f), eLayerType::BackGroundObj);
			IG_Stadium->SetName(L"IG_Stadium");
			IG_Stadium->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.122f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* TitleLogo = Instantiate<GameObject>(Vector3(0.0f, 242.0f, 1.111f), Vector3(738.f, 271.f, 1.f), eLayerType::BackGroundObj);
			TitleLogo->SetName(L"TitleLogo");
			TitleLogo->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");
		}

		// UI
		{
			NewGameUI = InstantiateUI<NewGameWindow>(Vector3(0.f, 50.f, 1.01f), eLayerType::UI, L"NewGameWindow");
			NewGameUI->SetState(ssz::GameObject::eState::Paused);

			ImportantBtn* NewGameStartBtn = InstantiateUI<ImportantBtn>(Vector3(-123.f, -335.f, 1.009f), NewGameUI, L"NewGameStartBtn");
			NewGameStartBtn->GetBtnComponent()->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"MainLobbyScene");

			DefaultBtn* NewGameUICloseBtn = InstantiateUI<DefaultBtn>(Vector3(123.f, -335.f, 1.009f), NewGameUI, L"NewGameUICloseBtn");
			NewGameUICloseBtn->GetBtnComponent()->SetDelegate(NewGameUI, (DELEGATE)&GameObject::SetPaused);
		}

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
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			if (NewGameUI->GetState() == GameObject::eState::Paused)
			{
				NewGameUI->SetActive();
			}
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

	void TitleScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}

	void TitleScene::OnExit()
	{
		CollisionManager::Clear();
	}
}