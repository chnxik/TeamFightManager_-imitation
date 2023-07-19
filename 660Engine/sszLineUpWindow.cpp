#include "sszLineUpWindow.h"
#include "CommonObjHeader.h"

#include "sszLineUpTeamTitle.h"

namespace ssz
{
	LineUpWindow::LineUpWindow(const std::wstring& key)
		: UIObject(key)
		, PlayerTeamTitle(nullptr)
		, EnemyTeamTitle(nullptr)
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"LineUpWindowTex", L"..\\Resources\\useResource\\stadium\\UI\\multi_lineup_ui_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"LineUpWindowTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set Panel
			AddComponent<PanelUI>();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(1630, 850.f, 1.f));
		}
#pragma endregion
#pragma region Add Object
		{
			PlayerTeamTitle = ssz::object::InstantiateUI<LineUpTeamTitle>(Vector3(-522.f, 240.f, 1.003f), this, L"PlayerTeamTitle");
			EnemyTeamTitle = ssz::object::InstantiateUI<LineUpTeamTitle>(Vector3(523.f, 240.f, 1.003f), this, L"EnemyTeamTitle");
		}
#pragma endregion
	}

	LineUpWindow::~LineUpWindow()
	{
	}

	void LineUpWindow::SetPlayerTeamTitle(ssz::LineUpTeamTitle::eColorType eColor)
	{
		PlayerTeamTitle->SetTitleType(ssz::LineUpTeamTitle::eCampType::Player, eColor);
	}

	void LineUpWindow::SetEnemyTeamTitle(ssz::LineUpTeamTitle::eColorType eColor)
	{
		EnemyTeamTitle->SetTitleType(ssz::LineUpTeamTitle::eCampType::Enemy, eColor);
	}

}