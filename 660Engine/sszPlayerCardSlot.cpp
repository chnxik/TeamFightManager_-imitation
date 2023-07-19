#include "sszPlayerCardSlot.h"
#include "CommonObjHeader.h"

namespace ssz
{
	PlayerCardSlot::PlayerCardSlot(const std::wstring& key)
		: UIObject(key)
	{
		std::wstring MtKey(mUIKey + L"_SlotMt");

#pragma region Meterial Load
		{
			vecCardTex[eColor::Red][eSlotState::Idle] = Resources::Load<Texture>(L"RedPlayerCardIdleTex", L"..\\Resources\\useResource\\Banpick\\player_card_bg_4.png");
			vecCardTex[eColor::Red][eSlotState::highlighted] = Resources::Load<Texture>(L"RedPlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_1.png");
			vecCardTex[eColor::Blue][eSlotState::Idle] = Resources::Load<Texture>(L"BluePlayerCardIdleTex", L"..\\Resources\\useResource\\Banpick\\player_card_bg_0.png");
			vecCardTex[eColor::Blue][eSlotState::highlighted] = Resources::Load<Texture>(L"BluePlayerCardHighLightedTex", L"..\\Resources\\useResource\\Banpick\\player_card_highlighted_bg_0.png");

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

	PlayerCardSlot::~PlayerCardSlot()
	{
	}
	void PlayerCardSlot::SetRed()
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(vecCardTex[eColor::Red][eSlotState::Idle]);
	}
	void PlayerCardSlot::SetBlue()
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(vecCardTex[eColor::Blue][eSlotState::Idle]);
	}
}