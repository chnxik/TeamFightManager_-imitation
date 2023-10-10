#include "sszPlayerCardBtn.h"
#include "CommonHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	PlayerCardBtn::PlayerCardBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, vecCardTex{}
	{
		
	}

	PlayerCardBtn::~PlayerCardBtn()
	{
	}

	void PlayerCardBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::Idle] = Resources::Load<Texture>(L"RedPlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_4.png");
			vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::On] = Resources::Load<Texture>(L"RedPlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_5.png");
			vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::Down] = Resources::Load<Texture>(L"RedPlayerCardSelectedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_6.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::Idle] = Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_0.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::On] = Resources::Load<Texture>(L"BluePlayerCardOnTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_1.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::Down] = Resources::Load<Texture>(L"BluePlayerCardSelectedTex", L"..\\Resources\\useResource\\stadium\\UI\\player_card_bg_2.png");

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
			mBtnComp->SetBtnType(ssz::ButtonUI::eBtnType::Togle);

			SetRed();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(235.f, 226.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);

		}
#pragma endregion
	}
	void PlayerCardBtn::SetRed()
	{
		mBtnComp->SetIdleTex(vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::Idle]);
		mBtnComp->SetOnTex(vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::On]);
		mBtnComp->SetDownTex(vecCardTex[(UINT)eTeamColor::Red][(UINT)ButtonUI::eBtnState::Down]);
	}
	void PlayerCardBtn::SetBlue()
	{
		mBtnComp->SetIdleTex(vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::Idle]);
		mBtnComp->SetOnTex(vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::On]);
		mBtnComp->SetDownTex(vecCardTex[(UINT)eTeamColor::Blue][(UINT)ButtonUI::eBtnState::Down]);
	}
}
