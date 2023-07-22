#include "sszStadiumScene.h"
#include "CommonHeader.h"

#include "sszLineUpWindow.h"
#include "sszPlayerCardBtn.h"
#include "sszDefaultBtn.h"

namespace ssz
{
	using namespace object;

	StadiumScene::StadiumScene()
		: LineUpWin(nullptr)
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

			Resources::Load<Texture>(L"LineUpUI_Highlight_SlotStartingMemTex", L"..\\Resources\\useResource\\stadium\\UI\\highlighted_slot_starting_member_bg.png");
			Resources::Load<Texture>(L"LineUpUI_Highlight_SlotSubMemTex", L"..\\Resources\\useResource\\stadium\\UI\\highlighted_slot_sub_bg.png");

			LoadMaterial(L"StadiumMt", L"SpriteShader", L"StadiumTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_chairMt", L"SpriteShader", L"Stadium_ChairTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_deskMt", L"SpriteShader", L"Stadium_deskTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frameMt", L"SpriteShader", L"Stadium_frameTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frame_frontMt", L"SpriteShader", L"Stadium_frame_frontTex", eRenderingMode::Transparent);
			LoadMaterial(L"Stadium_frame_BgMt", L"SpriteShader", L"Stadium_frame_BgTex", eRenderingMode::Transparent);

			//UI
			Resources::Load<Texture>(L"PlayerChangeIconTex", L"..\\Resources\\useResource\\stadium\\UI\\player_change_icon_0.png");
			LoadMaterial(L"PlayerChangeIconMt", L"SpriteShader", L"PlayerChangeIconTex", eRenderingMode::Transparent);
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
			LineUpWindow* LineUpUI = InstantiateUI<LineUpWindow>(Vector3(0.f, 0.f, 1.004f), eLayerType::UI, L"LineUpWindowBg");
			LineUpUI->SetPlayerTeamTitle(eTeamColor::Red);
			LineUpUI->SetEnemyTeamTitle(eTeamColor::Blue);
			LineUpUI->SetState(ssz::GameObject::eState::Paused);

			LineUpWin = LineUpUI;
			
			DefaultBtn* LineUpProgressBtn = InstantiateUI<DefaultBtn>(Vector3(0.f, -368.f, 1.003f), LineUpUI, L"LineUpProgressBtn");
			LineUpProgressBtn->GetBtnComponent()->SetDelegateW(this, (DELEGATEW)&Scene::ChangeScene, L"BanPickScene");

			InstantiateUI<PlayerCardBtn>(Vector3(-650.f, 74.f, 1.003f), LineUpUI, L"PlayerTeamCard_1")->SetRed();
			InstantiateUI<PlayerCardBtn>(Vector3(-395.f, 74.f, 1.003f), LineUpUI, L"PlayerTeamCard_2")->SetRed();
			InstantiateUI<PlayerCardBtn>(Vector3(65.f, 74.f, 1.003f), LineUpUI, L"PlayerTeamSubCard_1")->SetRed();
			InstantiateUI<PlayerCardBtn>(Vector3(399.f, 74.f, 1.003f), LineUpUI, L"EnemyTeamCard_1")->SetBlue();
			InstantiateUI<PlayerCardBtn>(Vector3(652.f, 74.f, 1.003f), LineUpUI, L"EnemyTeamCard_2")->SetBlue();

			UIObject* PlayerChangeIcon = InstantiateUI<UIObject>(Vector3(-159.f, 3.f, 1.003f),Vector3(135.f,120.f,1.f),LineUpUI,L"PlayerChangeIcon");
			PlayerChangeIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerChangeIconMt");
			PlayerChangeIcon->GetComponent<Transform>()->SetTransType(ssz::Transform::eTransType::PosAdd);
#pragma endregion

			// 오브젝트 배치용 스크립트
			// PlayerChangeIcon->AddComponent<ArrangementScript>()->SetDefault();
		}

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
			Cursor->AddComponent<CursorScript>();
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
		
		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			if (LineUpWin->GetState() == GameObject::eState::Paused)
			{
				LineUpWin->SetActive();
			}
		}
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