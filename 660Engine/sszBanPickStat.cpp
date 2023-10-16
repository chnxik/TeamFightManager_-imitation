#include "sszBanPickStat.h"
#include "CommonHeader.h"

#include "sszStatIcon.h"

namespace ssz
{
	BanPickStat::BanPickStat(const std::wstring& key)
		: UIObject(key)
		, mStatIcon(nullptr)
		, mSlotName(nullptr)
		, mStatValue(nullptr)
	{
	}

	BanPickStat::~BanPickStat()
	{
	}

	void BanPickStat::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_SlotMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"Banpick_statTex", L"..\\Resources\\useResource\\Banpick\\banpick_stat_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"Banpick_statTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// AddPanel
			AddComponent<PanelUI>();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(153, 63.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}

		{
			float StatSlotPosZ = GetComponent<Transform>()->GetPosition().z;

			// Set Icon
			mStatIcon = ssz::object::InstantiateUI<StatIcon>(Vector3(-59.f, 15.f, 1.019f), this, mUIKey);
			mSlotName = AddComponent<Text>();
			mStatValue = AddComponent<Text>();
			mSlotName->TextInit(Text::eFonts::Galmuri14, Vector3(-35.f, 15.f, 0.f), 25, FONT_RGBA(255, 255, 255, 255), FW1_LEFT | FW1_VCENTER);
			mStatValue->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -17.f, 0.f), 23, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		}
	}
	
	void BanPickStat::SetSlot(eStatType eType)
	{
		mStatIcon->SetIcon(eType);

		switch (eType)
		{
		case ssz::eStatType::ATK:
		{
			mSlotName->SetString(L"공격력");
			mStatValue->SetString(std::to_wstring(0));
			break;
		}
		case ssz::eStatType::DEF:
		{
			mSlotName->SetString(L"방어력");
			mStatValue->SetString(std::to_wstring(0));
			break;
		}
		case ssz::eStatType::APD:
		{
			mSlotName->SetString(L"공격 속도");
			mStatValue->SetString(std::to_wstring(0.0f).substr(0, 3));
			break;
		}
		case ssz::eStatType::HP:
		{
			mSlotName->SetString(L"체력");
			mStatValue->SetString(std::to_wstring(0));
			break;
		}
		case ssz::eStatType::RNG:
		{
			mSlotName->SetString(L"사거리");
			mStatValue->SetString(std::to_wstring(0));
			break;
		}
		case ssz::eStatType::SPD:
		{
			mSlotName->SetString(L"이동 속도");
			mStatValue->SetString(std::to_wstring(0));
			break;
		}
		default:
			break;
		}
	}
	void BanPickStat::SetValue(UINT value)
	{
		mStatValue->SetString(std::to_wstring(value));
	}
	void BanPickStat::SetValue(float value)
	{
		mStatValue->SetString(std::to_wstring(value).substr(0, 3));
	}
}