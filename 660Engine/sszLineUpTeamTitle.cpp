#include "sszLineUpTeamTitle.h"
#include "CommonObjHeader.h"

namespace ssz
{
	LineUpTeamTitle::LineUpTeamTitle(const std::wstring& key)
		: UIObject(key)
		, TitleTex{}
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			TitleTex[eCampType::Player][eColorType::Red] = Resources::Load<Texture>(L"LineUpUI_Red_Left_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_3.png");
			TitleTex[eCampType::Enemy][eColorType::Red] = Resources::Load<Texture>(L"LineUpUI_Red_Right_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_2.png");
			TitleTex[eCampType::Player][eColorType::Blue] = Resources::Load<Texture>(L"LineUpUI_Blue_Left_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_0.png");
			TitleTex[eCampType::Enemy][eColorType::Blue] = Resources::Load<Texture>(L"LineUpUI_Blue_Right_TTTex", L"..\\Resources\\useResource\\stadium\\UI\\lineup_ui_team_title_bg_1.png");


			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"LineUpUI_Red_Left_TTTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(500, 70.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}

	LineUpTeamTitle::~LineUpTeamTitle()
	{
	}

	void LineUpTeamTitle::SetTitleType(eCampType eCamp, eColorType eColor)
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(TitleTex[eCamp][eColor]);
	}
}