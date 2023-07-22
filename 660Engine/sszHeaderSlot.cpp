#include "sszHeaderSlot.h"
#include "CommonObjHeader.h"

namespace ssz
{
	HeaderSlot::HeaderSlot(const std::wstring& key)
		: UIObject(key)
	{
	
	}

	HeaderSlot::~HeaderSlot()
	{
	}
	void HeaderSlot::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_SlotMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"headerSlotBgTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_slot_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"headerSlotBgTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(339.f, 72.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}
}