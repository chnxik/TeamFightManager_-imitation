#include "sszPlayerCardBtn.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	PlayerCardBtn::PlayerCardBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, vecCardTex{}
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			vecCardTex[eTeamColor::Red][eBtnState::Idle] = Resources::Load<Texture>(L"RedPlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_4.png");
			vecCardTex[eTeamColor::Red][eBtnState::On] = Resources::Load<Texture>(L"RedPlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_5.png");
			vecCardTex[eTeamColor::Red][eBtnState::Down] = Resources::Load<Texture>(L"RedPlayerCardSelectedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_6.png");
			vecCardTex[eTeamColor::Blue][eBtnState::Idle] = Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_0.png");
			vecCardTex[eTeamColor::Blue][eBtnState::On] = Resources::Load<Texture>(L"BluePlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_1.png");
			vecCardTex[eTeamColor::Blue][eBtnState::Down] = Resources::Load<Texture>(L"BluePlayerCardSelectedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_2.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"RedPlayerCardIdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
				
			mBtnComp->Initialize();
			mBtnComp->SetBtnType(ssz::ButtonUI::eBtnType::Selected);

			SetRed();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(235.f, 226.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);

		}
#pragma endregion
	}

	PlayerCardBtn::~PlayerCardBtn()
	{
	}
	void PlayerCardBtn::SetRed()
	{
		mBtnComp->SetIdleTex(vecCardTex[eTeamColor::Red][eBtnState::Idle]);
		mBtnComp->SetOnTex(vecCardTex[eTeamColor::Red][eBtnState::On]);
		mBtnComp->SetDownTex(vecCardTex[eTeamColor::Red][eBtnState::Down]);
	}
	void PlayerCardBtn::SetBlue()
	{
		mBtnComp->SetIdleTex(vecCardTex[eTeamColor::Blue][eBtnState::Idle]);
		mBtnComp->SetOnTex(vecCardTex[eTeamColor::Blue][eBtnState::On]);
		mBtnComp->SetDownTex(vecCardTex[eTeamColor::Blue][eBtnState::Down]);
	}
}
