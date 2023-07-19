#include "sszMainLobbyScene.h"
#include "CommonHeader.h"

#include "sszLobbyMenuBtn.h"
#include "sszProceedBtn.h"

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

#pragma region Menu ButtonUI
				{
					// Menu Btn
					Vector3 MainMenuBtnSize(230.f, 70.f, 1.f);
					Vector3 MainMenuBtnPos[5] = {};

					for (int i = 0; i < 5; ++i)
					{
						float x = -810.f; // 버튼 첫 시작 x좌표
						x += (MainMenuBtnSize.x + 33.f) * i;
						float y = -440.f;
						MainMenuBtnPos[i] = Vector3(x, y, 1.001f);
					}

					LobbyMenuBtn* TeamManageMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[0], eLayerType::UI, L"TeamManageMenu");
					LobbyMenuBtn* OperateMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[1], eLayerType::UI, L"OperateMenu");
					LobbyMenuBtn* LeagueMenuBtn = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[2], eLayerType::UI, L"LeagueMenuBtn");
					LobbyMenuBtn* GameMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[3], eLayerType::UI, L"GameMenu");
					LobbyMenuBtn* SystemMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[4], eLayerType::UI, L"SystemMenu");
				}
#pragma endregion
#pragma region Proceed Btn
				{
					ProceedBtn* ProceedMenu = InstantiateUI<ProceedBtn>(Vector3(735.f, -430.f, 1.002f), eLayerType::UI,L"ProceedMenu");
					ProceedMenu->GetBtnComponent()->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"StadiumScene");
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