#include "sszMainLobbyScene.h"
#include "CommonHeader.h"

#include "sszLobbyHeader.h"

#include "sszButtonUI.h"

#include "sszLobbyMenuBtn.h"
#include "sszProceedBtn.h"
#include "sszWeeklyEventBtn.h"

#include "sszCloudObj.h"

namespace ssz
{
	using namespace object;

	MainLobbyScene::MainLobbyScene()
		: BgSky(nullptr)
		, mLobbyheader(nullptr)
		, mCloud{}
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

			LoadMaterial(L"Bg_Skyday_Mt", L"SpriteShader", L"SkydayBgTex", eRenderingMode::Transparent);
			LoadMaterial(L"Bg_Ground_Mt", L"SpriteShader", L"BgGroundTex", eRenderingMode::Transparent);
			LoadMaterial(L"Bg_House_Mt", L"SpriteShader", L"BgHouseTex", eRenderingMode::Transparent);
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

				int idx = 0;
				for (CloudObj* obj : mCloud)
				{
					obj = Instantiate<CloudObj>(Vector3(0.0f, 0.0f, 1.0145f), Vector3(381.f, 117, 1.f), eLayerType::BackGroundObj);
					obj->SetMt(idx++);
				}
			}
#pragma endregion
#pragma region UI
			{
				// UI_Headerbar
				mLobbyheader = InstantiateUI<LobbyHeader>(Vector3(0.0f, 484.5f, 1.015f), eLayerType::UI, L"LobbyheaderBg");

#pragma region ButtonUI
				{
					Vector3 MainMenuBtnSize(230.f, 70.f, 1.f);
					Vector3 MainMenuBtnPos[5] = {};

					for (int i = 0; i < 5; ++i)
					{
						float x = -810.f; // 버튼 첫 시작 x좌표
						x += (MainMenuBtnSize.x + 33.f) * i;
						float y = -440.f;
						MainMenuBtnPos[i] = Vector3(x, y, 1.001f);
					}

					// Menu Btn
					LobbyMenuBtn* TeamManageMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[0], eLayerType::UI, L"TeamManageMenu");
					LobbyMenuBtn* OperateMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[1], eLayerType::UI, L"OperateMenu");
					LobbyMenuBtn* LeagueMenuBtn = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[2], eLayerType::UI, L"LeagueMenuBtn");
					LobbyMenuBtn* GameMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[3], eLayerType::UI, L"GameMenu");
					LobbyMenuBtn* SystemMenu = InstantiateUI<LobbyMenuBtn>(MainMenuBtnPos[4], eLayerType::UI, L"SystemMenu");

					Resources::Load<Texture>(L"TeamManageMenuTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\icon\\main_button_icon_0.png");
					Resources::Load<Texture>(L"OperateMenuTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\icon\\main_button_icon_1.png");
					Resources::Load<Texture>(L"LeagueMenuBtnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\icon\\main_button_icon_2.png");
					Resources::Load<Texture>(L"GameMenuTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\icon\\main_button_icon_3.png");
					Resources::Load<Texture>(L"SystemMenuTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\icon\\main_button_icon_4.png");

					TeamManageMenu->InitBtnIcon(L"TeamManageMenuTex", L"팀 관리");
					OperateMenu->InitBtnIcon(L"OperateMenuTex", L"운영");
					LeagueMenuBtn->InitBtnIcon(L"LeagueMenuBtnTex", L"대회");
					GameMenu->InitBtnIcon(L"GameMenuTex", L"게임");
					SystemMenu->InitBtnIcon(L"SystemMenuTex", L"시스템");
				
					// Proceed Btn
					ProceedBtn* ProceedMenu = InstantiateUI<ProceedBtn>(Vector3(735.f, -430.f, 1.002f), eLayerType::UI, L"ProceedMenu");
					ProceedMenu->GetBtnComponent()->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"StadiumScene");
	
					// WeeklyEvent Btn
					WeeklyEventBtn* WeeklyEventMenu = InstantiateUI<WeeklyEventBtn>(Vector3(735.f, -320.f, 1.002f), eLayerType::UI, L"WeeklyEventMenu");
				}
#pragma endregion
				
				// 오브젝트 배치용 스크립트
				// ProceedMenu->AddComponent<ArrangementScript>()->SetDefault();
			}
#pragma endregion
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
				
				for (CloudObj* obj : mCloud)
				{
					obj->SetDayTime(CloudObj::eDayTime::Sunset);
				}
				
				skyBg++;
				break;
			case 1:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkynightBgTex"));
				
				for (CloudObj* obj : mCloud)
				{
					obj->SetDayTime(CloudObj::eDayTime::Night);
				}
				
				skyBg++;
				break;
			case 2:
				BgSky->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"SkydayBgTex"));
				
				for (CloudObj* obj : mCloud)
				{
					obj->SetDayTime(CloudObj::eDayTime::Day);
				}
				
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
		// Save
		FileManager::OpenSaveFile(L"SaveFile.sav");
		
		wstring TeamName = TGM::GetPlayerTeam()->GetTeamName();
		
		FileManager::DataSave(TeamName);

		FileManager::CloseSaveFile();

		FileManager::OpenLoadFile(L"SaveFile.sav");
		
		TeamName = {};

		FileManager::DataLoad(TeamName);

		FileManager::CloseLoadFile();



		AddGameObject(eLayerType::Cursor, TGM::GetCursor());
		AddGameObject(eLayerType::Camera, TGM::GetCamera());

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);

		mLobbyheader->UpdateEnterScene();
	}
	void MainLobbyScene::OnExit()
	{
		CollisionManager::Clear();
		TGM::SceneClear();
	}
}