#include "sszNewGameWindow.h"
#include "CommonObjHeader.h"

namespace ssz
{
	NewGameWindow::NewGameWindow(const std::wstring& key)
		: UIObject(key)
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
		}
#pragma endregion
	}

}