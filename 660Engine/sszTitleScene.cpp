#include "sszTitleScene.h"
#include "CommonHeader.h"

#include "sszObj_IG_Stadium.h"

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
			Resources::Load<Texture>(L"TitleLogoTex", L"..\\Resources\\useResource\\Title\\logo_tp.png");

			LoadMaterial(L"TitleBgMt", L"SpriteShader", L"TitleBg", eRenderingMode::Transparent);
			LoadMaterial(L"IGStadiumSkyMt", L"SpriteShader", L"IGStadiumSkyTex", eRenderingMode::Transparent);
			LoadMaterial(L"TitleLogoMt", L"SpriteShader", L"TitleLogoTex", eRenderingMode::Transparent);
		}
#pragma region Create Object for this Scene
		// Bagk Ground
		{
			GameObject* TitleBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			TitleBg->SetName(L"TitleBg");
			TitleBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleBgMt");

			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -44.0f, 1.121f), Vector3(2235.f, 1460.f, 1.f), eLayerType::BackGroundObj);

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
		Cursor::RegistCursor(this);
		MainCamera::RegistCamera(this);

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}

	void TitleScene::OnExit()
	{
		CollisionManager::Clear();

		Erase(eLayerType::Cursor);
		Erase(eLayerType::Camera);
	}
}