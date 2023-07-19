#include "sszBanPickStat.h"
#include "CommonObjHeader.h"

#include "sszStatIcon.h"

namespace ssz
{
	BanPickStat::BanPickStat(const std::wstring& key)
		: UIObject(key)
		, mStatIcon(nullptr)
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
		}
	}

	BanPickStat::~BanPickStat()
	{
	}
	
	void BanPickStat::SetSlot(eStatType eType)
	{
		mStatIcon->SetIcon((ssz::StatIcon::eStatType)eType);
	}
}