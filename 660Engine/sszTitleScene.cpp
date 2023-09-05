#include "sszTitleScene.h"
#include "CommonHeader.h"

#include "sszApplication.h"


#include "sszObj_IG_Stadium.h"

#include "sszTestEditBox.h"

// UI
#include "sszNewGameWindow.h"

// Btn
#include "sszDefaultBtn.h"
#include "sszImportantBtn.h"
#include "sszTitleMenuBtn.h"

extern ssz::Application application;

namespace ssz
{
	using namespace object;

	TitleScene::TitleScene()
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

			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -44.0f, 1.41f), Vector3(2235.f, 1460.f, 1.f), eLayerType::BackGroundObj);

			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.42f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			GameObject* TitleLogo = Instantiate<GameObject>(Vector3(0.0f, 242.0f, 1.31f), Vector3(738.f, 271.f, 1.f), eLayerType::BackGroundObj);
			TitleLogo->SetName(L"TitleLogo");
			TitleLogo->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TitleLogoMt");

			TestEditBox* TestEdit = Instantiate<TestEditBox>(Vector3(0.f, 0.f, 0.f), Vector3(200.f, 100.f, 1.f), eLayerType::BackGroundObj);
		}

		// UI
		{
			// Window
			UIObject* NewGameUI = InstantiateUI<NewGameWindow>(Vector3(0.f, 50.f, 1.05f), eLayerType::UI, L"NewGameWindow");
			NewGameUI->SetState(ssz::GameObject::eState::Paused);


			//Btn
			TitleMenuBtn* NewGameBtn = InstantiateUI<TitleMenuBtn>(Vector3(0.f, 10.f, 1.2f), Vector3(100.f, 50.f, 1.f), eLayerType::UI, L"TitleNewGameBtn");
			NewGameBtn->SetNewGameBtn();
			NewGameBtn->GetBtnComponent()->SetDelegate(NewGameUI, (DELEGATE)&GameObject::SetActive);
			
			TitleMenuBtn* LoadBtn = InstantiateUI<TitleMenuBtn>(Vector3(0.f, -90.f, 1.2f), Vector3(100.f, 50.f, 1.f), eLayerType::UI, L"TitleLoadBtn");
			LoadBtn->SetLoadBtn();
			
			TitleMenuBtn* ExitBtn = InstantiateUI<TitleMenuBtn>(Vector3(0.f, -190.f, 1.2f), Vector3(100.f, 50.f, 1.f), eLayerType::UI, L"TitleExitBtn");
			ExitBtn->SetExitBtn();
			ExitBtn->GetBtnComponent()->SetDelegate(this, (DELEGATE)&TitleScene::ExitProgram);

			ImportantBtn* NewGameStartBtn = InstantiateUI<ImportantBtn>(Vector3(-123.f, -335.f, 1.049f), NewGameUI, L"NewGameStartBtn");
			NewGameStartBtn->GetBtnComponent()->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"MainLobbyScene");
			Text* StartBtnText = NewGameStartBtn->AddComponent<Text>();
			StartBtnText->SetFontSize(30);
			StartBtnText->SetFlags(FW1_CENTER | FW1_VCENTER);
			StartBtnText->SetString(L"���� ����");

			DefaultBtn* NewGameUICloseBtn = InstantiateUI<DefaultBtn>(Vector3(123.f, -335.f, 1.049f), NewGameUI, L"NewGameUICloseBtn");
			NewGameUICloseBtn->GetBtnComponent()->SetDelegate(NewGameUI, (DELEGATE)&GameObject::SetPaused);
			Text* CloseBtnText = NewGameUICloseBtn->AddComponent<Text>();
			CloseBtnText->SetFontSize(30);
			CloseBtnText->SetFlags(FW1_CENTER | FW1_VCENTER);
			CloseBtnText->SetString(L"���");
		}

		
#pragma endregion
	}
	void TitleScene::Update()
	{
		Scene::Update();
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
		AddGameObject(eLayerType::Cursor, TGM::GetCursor());
		AddGameObject(eLayerType::Camera, TGM::GetCamera());

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}

	void TitleScene::OnExit()
	{
		CollisionManager::Clear();
		TGM::SceneClear();
	}

	void TitleScene::ExitProgram()
	{
		SendMessage(application.GetHwnd(), WM_DESTROY, 0, 0);
	}
}