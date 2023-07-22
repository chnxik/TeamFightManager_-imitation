#include "sszBanLine.h"
#include "CommonObjHeader.h"

namespace ssz
{
	BanLine::BanLine(const std::wstring& key)
		: UIObject(key)
	{
	}

	BanLine::~BanLine()
	{
	}
	void BanLine::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_LineMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"BanLine_RedTex", L"..\\Resources\\useResource\\Banpick\\middle_ban_red_line.png");
			Resources::Load<Texture>(L"BanLine_BlueTex", L"..\\Resources\\useResource\\Banpick\\middle_ban_blue_line.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BanLine_RedTex", eRenderingMode::Transparent);
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
			tr->SetScale(Vector3(1450.f, 90.f, 1.f));
		}
#pragma endregion
#pragma region SlotUI Load
		{
		}
#pragma endregion
	}
}