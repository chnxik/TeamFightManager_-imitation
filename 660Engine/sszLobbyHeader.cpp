#include "sszLobbyHeader.h"
#include "CommonObjHeader.h"

#include "sszHeaderSlot.h"

namespace ssz
{
	LobbyHeader::LobbyHeader(const std::wstring& key)
		: UIObject(key)
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"UIheaderBarTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"UIheaderBarTex", eRenderingMode::Transparent);
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
			tr->SetScale(Vector3(1920, 111.f, 1.f));
		}
#pragma endregion
#pragma region SlotUI Load
		{
			HeaderSlot* DateSlot = ssz::object::InstantiateUI<HeaderSlot>(Vector3(416.f, 0.f, 1.002f), this, L"DateSlot");
			HeaderSlot* GoldSlot = ssz::object::InstantiateUI<HeaderSlot>(Vector3(775.f, 0.f, 1.002f), this, L"DateSlot");
		}
#pragma endregion
	}

	LobbyHeader::~LobbyHeader()
	{
	}
}