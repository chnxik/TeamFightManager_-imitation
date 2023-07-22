#include "sszBattleHeader.h"
#include "CommonObjHeader.h"

namespace ssz
{
	BattleHeader::BattleHeader(const std::wstring& key)
		: UIObject(key)
	{
	
	}

	BattleHeader::~BattleHeader()
	{
	}
	void BattleHeader::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\Banpick\\header_bg.png");

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
			tr->SetScale(Vector3(1920, 123.f, 1.f));
		}
#pragma endregion
#pragma region SlotUI Load
		{
		}
#pragma endregion
	}
}