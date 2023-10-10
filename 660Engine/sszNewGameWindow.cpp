#include "sszNewGameWindow.h"
#include "CommonHeader.h"

#include "sszImportantBtn.h"
#include "sszDefaultBtn.h"

#include "sszTypeUI.h"
#include "sszSelectBtn.h"
#include "sszButtonUI.h"
#include "sszSelectBtnUI.h"

#include "sszTeamIconSlot.h"
#include "sszAvatarSlot.h"

#include "sszTGM.h"

#include "sszPilot.h"
#include "sszTeam.h"

namespace ssz
{
	NewGameWindow::NewGameWindow(const std::wstring& key)
		: UIObject(key)
		, mSelectedLogo(nullptr)
		, mSelectedHair(nullptr)
		, mTeamIconSlot(nullptr)
		, mAvatarSlot(nullptr)
		, mTeamNameType(nullptr)
		, mCoachType(nullptr)
		, NewGameStartBtn(nullptr)
		, NewGameUICloseBtn(nullptr)
	{
		
	}

	NewGameWindow::~NewGameWindow()
	{
	}

	void NewGameWindow::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_WindowMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"NewGameUITex", L"..\\Resources\\useResource\\Title\\NewGame\\new_game_ui_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"NewGameUITex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set Panel
			AddComponent<PanelUI>();
			AddComponent<Collider2D>();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(1350.f, 786.f, 1.f));

			Text* NewGameTitle = AddComponent<Text>();
			Text* TeamName = AddComponent<Text>();
			Text* CoachName = AddComponent<Text>();
			Text* TeamLogo = AddComponent<Text>();
			Text* CoachTex = AddComponent<Text>();

			NewGameTitle->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, 350.f, 0.f), 50.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			TeamName->TextInit(Text::eFonts::Galmuri14, Vector3(-330.f, 250.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CoachName->TextInit(Text::eFonts::Galmuri14, Vector3(340.f, 250.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			TeamLogo->TextInit(Text::eFonts::Galmuri14, Vector3(-330.f, 30.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CoachTex->TextInit(Text::eFonts::Galmuri14, Vector3(340.f, 30.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);

			NewGameTitle->SetString(L"�� ����");
			TeamName->SetString(L"�� �̸�");
			CoachName->SetString(L"���� �̸�");
			TeamLogo->SetString(L"�� �ΰ�");
			CoachTex->SetString(L"���� ����");

			// ���ӽ���, ��� ��ư

			NewGameStartBtn = InstantiateUI<ImportantBtn>(Vector3(-123.f, -335.f, 1.049f), this, L"NewGameStartBtn");
			NewGameStartBtn->GetBtnComponent()->SetDelegate(this, (DELEGATE)&NewGameWindow::GameStart);
			NewGameStartBtn->SetKBDIcon(KBDIcon::F);

			Text* StartBtnText = NewGameStartBtn->AddComponent<Text>();
			StartBtnText->TextInit(Text::eFonts::Galmuri14, Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			StartBtnText->SetString(L"���� ����");

			NewGameUICloseBtn = InstantiateUI<DefaultBtn>(Vector3(123.f, -335.f, 1.049f), this, L"NewGameUICloseBtn");
			NewGameUICloseBtn->GetBtnComponent()->SetDelegate(this, (DELEGATE)&UIObject::UIClose);
			NewGameUICloseBtn->SetKBDIcon(KBDIcon::R);

			Text* CloseBtnText = NewGameUICloseBtn->AddComponent<Text>();
			CloseBtnText->TextInit(Text::eFonts::Galmuri14, Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CloseBtnText->SetString(L"���");
		
			// ���̸� , ��ġ�̸� �Է� ��ư

			float posz = tr->GetPosition().z;
			mTeamNameType = InstantiateUI<TypeUI>(Vector3(-280.f, 125.f, posz), Vector3(500.f, 75.f, 1.f), this, L"TN_TypeUI");
			mCoachType = InstantiateUI<TypeUI>(Vector3(390.f, 125.f, posz), Vector3(500.f, 75.f, 1.f), this, L"CN_TypeUI");

			
			// �ΰ� ���� ��ư 1 ~ 10
			mTeamIconSlot = InstantiateUI<TeamIconSlot>(Vector3(-585.f, 125.f, posz - 0.0001f), Vector3(100.f, 100.f, 1.0f), this, L"SelectedLogo");
			{
				Vector3 LogoBtnPos(tr->GetPosition());

				// �ΰ� �ؽ��� �ε�
				Resources::Load<Texture>(L"TeamLogoTex_1", L"..\\Resources\\useResource\\TeamLogo\\albatrosses.png");
				Resources::Load<Texture>(L"TeamLogoTex_2", L"..\\Resources\\useResource\\TeamLogo\\anchors.png");
				Resources::Load<Texture>(L"TeamLogoTex_3", L"..\\Resources\\useResource\\TeamLogo\\giraffes.png");
				Resources::Load<Texture>(L"TeamLogoTex_4", L"..\\Resources\\useResource\\TeamLogo\\goats.png");
				Resources::Load<Texture>(L"TeamLogoTex_5", L"..\\Resources\\useResource\\TeamLogo\\marlins.png");
				Resources::Load<Texture>(L"TeamLogoTex_6", L"..\\Resources\\useResource\\TeamLogo\\lions.png");
				Resources::Load<Texture>(L"TeamLogoTex_7", L"..\\Resources\\useResource\\TeamLogo\\squids.png");
				Resources::Load<Texture>(L"TeamLogoTex_8", L"..\\Resources\\useResource\\TeamLogo\\tigers.png");
				Resources::Load<Texture>(L"TeamLogoTex_9", L"..\\Resources\\useResource\\TeamLogo\\whales.png");
				Resources::Load<Texture>(L"TeamLogoTex_10", L"..\\Resources\\useResource\\TeamLogo\\rabbits.png");

				for (int i = 0; i <= 1; ++i)
				{
					for (int j = 1; j <= 5; ++j)
					{
						int idx = (i * 5) + j;
						std::wstring BtnName = L"TeamLogoBtn_" + std::to_wstring(idx);
						LogoBtnPos.x = -525.f + ((j - 1) * 110.f);
						LogoBtnPos.y = -97.f - (i * 110.f);

						SelectBtn* TeamLogoSlot = InstantiateUI<SelectBtn>(LogoBtnPos, Vector3(100.f, 100.f, 1.f), this, BtnName);
						TeamLogoSlot->InitCheckSelected(&mSelectedLogo);

						std::wstring Texkey = L"TeamLogoTex_" + std::to_wstring(idx);
						TeamLogoSlot->InitItemTex(Texkey, idx, LogoBtnPos, Vector3(100.f, 100.f, 1.f), this);
						TeamLogoSlot->GetComponent<SelectBtnUI>()->SetDelegateW(mTeamIconSlot, (DELEGATEW)&TeamIconSlot::ChangeIcon, Texkey);
						
						if (i == 0 && j == 1)
						{
							TeamLogoSlot->MouseLbtnDown();
							TeamLogoSlot->MouseLbtnClicked();
						}
					}
				}
			}

			// ��ġ ���� ���� ��ư
			mAvatarSlot = InstantiateUI<AvatarSlot>(Vector3(83.f, 125.f, posz - 0.0001f), Vector3(100.f, 100.f, 1.0f), this, L"SelectedAvatar");

			{
				Vector3 LogoBtnPos(tr->GetPosition());

				// �ΰ� �ؽ��� �ε�
				Resources::Load<Texture>(L"CoachHairTex_1", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_0.png");
				Resources::Load<Texture>(L"CoachHairTex_2", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_1.png");
				Resources::Load<Texture>(L"CoachHairTex_3", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_2.png");
				Resources::Load<Texture>(L"CoachHairTex_4", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_3.png");
				Resources::Load<Texture>(L"CoachHairTex_5", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_4.png");
				Resources::Load<Texture>(L"CoachHairTex_6", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_5.png");
				Resources::Load<Texture>(L"CoachHairTex_7", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_6.png");
				Resources::Load<Texture>(L"CoachHairTex_8", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_7.png");
				Resources::Load<Texture>(L"CoachHairTex_9", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_8.png");
				Resources::Load<Texture>(L"CoachHairTex_10", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_hair_9.png");

				for (int i = 0; i <= 1; ++i)
				{
					for (int j = 1; j <= 5; ++j)
					{
						int idx = (i * 5) + j;
						std::wstring BtnName = L"CoachHair_" + std::to_wstring(idx);
						LogoBtnPos.x = 145.f + ((j - 1) * 110.f);
						LogoBtnPos.y = -97.f - (i * 110.f);

						SelectBtn* AvatarSlot = InstantiateUI<SelectBtn>(LogoBtnPos, Vector3(100.f, 100.f, 1.f), this, BtnName);
						AvatarSlot->InitCheckSelected(&mSelectedHair);


						std::wstring Texkey = L"CoachHairTex_" + std::to_wstring(idx);
						
						Vector2 TexScale = Resources::Find<Texture>(Texkey)->GetTextureSize();
						TexScale *= 3.f;

						AvatarSlot->InitItemTex(Texkey, idx, LogoBtnPos, Vector3(TexScale.x, TexScale.y, 1.f), this);
						AvatarSlot->GetComponent<SelectBtnUI>()->SetDelegateW(mAvatarSlot, (DELEGATEW)&AvatarSlot::ChangeHair, Texkey);

						if (i == 0 && j == 1)
						{
							AvatarSlot->MouseLbtnDown();
							AvatarSlot->MouseLbtnClicked();
						}
					}
				}
			}
		}
#pragma endregion
	}

	void NewGameWindow::Update()
	{
		UIObject::Update();

		if (mTeamNameType->IsCurTyping() || mCoachType->IsCurTyping())
			return;

		if (Input::GetKey(eKeyCode::F))
			NewGameStartBtn->MouseLbtnClicked();
		
		else if (Input::GetKey(eKeyCode::R))
			NewGameUICloseBtn->MouseLbtnClicked();

	}

	void NewGameWindow::GameStart()
	{
		// �÷��̾� �� ���
		std::wstring TeamName = mTeamNameType->Getstr();
		std::shared_ptr<Texture> TeamIcon = mSelectedLogo->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		
		Team* PlayerTeam = TGM::GetPlayerTeam();
		PlayerTeam->SetTeamName(TeamName);
		PlayerTeam->SetIconTex(mTeamIconSlot->GetIconTexKey());
		
		

		// ���Ϸ� ��������
		std::random_device rd;
		std::mt19937 gen(rd());
		
		// ���Ϸ� ����
		std::vector<Pilot*> Pilots;

		std::map<std::wstring, Pilot*> PilotList = TGM::GetPilotList();
		std::map<std::wstring, Pilot*>::iterator PilotIter = PilotList.begin();

		for (; PilotIter != PilotList.end(); PilotIter++)
		{
			Pilot* pilot = Pilots.emplace_back(PilotIter->second);

			UINT Age = rand() % 7 + 17;
			UINT ATK = rand() % 5;
			UINT DEF = rand() % 5;

			pilot->SetPilotData(ATK, DEF, Age);
		}

		// ����
		std::shuffle(Pilots.begin(), Pilots.end(), gen);
		
		// ��ü �� �ʱ� ����
		if (!(TGM::TeamInitialize(Pilots)))
			assert(nullptr);


		SceneManager::LoadScene(L"MainLobbyScene");
	}
}