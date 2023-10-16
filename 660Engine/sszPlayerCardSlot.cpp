#include "sszPlayerCardSlot.h"
#include "CommonHeader.h"

#include "sszPilot.h"

namespace ssz
{
	PlayerCardSlot::PlayerCardSlot(const std::wstring& key)
		: UIObject(key)
		, bSelect(false)
		, mAvatarFace(nullptr)
		, mRegistedPilot(nullptr)
		, mPilotName(nullptr)
		, mCharacter(nullptr)
		, mAtkIcon(nullptr)
		, mDefIcon(nullptr)
	{
	}

	PlayerCardSlot::~PlayerCardSlot()
	{
	}
	void PlayerCardSlot::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_SlotMt");

#pragma region Meterial Load
		{
			vecCardTex[(UINT)eTeamColor::Red][(UINT)eSlotState::Idle] = Resources::Load<Texture>(L"RedPlayerCardIdleTex", L"..\\Resources\\useResource\\Banpick\\player_card_bg_4.png");
			vecCardTex[(UINT)eTeamColor::Red][(UINT)eSlotState::Togle] = Resources::Load<Texture>(L"RedPlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_1.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)eSlotState::Idle] = Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\Banpick\\player_card_bg_0.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)eSlotState::Togle] = Resources::Load<Texture>(L"BluePlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_0.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BattleHeaderTex", eRenderingMode::Transparent);
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
			tr->SetScale(Vector3(235.f, 226.f, 1.f));

			// Text Setting
			mPilotName = AddComponent<Text>();
			mCharacter = AddComponent<Text>();

			mPilotName->TextInit(Text::eFonts::Galmuri11, Vector3(-105.f, 88.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_LEFT | FW1_VCENTER);
			mCharacter->TextInit(Text::eFonts::Galmuri11, Vector3(42.f, 50, 0.f), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			
			mPilotName->SetString(L"NONE");
			mCharacter->SetString(L"���");


			Resources::Load<Texture>(L"PilotATKIconTex", L"..\\Resources\\useResource\\Banpick\\attack_icon.png");
			Resources::Load<Texture>(L"PilotDEFIconTex", L"..\\Resources\\useResource\\Banpick\\defense_icon.png");
			
			LoadMaterial(L"PilotATKStatMt", L"SpriteShader", L"PilotATKIconTex", eRenderingMode::Transparent);
			LoadMaterial(L"PilotDEFStatMt", L"SpriteShader", L"PilotDEFIconTex", eRenderingMode::Transparent);

			mAtkIcon = object::InstantiateUI<UIObject>(Vector3(-95.f, -32.f, 0.f), Vector3(25.f, 25.f, 0.f), this, L"PilotATKStat");;
			mAtkIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
			mAtkIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PilotATKStatMt");
			Text* AtkStatText = mAtkIcon->AddComponent<Text>();
			AtkStatText->TextInit(Text::eFonts::Galmuri9, Vector3(50.f, -5.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			AtkStatText->SetString(L"NONE");

			mDefIcon = object::InstantiateUI<UIObject>(Vector3(10.f, -32.f, 0.f), Vector3(25.f, 25.f, 0.f), this, L"PilotATKStat");;
			mDefIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
			mDefIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PilotDEFStatMt");
			Text* DefStatText = mDefIcon->AddComponent<Text>();
			DefStatText->TextInit(Text::eFonts::Galmuri9, Vector3(50.f, -5.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			DefStatText->SetString(L"NONE");

		}
#pragma endregion
#pragma region SlotUI Load
		{
		}
#pragma endregion
	}

	void PlayerCardSlot::RegistPilot(Pilot* pilot)
	{
		mRegistedPilot = pilot;
		mPilotName->SetString(mRegistedPilot->GetPilotName());
		
		UINT PilotATK = mRegistedPilot->GetPilotATK();
		UINT PilotDEF = mRegistedPilot->GetPilotDEF();
		
		mAtkIcon->GetComponent<Text>()->SetString(std::to_wstring(PilotATK));
		mDefIcon->GetComponent<Text>()->SetString(std::to_wstring(PilotDEF));
	}
	
	void PlayerCardSlot::SetRed()
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(vecCardTex[(UINT)eTeamColor::Red][(UINT)eSlotState::Idle]);
	}
	
	void PlayerCardSlot::SetBlue()
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(vecCardTex[(UINT)eTeamColor::Blue][(UINT)eSlotState::Idle]);
	}
}