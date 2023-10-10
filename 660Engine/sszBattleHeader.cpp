#include "sszBattleHeader.h"
#include "CommonHeader.h"
#include "sszTGM.h"

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

			// Time
			Text* tx = AddComponent<Text>();
			tx->SetOffsetPos(Vector3(-20.f, -30.f, 0.f));
			tx->SetFontSize(25);
			tx->SetFont(L"Galmuri14");
		}
#pragma endregion
#pragma region SlotUI Load
		{
		}
#pragma endregion
	}
	void BattleHeader::Update()
	{
		float gametime = TGM::GetGameTime() - (float)Time::DeltaTime();

		if (gametime < 0.f)
			gametime = 0.f;

		TGM::SetGameTime(gametime);

		std::wstring gt = L": ";
		gt += std::to_wstring((UINT)gametime);

		GetComponent<Text>()->SetString(gt);
		GameObject::Update();
	}
}