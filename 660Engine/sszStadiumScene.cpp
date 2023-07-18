#include "sszStadiumScene.h"
#include "CommonHeader.h"

namespace ssz
{
	using namespace object;

	StadiumScene::StadiumScene()
	{
	}
	StadiumScene::~StadiumScene()
	{
	}
	void StadiumScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"StadiumTex", L"..\\Resources\\useResource\\stadium\\stadium_bg.png");
			Resources::Load<Texture>(L"Stadium_ChairTex", L"..\\Resources\\useResource\\stadium\\stadium_chair.png");
			Resources::Load<Texture>(L"Stadium_deskTex", L"..\\Resources\\useResource\\stadium\\stadium_desk.png");
			Resources::Load<Texture>(L"Stadium_frameTex", L"..\\Resources\\useResource\\stadium\\stadium_frame.png");
			Resources::Load<Texture>(L"Stadium_frame_frontTex", L"..\\Resources\\useResource\\stadium\\stadium_frame_front.png");
			Resources::Load<Texture>(L"Stadium_frame_BgTex", L"..\\Resources\\useResource\\stadium\\frame_bg.png");

			Resources::Load<Texture>(L"LineUpUITex", L"..\\Resources\\useResource\\stadium\\UI\\multi_lineup_ui_bg.png");
			Resources::Load<Texture>(L"LineUpUI_Highlight_SlotStartingMemTex", L"..\\Resources\\useResource\\stadium\\UI\\highlighted_slot_starting_member_bg.png");
			Resources::Load<Texture>(L"LineUpUI_Highlight_SlotSubMemTex", L"..\\Resources\\useResource\\stadium\\UI\\highlighted_slot_sub_bg.png");

			Resources::Load<Texture>(L"LineUpUI_Blue_Left_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_0.png");
			Resources::Load<Texture>(L"LineUpUI_Blue_Right_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_1.png");
			Resources::Load<Texture>(L"LineUpUI_Red_Left_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_3.png");
			Resources::Load<Texture>(L"LineUpUI_Red_Right_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_2.png");

			Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_0.png");
			Resources::Load<Texture>(L"BluePlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_1.png");
			Resources::Load<Texture>(L"BluePlayerCardHighlightedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_2.png");
			Resources::Load<Texture>(L"RedPlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_4.png");
			Resources::Load<Texture>(L"RedPlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_5.png");
			Resources::Load<Texture>(L"RedPlayerCardHighlightedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_6.png");

			Resources::Load<Texture>(L"PlayerChangeIconTex", L"..\\Resources\\useResource\\stadium\\UI\\player_change_icon_0.png");
			Resources::Load<Texture>(L"PlayerChangeIconHighlightTex", L"..\\Resources\\useResource\\stadium\\UI\\player_change_icon_1.png");
		}

		{
			LoadMaterial(L"StadiumMt", L"SpriteShader", L"StadiumTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_chairMt", L"SpriteShader", L"Stadium_ChairTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_deskMt", L"SpriteShader", L"Stadium_deskTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frameMt", L"SpriteShader", L"Stadium_frameTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frame_frontMt", L"SpriteShader", L"Stadium_frame_frontTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frame_BgMt", L"SpriteShader", L"Stadium_frame_BgTex", eRenderingMode::Transparent);

			//UI
			LoadMaterial(L"LineUpUIBgMt", L"SpriteShader", L"LineUpUITex", eRenderingMode::Transparent);
			LoadMaterial(L"LineUpUI_SlotStartingMem_HighlightMt", L"SpriteShader", L"LineUpUI_Highlight_SlotStartingMemTex", eRenderingMode::Transparent);
			LoadMaterial(L"LineUpUI_SlotSub_HighlightMt", L"SpriteShader", L"LineUpUI_Highlight_SlotSubMemTex", eRenderingMode::Transparent);
			
			LoadMaterial(L"LineUpUI_PlayerTeamTitle_Mt", L"SpriteShader", L"LineUpUI_Red_Left_TTTex", eRenderingMode::Transparent);
			LoadMaterial(L"LineUpUI_EnemyTeamTitle_Mt", L"SpriteShader", L"LineUpUI_Blue_Right_TTTex", eRenderingMode::Transparent);
			LoadMaterial(L"PlayerChangeIconMt", L"SpriteShader", L"PlayerChangeIconTex", eRenderingMode::Transparent);
			
			LoadMaterial(L"PlayerTeam_1_CardMt", L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"PlayerTeam_2_CardMt", L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"PlayerTeam_3_CardMt", L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"PlayerTeam_Sub1_CardMt", L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"PlayerTeam_Sub2_CardMt", L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"EnemyTeam_1_CardMt", L"SpriteShader", L"BluePlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"EnemyTeam_2_CardMt", L"SpriteShader", L"BluePlayerCardIdleTex", eRenderingMode::Transparent);
			LoadMaterial(L"EnemyTeam_3_CardMt", L"SpriteShader", L"BluePlayerCardIdleTex", eRenderingMode::Transparent);

			LoadMaterial(L"LineUpUI_CorrectBtnMt", L"SpriteShader", L"DefaultBtn_IdleTex", eRenderingMode::Transparent);
		}
#pragma region Create Object for this Scene
		// GameObject
		{
			// StadiumBg
			GameObject* StadiumBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			StadiumBg->SetName(L"StadiumBg");
			StadiumBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"StadiumMt");

			// Stadium Chair
			GameObject* Stadium_Chair = Instantiate<GameObject>(Vector3(0.0f, -115.f, 1.03f), Vector3(1197.f, 143.f, 1.f), eLayerType::BackGround);
			Stadium_Chair->SetName(L"StadiumChair");
			Stadium_Chair->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_chairMt");
			
			// Stadium Desk
			GameObject* Stadium_desk = Instantiate<GameObject>(Vector3(0.0f, -147.f, 1.02f), Vector3(1273.f, 141.f, 1.f), eLayerType::BackGround);
			Stadium_desk->SetName(L"StadiumDesk");
			Stadium_desk->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_deskMt");
			
			// Stadium frame
			GameObject* Stadium_frame = Instantiate<GameObject>(Vector3(0.0f, -100.f, 1.04f), Vector3(1735.f, 200.f, 1.f), eLayerType::BackGround);
			Stadium_frame->SetName(L"StadiumFrame");
			Stadium_frame->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frameMt");
			
			// Stadium frame front
			GameObject* Stadium_frame_front = Instantiate<GameObject>(Vector3(0.0f, -232.f, 1.01f), Vector3(1768.f, 80.f, 1.f), eLayerType::BackGround);
			Stadium_frame_front->SetName(L"StadiumFrameFront");
			Stadium_frame_front->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frame_frontMt");
			
			// Stadium frame Bg
			GameObject* Stadium_frame_Bg = Instantiate<GameObject>(Vector3(0.0f, -100.f, 1.05f), Vector3(1252.f, 160.f, 1.f), eLayerType::BackGround);
			Stadium_frame_Bg->SetName(L"StadiumframeBg");
			Stadium_frame_Bg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frame_BgMt");
		}

		// UI
		{
#pragma region LineUpUI
			UIObject* LineUpUI = Instantiate<UIObject>(Vector3(0.f, 0.f, 1.004f), Vector3(1630.f, 850.f, 1.f), eLayerType::UI);
			LineUpUI->SetName(L"LineUpUIBg");
			LineUpUI->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh",L"LineUpUIBgMt");
			LineUpUI->AddComponent<Collider2D>()->Initialize();

			UIObject* PlayerTeamTitle = InstantiateUI<UIObject>(Vector3(-522.f, 240.f, 1.003f), Vector3(500.f, 70.f, 1.f), LineUpUI, false);
			PlayerTeamTitle->SetName(L"LineUp_PlayerTeamTitle");
			PlayerTeamTitle->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LineUpUI_PlayerTeamTitle_Mt");

			UIObject* EnemyTeamTitle = InstantiateUI<UIObject>(Vector3(523.f, 240.f, 1.003f), Vector3(500.f, 70.f, 1.f), LineUpUI, false);
			EnemyTeamTitle->SetName(L"LineUp_EnemyTeamTitle");
			EnemyTeamTitle->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LineUpUI_EnemyTeamTitle_Mt");

			UIObject* PlayerTeamCharCard_1 = InstantiateUI<UIObject>(Vector3(-650.f, 74.f, 1.003f), Vector3(235.f, 226.f, 1.f), LineUpUI, true);
			PlayerTeamCharCard_1->SetName(L"PlayerTeamCharCard_1");
			PlayerTeamCharCard_1->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerTeam_1_CardMt");
			Button* PTCharCard_1_Btn = PlayerTeamCharCard_1->AddComponent<Button>();
			PTCharCard_1_Btn->Initialize();
			PTCharCard_1_Btn->SetIdleTex(L"RedPlayerCardIdleTex");
			PTCharCard_1_Btn->SetOnTex(L"RedPlayerCardOnTex");
			PTCharCard_1_Btn->SetDownTex(L"RedPlayerCardHighlightedTex");

			UIObject* PlayerTeamCharCard_2 = InstantiateUI<UIObject>(Vector3(-395, 74.f, 1.003f), Vector3(235.f, 226.f, 1.f), LineUpUI, true);
			PlayerTeamCharCard_2->SetName(L"PlayerTeamCharCard_2");
			PlayerTeamCharCard_2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerTeam_2_CardMt");
			Button* PTCharCard_2_Btn = PlayerTeamCharCard_2->AddComponent<Button>();
			PTCharCard_2_Btn->Initialize();
			PTCharCard_2_Btn->SetIdleTex(L"RedPlayerCardIdleTex");
			PTCharCard_2_Btn->SetOnTex(L"RedPlayerCardOnTex");
			PTCharCard_2_Btn->SetDownTex(L"RedPlayerCardHighlightedTex");

			UIObject* PlayerTeamSubCharCard_1 = InstantiateUI<UIObject>(Vector3(65.f, 74.f, 1.003f), Vector3(235.f, 226.f, 1.f), LineUpUI, true);
			PlayerTeamSubCharCard_1->SetName(L"PlayerTeamSubCharCard_1");
			PlayerTeamSubCharCard_1->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerTeam_Sub1_CardMt");
			Button* PTSubCharCard_1_Btn = PlayerTeamSubCharCard_1->AddComponent<Button>();
			PTSubCharCard_1_Btn->Initialize();
			PTSubCharCard_1_Btn->SetIdleTex(L"RedPlayerCardIdleTex");
			PTSubCharCard_1_Btn->SetOnTex(L"RedPlayerCardOnTex");
			PTSubCharCard_1_Btn->SetDownTex(L"RedPlayerCardHighlightedTex");

			UIObject* EnemyTeamCharCard_1 = InstantiateUI<UIObject>(Vector3(399.f, 74.f, 1.003f), Vector3(235.f, 226.f, 1.f), LineUpUI, true);
			EnemyTeamCharCard_1->SetName(L"EnemyTeamCharCard_1");
			EnemyTeamCharCard_1->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"EnemyTeam_1_CardMt");
			Button* ETCharCard_1_Btn = EnemyTeamCharCard_1->AddComponent<Button>();
			ETCharCard_1_Btn->Initialize();
			ETCharCard_1_Btn->SetIdleTex(L"BluePlayerCardIdleTex");
			ETCharCard_1_Btn->SetOnTex(L"BluePlayerCardOnTex");
			ETCharCard_1_Btn->SetDownTex(L"BluePlayerCardHighlightedTex");

			UIObject* EnemyTeamCharCard_2 = InstantiateUI<UIObject>(Vector3(652.f, 74.f, 1.003f), Vector3(235.f, 226.f, 1.f), LineUpUI, true);
			EnemyTeamCharCard_2->SetName(L"EnemyTeamCharCard_2");
			EnemyTeamCharCard_2->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"EnemyTeam_2_CardMt");
			Button* ETCharCard_2_Btn = EnemyTeamCharCard_2->AddComponent<Button>();
			ETCharCard_2_Btn->Initialize();
			ETCharCard_2_Btn->SetIdleTex(L"BluePlayerCardIdleTex");
			ETCharCard_2_Btn->SetOnTex(L"BluePlayerCardOnTex");
			ETCharCard_2_Btn->SetDownTex(L"BluePlayerCardHighlightedTex");

			UIObject* PlayerChangeIcon = InstantiateUI<UIObject>(Vector3(-159.f, 3.f, 1.003f),Vector3(135.f,120.f,1.f),LineUpUI,true);
			PlayerChangeIcon->SetName(L"PlayerChangeIcon");
			PlayerChangeIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerChangeIconMt");


			UIObject* LineUpCorrectBtn = InstantiateUI<UIObject>(Vector3(0.f, -368.f, 1.003f), Vector3(207.f, 75.f, 1.f), LineUpUI, true);
			LineUpCorrectBtn->SetName(L"DefaultUI");
			LineUpCorrectBtn->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LineUpUI_CorrectBtnMt");
			Button* LineUpCorrectBtnComp = LineUpCorrectBtn->AddComponent<Button>();
			LineUpCorrectBtnComp->Initialize();
			LineUpCorrectBtnComp->SetIdleTex(L"DefaultBtn_IdleTex");
			LineUpCorrectBtnComp->SetOnTex(L"DefaultBtn_OnTex");
			LineUpCorrectBtnComp->SetDownTex(L"DefaultBtn_DownTex");
			LineUpCorrectBtnComp->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"BanPickScene");
#pragma endregion

			// 오브젝트 배치용 스크립트
			// PlayerChangeIcon->AddComponent<ArrangementScript>()->SetDefault();
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
	void StadiumScene::Update()
	{
		Scene::Update();
	}
	void StadiumScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void StadiumScene::Render()
	{
		Scene::Render();
	}
	void StadiumScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void StadiumScene::OnExit()
	{
		CollisionManager::Clear();
	}
}