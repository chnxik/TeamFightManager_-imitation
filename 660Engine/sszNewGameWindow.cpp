#include "sszNewGameWindow.h"
#include "CommonObjHeader.h"

#include "sszImportantBtn.h"
#include "sszDefaultBtn.h"

#include "sszTypeUI.h"
#include "sszLogoSelectBtn.h"
#include "sszButtonUI.h"
#include "sszTeamIcon.h"
#include "sszSelectBtnUI.h"

namespace ssz
{
	NewGameWindow::NewGameWindow(const std::wstring& key)
		: UIObject(key)
		, mSelectedLogo(nullptr)
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

			NewGameTitle->TextInit(L"Galmuri14", Vector3(0.f, 350.f, 0.f), 50.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			TeamName->TextInit(L"Galmuri14", Vector3(-330.f, 250.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CoachName->TextInit(L"Galmuri14", Vector3(340.f, 250.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			TeamLogo->TextInit(L"Galmuri14", Vector3(-330.f, 30.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CoachTex->TextInit(L"Galmuri14", Vector3(340.f, 30.f, 0.f), 40.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);

			NewGameTitle->SetString(L"새 게임");
			TeamName->SetString(L"팀 이름");
			CoachName->SetString(L"감독 이름");
			TeamLogo->SetString(L"팀 로고");
			CoachTex->SetString(L"감독 외형");

			Scene* ActiveScene = SceneManager::GetActiveScene();

			// 게임시작, 취소 버튼

			ImportantBtn* NewGameStartBtn = InstantiateUI<ImportantBtn>(Vector3(-123.f, -335.f, 1.049f), this, L"NewGameStartBtn");
			NewGameStartBtn->GetBtnComponent()->SetDelegateW(ActiveScene, (DELEGATEW)&Scene::ChangeScene, L"MainLobbyScene");
			NewGameStartBtn->SetKBDIcon(KBDIcon::F);

			Text* StartBtnText = NewGameStartBtn->AddComponent<Text>();
			StartBtnText->TextInit(L"Galmuri14", Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			StartBtnText->SetString(L"게임 시작");

			DefaultBtn* NewGameUICloseBtn = InstantiateUI<DefaultBtn>(Vector3(123.f, -335.f, 1.049f), this, L"NewGameUICloseBtn");
			NewGameUICloseBtn->GetBtnComponent()->SetDelegate(this, (DELEGATE)&UIObject::UIClose);
			NewGameUICloseBtn->SetKBDIcon(KBDIcon::R);

			Text* CloseBtnText = NewGameUICloseBtn->AddComponent<Text>();
			CloseBtnText->TextInit(L"Galmuri14", Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CloseBtnText->SetString(L"취소");
		
			// 팀이름 , 코치이름 입력 버튼

			float posz = tr->GetPosition().z;
			TypeUI* TeamNameType = InstantiateUI<TypeUI>(Vector3(-280.f, 125.f, posz), Vector3(500.f, 100.f, 1.f), this, L"TN_TypeUI");
			TypeUI* CoachType = InstantiateUI<TypeUI>(Vector3(390.f, 125.f, posz), Vector3(500.f, 100.f, 1.f), this, L"CN_TypeUI");

			TeamIcon* NewTeamIcon = InstantiateUI<TeamIcon>(Vector3(-585.f, 125.f, posz - 0.0001f), Vector3(100.f, 100.f, 1.0f), this, L"SelectedLogo");
			
			// 로고 선택 버튼 1 ~ 10
			Vector3 LogoBtnPos(tr->GetPosition());

			// 로고 텍스쳐 로딩
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
					wstring BtnName = L"TeamLogoBtn_" + std::to_wstring(idx);
					LogoBtnPos.x = -525.f + ((j - 1) * 110.f);
					LogoBtnPos.y = -97.f - (i * 110.f);
					
					LogoSelectBtn* TeamLogoSlot = InstantiateUI<LogoSelectBtn>(LogoBtnPos, Vector3(100.f, 100.f, 1.f), this, BtnName);
					TeamLogoSlot->InitCheckSelected(&mSelectedLogo);

					wstring Texkey = L"TeamLogoTex_" + std::to_wstring(idx);
					TeamLogoSlot->InitTeamLogo(Texkey, idx, LogoBtnPos, this, NewTeamIcon);
				}
			}
		}
#pragma endregion
	}

}