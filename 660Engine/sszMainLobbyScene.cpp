#include "sszMainLobbyScene.h"
#include "CommonHeader.h"

namespace ssz
{
	using namespace object;

	MainLobbyScene::MainLobbyScene()
		: BgSky(nullptr)
	{
	}

	MainLobbyScene::~MainLobbyScene()
	{
	}

	void MainLobbyScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"SkydayBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_day.png");
			Resources::Load<Texture>(L"SkynightBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_night.png");
			Resources::Load<Texture>(L"SkysunsetBgTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\sky\\sky_sunset.png");
			Resources::Load<Texture>(L"BgGroundTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\Ground\\ground.png");
			Resources::Load<Texture>(L"BgHouseTex", L"..\\Resources\\useResource\\Mainlobby\\Bg\\house\\house_bg.png");

			Resources::Load<Texture>(L"UIheaderBarTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_bg.png");

			Resources::Load<Texture>(L"MainMenuBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_0.png");
			Resources::Load<Texture>(L"MainMenuBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_1.png");
			Resources::Load<Texture>(L"MainMenuBtnDownTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_2.png");

			Resources::Load<Texture>(L"ProceedBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_0.png");
			Resources::Load<Texture>(L"ProceedBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_1.png");
			Resources::Load<Texture>(L"ProceedBtnArrowTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_2.png");
			Resources::Load<Texture>(L"ProceedBtnDownTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_3.png");

			Resources::Load<Texture>(L"WeeklyEventRedBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_0.png");
			Resources::Load<Texture>(L"WeeklyEventRedBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_1.png");
			Resources::Load<Texture>(L"WeeklyEventGrayBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_3.png");
			Resources::Load<Texture>(L"WeeklyEventGrayBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_4.png");

			Resources::Load<Texture>(L"UIheaderSlotBgTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_slot_bg.png");
		}
		{
			LoadMaterial(L"Bg_Skyday_Mt", L"SpriteShader", L"SkydayBgTex", eRenderingMode::Transparent);
			LoadMaterial(L"Bg_Ground_Mt", L"SpriteShader", L"BgGroundTex", eRenderingMode::Transparent);
			LoadMaterial(L"Bg_House_Mt", L"SpriteShader", L"BgHouseTex", eRenderingMode::Transparent);
			LoadMaterial(L"UI_headerBar_Mt", L"SpriteShader", L"UIheaderBarTex", eRenderingMode::Transparent);

			LoadMaterial(L"MainMenuBtnIdleMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"ProceedBtnIdleMt", L"SpriteShader", L"ProceedBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"ProceedBtnArrowMt", L"SpriteShader", L"ProceedBtnArrowTex", eRenderingMode::Transparent);

			LoadMaterial(L"TeamManageMenuBtnMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"OperateMenuBtnMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"LeagueMenuBtnMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"GameMenuBtnMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"SystemMenuBtnMt", L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);

			LoadMaterial(L"WeeklyEventBtnIdleMt", L"SpriteShader", L"WeeklyEventRedBtnIdleTex", eRenderingMode::Transparent);

			LoadMaterial(L"UIheaderSlotBgMt", L"SpriteShader", L"UIheaderSlotBgTex",eRenderingMode::Transparent);
		}
#pragma region Create Object for this Scene
		// GameObject
		{
#pragma region BgObj
			{
				// Bg_Sky
				GameObject* Bg_Sky = Instantiate<GameObject>(Vector3(0.0f, 166.f, 1.1f), Vector3(1920.f, 1920.f, 1.f), eLayerType::BackGround);
				Bg_Sky->SetName(L"Bg_Sky");
				Bg_Sky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_Skyday_Mt");
				BgSky = Bg_Sky;

				// Bg_Ground
				GameObject* Bg_Ground = Instantiate<GameObject>(Vector3(0.0f, -412.f, 1.015f), Vector3(1920.f, 256.f, 1.f), eLayerType::BackGround);
				Bg_Ground->SetName(L"Bg_Ground");
				Bg_Ground->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_Ground_Mt");

				// Bg_House
				GameObject* Bg_House = Instantiate<GameObject>(Vector3(0.0f, -28.f, 1.014f), Vector3(668.f, 512.f, 1.f), eLayerType::BackGroundObj);
				Bg_House->SetName(L"Bg_House");
				Bg_House->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Bg_House_Mt");
			}
#pragma endregion
#pragma region UI
			{
				// UI_Headerbar
				UIObject* UI_headerBar = Instantiate<UIObject>(Vector3(0.0f, 484.5f, 1.015f), Vector3(1920.f, 111.f, 1.f), eLayerType::UI);
				UI_headerBar->SetName(L"UI_header_Bar");
				UI_headerBar->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UI_headerBar_Mt");
				UI_headerBar->AddComponent<Collider2D>()->Initialize();

#pragma region Menu Button
				{
					// Menu Btn
					Vector3 MainMenuBtnSize(230.f, 60.f, 1.f);
					Vector3 MainMenuBtnPos[5] = {};

					for (int i = 0; i < 5; ++i)
					{
						float x = -810.f; // 버튼 첫 시작 x좌표
						x += (MainMenuBtnSize.x + 27.f) * i;
						float y = -460.f;
						MainMenuBtnPos[i] = Vector3(x, y, 1.001f);
					}

					UIObject* TeamManageMenu = Instantiate<UIObject>(MainMenuBtnPos[0], MainMenuBtnSize, eLayerType::UI);
					TeamManageMenu->SetName(L"TeamManageMenuBtn");
					TeamManageMenu->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TeamManageMenuBtnMt");
					TeamManageMenu->AddComponent<Collider2D>()->Initialize();

					Button* TeamManageMenuBtn = TeamManageMenu->AddComponent<Button>();
					TeamManageMenuBtn->Initialize();
					TeamManageMenuBtn->SetIdleTex(L"MainMenuBtnIdleTex");
					TeamManageMenuBtn->SetOnTex(L"MainMenuBtnOnTex");
					TeamManageMenuBtn->SetDownTex(L"MainMenuBtnDownTex");

					UIObject* OperateMenu = Instantiate<UIObject>(MainMenuBtnPos[1], MainMenuBtnSize, eLayerType::UI);
					OperateMenu->SetName(L"OperateMenuBtn");
					OperateMenu->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"OperateMenuBtnMt");
					OperateMenu->AddComponent<Collider2D>()->Initialize();

					Button* OperateMenuBtn = OperateMenu->AddComponent<Button>();
					OperateMenuBtn->Initialize();
					OperateMenuBtn->SetIdleTex(L"MainMenuBtnIdleTex");
					OperateMenuBtn->SetOnTex(L"MainMenuBtnOnTex");
					OperateMenuBtn->SetDownTex(L"MainMenuBtnDownTex");

					UIObject* LeagueMenu = Instantiate<UIObject>(MainMenuBtnPos[2], MainMenuBtnSize, eLayerType::UI);
					LeagueMenu->SetName(L"LeagueMenuBtn");
					LeagueMenu->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LeagueMenuBtnMt");
					LeagueMenu->AddComponent<Collider2D>()->Initialize();

					Button* LeagueMenuBtn = LeagueMenu->AddComponent<Button>();
					LeagueMenuBtn->Initialize();
					LeagueMenuBtn->SetIdleTex(L"MainMenuBtnIdleTex");
					LeagueMenuBtn->SetOnTex(L"MainMenuBtnOnTex");
					LeagueMenuBtn->SetDownTex(L"MainMenuBtnDownTex");

					UIObject* GameMenu = Instantiate<UIObject>(MainMenuBtnPos[3], MainMenuBtnSize, eLayerType::UI);
					GameMenu->SetName(L"GameMenuBtn");
					GameMenu->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"GameMenuBtnMt");
					GameMenu->AddComponent<Collider2D>()->Initialize();

					Button* GameMenuBtn = GameMenu->AddComponent<Button>();
					GameMenuBtn->Initialize();
					GameMenuBtn->SetIdleTex(L"MainMenuBtnIdleTex");
					GameMenuBtn->SetOnTex(L"MainMenuBtnOnTex");
					GameMenuBtn->SetDownTex(L"MainMenuBtnDownTex");

					UIObject* SystemMenu = Instantiate<UIObject>(MainMenuBtnPos[4], MainMenuBtnSize, eLayerType::UI);
					SystemMenu->SetName(L"SystemMenuBtn");
					SystemMenu->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SystemMenuBtnMt");
					SystemMenu->AddComponent<Collider2D>()->Initialize();

					Button* SystemMenuBtn = SystemMenu->AddComponent<Button>();
					SystemMenuBtn->Initialize();
					SystemMenuBtn->SetIdleTex(L"MainMenuBtnIdleTex");
					SystemMenuBtn->SetOnTex(L"MainMenuBtnOnTex");
					SystemMenuBtn->SetDownTex(L"MainMenuBtnDownTex");
				}
#pragma endregion
#pragma region Proceed Btn
				{
					// ProceedBtn
					UIObject* ProceedBtn = Instantiate<UIObject>(Vector3(735.f, -430.f, 1.002f), Vector3(340.f, 120.f, 1.f), eLayerType::UI);
					ProceedBtn->SetName(L"ProceedMenuBtn");
					ProceedBtn->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ProceedBtnIdleMt");
					ProceedBtn->AddComponent<Collider2D>()->Initialize();

					Button* ProceedBtnComp = ProceedBtn->AddComponent<Button>();
					ProceedBtnComp->Initialize();
					ProceedBtnComp->SetIdleTex(L"ProceedBtnIdleTex");
					ProceedBtnComp->SetOnTex(L"ProceedBtnOnTex");
					ProceedBtnComp->SetDownTex(L"ProceedBtnDownTex");
					ProceedBtnComp->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"StadiumScene");

					UIObject* ProceedArrow = InstantiateUI<UIObject>(Vector3(97.f, 0.f, -0.001f), Vector3(-195.f, 0.f, 0.f), ProceedBtn, false);
					ProceedArrow->SetName(L"ProceedMenuBtnArrow");
					ProceedArrow->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ProceedBtnArrowMt");
					Transform* Proceedtr = ProceedArrow->GetComponent<Transform>();
					Proceedtr->SetParent(ProceedBtn->GetComponent<Transform>());
					Proceedtr->SetTransTypeADD();

				}
#pragma endregion
#pragma region WeeklyEvent Btn
				{
					// WeeklyEventBtn
					UIObject* WeeklyEventBtn = Instantiate<UIObject>(Vector3(735.f, -320.f, 1.002f), Vector3(340.f, 60.f, 1.f), eLayerType::UI);
					WeeklyEventBtn->SetName(L"WeeklyEventBtn");
					WeeklyEventBtn->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"WeeklyEventBtnIdleMt");
					WeeklyEventBtn->AddComponent<Collider2D>()->Initialize();
				}
#pragma endregion

				// UI header Slot
				UIObject* HeaderGoldSlotUI = Instantiate<UIObject>(Vector3(775.f, 485.f, 1.002f), Vector3(339.f, 72.f, 1.f), eLayerType::UI);
				HeaderGoldSlotUI->SetName(L"HeaderGoldSlotUI");
				HeaderGoldSlotUI->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UIheaderSlotBgMt");

				UIObject* HeaderDaySlotUI = Instantiate<UIObject>(Vector3(416.f, 485.f, 1.002f), Vector3(339.f, 72.f, 1.f), eLayerType::UI);
				HeaderDaySlotUI->SetName(L"HeaderDaySlotUI");
				HeaderDaySlotUI->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UIheaderSlotBgMt");

				// 오브젝트 배치용 스크립트
				// ArrangementScript* ArScript = UI_headerBar->AddComponent<ArrangementScript>();
				// ArScript->SetDefault();
			}
#pragma endregion
		}

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");

			// Init
			Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");
			LoadMaterial(L"CursorMt", L"SpriteShader", L"CursorTex", eRenderingMode::Transparent);

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

	void MainLobbyScene::Update()
	{
		Scene::Update();

		static UINT skyBg = 0;

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			switch (skyBg)
			{
			case 0:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture (Resources::Find<Texture>(L"SkysunsetBgTex"));
				skyBg++;
				break;
			case 1:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkynightBgTex"));
				skyBg++;
				break;
			case 2:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkydayBgTex"));
				skyBg = 0;
				break;
			}
		}
	}

	void MainLobbyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MainLobbyScene::Render()
	{
		Scene::Render();
	}
	void MainLobbyScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void MainLobbyScene::OnExit()
	{
		CollisionManager::Clear();
	}
}