#include "sszPlayerCardSlot.h"
#include "CommonObjHeader.h"

namespace ssz
{
	PlayerCardSlot::PlayerCardSlot(const std::wstring& key)
		: UIObject(key)
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
			vecCardTex[(UINT)eTeamColor::Red][(UINT)eSlotState::Selected] = Resources::Load<Texture>(L"RedPlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_1.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)eSlotState::Idle] = Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\Banpick\\player_card_bg_0.png");
			vecCardTex[(UINT)eTeamColor::Blue][(UINT)eSlotState::Selected] = Resources::Load<Texture>(L"BluePlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_0.png");

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
		}
#pragma endregion
#pragma region SlotUI Load
		{
		}
#pragma endregion
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