#include "sszNewGameWindow.h"
#include "CommonObjHeader.h"

#include "sszImportantBtn.h"
#include "sszDefaultBtn.h"

#include "sszTypeUI.h"
#include "sszLogoSelectBtn.h"

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

			NewGameTitle->SetString(L"�� ����");
			TeamName->SetString(L"�� �̸�");
			CoachName->SetString(L"���� �̸�");
			TeamLogo->SetString(L"�� �ΰ�");
			CoachTex->SetString(L"���� ����");

			Scene* ActiveScene = SceneManager::GetActiveScene();

			// ���ӽ���, ��� ��ư

			ImportantBtn* NewGameStartBtn = InstantiateUI<ImportantBtn>(Vector3(-123.f, -335.f, 1.049f), this, L"NewGameStartBtn");
			NewGameStartBtn->GetBtnComponent()->SetDelegateW(ActiveScene, (DELEGATEW)&Scene::ChangeScene, L"MainLobbyScene");
			NewGameStartBtn->SetKBDIcon(KBDIcon::F);

			Text* StartBtnText = NewGameStartBtn->AddComponent<Text>();
			StartBtnText->TextInit(L"Galmuri14", Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			StartBtnText->SetString(L"���� ����");

			DefaultBtn* NewGameUICloseBtn = InstantiateUI<DefaultBtn>(Vector3(123.f, -335.f, 1.049f), this, L"NewGameUICloseBtn");
			NewGameUICloseBtn->GetBtnComponent()->SetDelegate(this, (DELEGATE)&UIObject::UIClose);
			NewGameUICloseBtn->SetKBDIcon(KBDIcon::R);

			Text* CloseBtnText = NewGameUICloseBtn->AddComponent<Text>();
			CloseBtnText->TextInit(L"Galmuri14", Vector3(25.f, 13.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER);
			CloseBtnText->SetString(L"���");
		
			// ���̸� , ��ġ�̸� �Է� ��ư

			float posz = tr->GetPosition().z;
			TypeUI* TeamNameType = InstantiateUI<TypeUI>(Vector3(-280.f, 125.f, posz), Vector3(500.f, 100.f, 1.f), this, L"TN_TypeUI");
			TypeUI* CoachType = InstantiateUI<TypeUI>(Vector3(390.f, 125.f, posz), Vector3(500.f, 100.f, 1.f), this, L"CN_TypeUI");

			// �ΰ� ���� ��ư 1 ~ 10
			Vector3 LogoBtnPos(tr->GetPosition());

			for (int i = 1; i <= 2; ++i)
			{
				for (int j = 1; j <= 5; ++j)
				{
					wstring BtnName = L"TeamLogoBtn_" + std::to_wstring((i * 5) + j);
					LogoBtnPos.x = -525.f + ((j - 1) * 110.f);
					LogoBtnPos.y = -97.f - ((i - 1) * 110.f);
					
					LogoSelectBtn* TeamLogoSlot = InstantiateUI<LogoSelectBtn>(LogoBtnPos, Vector3(100.f, 100.f, 1.f), this, BtnName);
					TeamLogoSlot->InitCheckSelected(&mSelectedLogo);
				}
			}
		}
#pragma endregion
	}

}