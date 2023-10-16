#include "sszBanPickScene.h"
#include "CommonHeader.h"

#include "sszTGM.h"
#include "sszLeague.h"

#include "sszTeam.h"
#include "sszPilot.h"

#include "sszBattleHeader.h"
#include "sszBanLine.h"
#include "sszPlayerCardSlot.h"
#include "sszChampSelectSlot.h"

#include "sszBanPickWindow.h"

namespace ssz
{
	using namespace object;

	BanPickScene::BanPickScene()
		: mPhase(eBanPickPhase::SceneIn1)
		, mPlayerSlot{}
		, mAccTime(0.f)
		, mBattleHeader(nullptr)
		, mBanPickWindow(nullptr)
		, mBanLine(nullptr)
		, mBanLineCenterText(nullptr)
		, mBanLineSideText(nullptr)
		, mChampSlot{}
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
			Resources::Load<Texture>(L"GeneralBgTex", L"..\\Resources\\useResource\\UI\\ui_bg_empty.png");
			
			// Make Material
			LoadMaterial(L"GeneralBgMt", L"SpriteShader", L"GeneralBgTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Create Object for this Scene
#pragma region GameObject
		// GameObject
		{
			// BanpickBg
			GameObject* BanpickBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.2f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			BanpickBg->SetName(L"GeneralBg");
			BanpickBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"GeneralBgMt");
		}
#pragma endregion
#pragma region UI
		{
			// Battle Header
			mBattleHeader = InstantiateUI<BattleHeader>(Vector3(0.0f, 540.f, 1.04f), eLayerType::UI, L"BattleHeaderBg");


			// PlayerCard
			mPlayerSlot[(UINT)eTeamColor::Red][0] = InstantiateUI<PlayerCardSlot>(Vector3(960.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1"); 
			mPlayerSlot[(UINT)eTeamColor::Red][1] = InstantiateUI<PlayerCardSlot>(Vector3(960.f, 70.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2");
			mPlayerSlot[(UINT)eTeamColor::Blue][0] = InstantiateUI<PlayerCardSlot>(Vector3(-960.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1");
			mPlayerSlot[(UINT)eTeamColor::Blue][1] = InstantiateUI<PlayerCardSlot>(Vector3(-960.f, 70.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2");

			mPlayerSlot[(UINT)eTeamColor::Red][0]->SetRed();
			mPlayerSlot[(UINT)eTeamColor::Red][1]->SetRed();
			mPlayerSlot[(UINT)eTeamColor::Blue][0]->SetBlue();
			mPlayerSlot[(UINT)eTeamColor::Blue][1]->SetBlue();

			mBanPickWindow = InstantiateUI<BanPickWindow>(Vector3(0.f, -960.f, 1.19f), eLayerType::UI, L"BanPickWindow");
		
			// BanLine
			mBanLine = InstantiateUI<BanLine>(Vector3(0.f, 353.f, 1.03f), mBanPickWindow, L"BanLine");
			mBanLineCenterText = mBanLine->AddComponent<Text>();
			mBanLineSideText = mBanLine->AddComponent<Text>();

			mBanLineCenterText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -7.f, 0.f), 55, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			mBanLineSideText->TextInit(Text::eFonts::Galmuri11, Vector3(-550.f, -7.f, 0.f), 35, FONT_RGBA(255, 255, 255, 255), FW1_LEFT | FW1_VCENTER);
			mBanLineCenterText->SetString(L"금지할 챔피언을 선택하세요");
			mBanLineSideText->SetString(L"금지 단계\n(1/2)");

			// Champ Slot
			Vector3 SlotStartPoint(-545.f, 185.f, 1.18f);

			for (int i = 0; i < (UINT)eChamp::NONE; ++i)
			{
				std::wstring SlotKey = L"ChampSlot_" + std::to_wstring(i);
				ChampSelectSlot* NewSlot = InstantiateUI<ChampSelectSlot>(mBanPickWindow, SlotKey);

				Transform* SlotTr = NewSlot->GetComponent<Transform>();
				Vector3 SlotPos = SlotStartPoint;
				SlotPos.x += (SlotTr->GetScale().x) * i + (12.f * i);
				SlotTr->SetPosition(SlotPos);
				
				NewSlot->RegistWindowUI(mBanPickWindow);
				NewSlot->RegistChamp((eChamp)i);	// 순서대로 챔프 등록
				
				mChampSlot[i] = NewSlot;
			}


			// BanpickClassTap
			// 클래스탭은 Btn 묶음으로 부모객체에서 상태를 받아 선택된 버튼과 나머지 버튼의 크기와 위치가 바뀌도록 한다.

			// 오브젝트 배치용 스크립트
		}
#pragma endregion
		
#pragma endregion
	}
	void BanPickScene::Update()
	{
		Scene::Update();

		switch (mPhase)
		{
		case ssz::BanPickScene::eBanPickPhase::SceneIn1:
		{
			mAccTime += (float)Time::DeltaTime();

			Transform* BtHdTr = mBattleHeader->GetComponent<Transform>();
			Vector3 BtHdPos = BtHdTr->GetPosition();

			// 헤더
			if (478.5 < BtHdPos.y)
			{
				// 처음 위치 - 현재위치
				float fForce = BtHdPos.y - 478.5f;
				BtHdPos.y -= fForce * 4.f * (float)Time::DeltaTime();

				BtHdTr->SetPosition(BtHdPos);
			}

			// PlayerSlot
			Transform* RedSlotTr1 = mPlayerSlot[(UINT)eTeamColor::Red][0]->GetComponent<Transform>();
			Transform* RedSlotTr2 = mPlayerSlot[(UINT)eTeamColor::Red][1]->GetComponent<Transform>();
			Transform* BlueSlotTr1 = mPlayerSlot[(UINT)eTeamColor::Blue][0]->GetComponent<Transform>();
			Transform* BlueSlotTr2 = mPlayerSlot[(UINT)eTeamColor::Blue][1]->GetComponent<Transform>();

			Vector3 RSlotPos1 = RedSlotTr1->GetPosition();
			Vector3 RSlotPos2 = RedSlotTr2->GetPosition();
			Vector3 BSlotPos1 = BlueSlotTr1->GetPosition();
			Vector3 BSlotPos2 = BlueSlotTr2->GetPosition();

			// RSlot
			if (843.f < RSlotPos1.x)
			{
				float fForce = RSlotPos1.x - 843.f;
				RSlotPos1.x -= fForce * 4.f * (float)Time::DeltaTime();
				RSlotPos2.x -= fForce * 4.f * (float)Time::DeltaTime();

				RedSlotTr1->SetPosition(RSlotPos1);
				RedSlotTr2->SetPosition(RSlotPos2);
			}

			// BSlot
			if (-843.f > BSlotPos1.x)
			{
				float fForce = RSlotPos1.x - 843.f;
				BSlotPos1.x += fForce * 4.f * (float)Time::DeltaTime();
				BSlotPos2.x += fForce * 4.f * (float)Time::DeltaTime();

				BlueSlotTr1->SetPosition(BSlotPos1);
				BlueSlotTr2->SetPosition(BSlotPos2);
			}
			
			if (1.f < mAccTime)
			{
				mAccTime = 0.f;
				mPhase = eBanPickPhase::SceneIn2;
			}


			break;
		}
		case ssz::BanPickScene::eBanPickPhase::SceneIn2:
		{
			mAccTime += (float)Time::DeltaTime();

			// BanPick
			Transform* WindowTr = mBanPickWindow->GetComponent<Transform>();
			Vector3 WindowPos = WindowTr->GetPosition();

			// BanPick Window
			if (0.f > WindowPos.y)
			{
				// 처음 위치 - 현재위치
				float fForce = 0.f - WindowPos.y;
				WindowPos.y += fForce * 4.f * (float)Time::DeltaTime();

				WindowTr->SetPosition(WindowPos);
			}
			
			if (1.f < mAccTime)
			{
				mAccTime = 0.f;
				mPhase = eBanPickPhase::BP_1;
			}


			break;
		}
		case ssz::BanPickScene::eBanPickPhase::BP_1:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::BP_2:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_1:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_2:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_3:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_4:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::SceneOut:
		{
			if (Input::GetKeyDown(eKeyCode::ENTER))
			{
				SceneManager::LoadScene(L"IGStadiumScene");
			}
			break;
		}
		default:
			break;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			NextPhase();
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
		AddGameObject(eLayerType::Cursor, TGM::GetCursor());
		AddGameObject(eLayerType::Camera, TGM::GetCamera());

		mPhase = eBanPickPhase::SceneIn1;
		mBanLine->ChangeTurn(eTeamColor::Blue);
		mBanLineCenterText->SetString(L"금지할 챔피언을 선택하세요");
		mBanLineSideText->SetString(L"금지 단계\n(1/2)");
		
		mBattleHeader->RegistTeam();
		mBattleHeader->SetTitleType();
		

		Team* PlayerTeam = TGM::GetPlayerTeam();
		Team* EnemyTeam = TGM::GetLeagueManage()->GetEnemyTeam();

		std::vector<Pilot*> PlayerTeamPilotList = PlayerTeam->GetPilotList();
		std::vector<Pilot*> EnemyTeamPilotList = EnemyTeam->GetPilotList();

		for (int i = 0; i < 2; ++i)
		{
			mPlayerSlot[(UINT)eTeamColor::Blue][i]->RegistPilot(PlayerTeamPilotList[i]);
			mPlayerSlot[(UINT)eTeamColor::Red][i]->RegistPilot(EnemyTeamPilotList[i]);
		}
		

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);

		Reset();
	}
	void BanPickScene::OnExit()
	{
		CollisionManager::Clear();
		
		TGM::SceneClear();
	}
	void BanPickScene::NextPhase()
	{
		switch (mPhase)
		{
		case ssz::BanPickScene::eBanPickPhase::SceneIn1:
		{
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::SceneIn2:
			break;
		case ssz::BanPickScene::eBanPickPhase::BP_1:
		{
			mBanLineSideText->SetString(L"금지 단계\n(2/2)");
			mBanLine->ChangeTurn(eTeamColor::Red);
			mPhase = eBanPickPhase::BP_2;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::BP_2:
		{
			mBanLineSideText->SetString(L"선택 단계\n(1/3)");
			mBanLine->ChangeTurn(eTeamColor::Blue);
			mBanLineCenterText->SetString(L"사용할 챔피언을 선택하세요");
			mPhase = eBanPickPhase::PP_1;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_1:
		{
			mBanLineSideText->SetString(L"선택 단계\n(2/3)");
			mBanLine->ChangeTurn(eTeamColor::Red);
			mPhase = eBanPickPhase::PP_2;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_2:
		{
			mPhase = eBanPickPhase::PP_3;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_3:
		{
			mBanLineSideText->SetString(L"선택 단계\n(3/3)");
			mBanLine->ChangeTurn(eTeamColor::Blue);
			mPhase = eBanPickPhase::PP_4;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::PP_4:
		{
			mPhase = eBanPickPhase::SceneOut;
			break;
		}
		case ssz::BanPickScene::eBanPickPhase::SceneOut:
		{
			break;
		}
		}
	}
	void BanPickScene::Reset()
	{
		mPhase = ssz::BanPickScene::eBanPickPhase::SceneIn1;
		mAccTime = 0.f;

		// 위치 초기화
		mBattleHeader->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 540.f, 1.04f));
		mBanPickWindow->GetComponent<Transform>()->SetPosition(Vector3(0.f, -960.f, 1.19f));

		mPlayerSlot[(UINT)eTeamColor::Red][0]->GetComponent<Transform>()->SetPosition(Vector3(960.f, 308.f, 1.02f));
		mPlayerSlot[(UINT)eTeamColor::Red][1]->GetComponent<Transform>()->SetPosition(Vector3(960.f, 70.f, 1.02f));
		mPlayerSlot[(UINT)eTeamColor::Blue][0]->GetComponent<Transform>()->SetPosition(Vector3(-960.f, 308.f, 1.02f));
		mPlayerSlot[(UINT)eTeamColor::Blue][1]->GetComponent<Transform>()->SetPosition(Vector3(-960.f, 70.f, 1.02f));
	}
}