#include "sszBanpickClassTap.h"
#include "CommonObjHeader.h"

namespace ssz
{
	BanpickClassTap::BanpickClassTap(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"BanpickClassTapBtnIdleTex", L"..\\Resources\\useResource\\Bampick\\tab_unselected_bg_0.png");
			Resources::Load<Texture>(L"BanpickClassTapBtnOneTex", L"..\\Resources\\useResource\\Bampick\\tab_unselected_bg_1.png");
			Resources::Load<Texture>(L"BanpickClassTapBtnDownTex", L"..\\Resources\\useResource\\Bampick\\tab_selected_bg.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BanpickClassTapBtnIdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"BanpickClassTapBtnIdleTex");
			mBtnComp->SetOnTex(L"BanpickClassTapBtnOneTex");
			mBtnComp->SetDownTex(L"BanpickClassTapBtnDownTex");
			mBtnComp->SetBtnType(ssz::ButtonUI::eBtnType::Selected);

			// Set default Size
			GetComponent<Transform>()->SetScale(Vector3(54, 18.f, 1.f));

			// 
		}
#pragma endregion
	}

	BanpickClassTap::~BanpickClassTap()
	{
	}
}
