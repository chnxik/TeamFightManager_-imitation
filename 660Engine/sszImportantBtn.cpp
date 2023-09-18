#include "sszImportantBtn.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	ImportantBtn::ImportantBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, mKBDIcon(nullptr)
	{
		
	}

	ImportantBtn::~ImportantBtn()
	{
	}
	void ImportantBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"ImportantBtn_IdleTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_0.png");
			Resources::Load<Texture>(L"ImportantBtn_OnTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_1.png");
			Resources::Load<Texture>(L"ImportantBtn_DownTex", L"..\\Resources\\useResource\\CommonUI\\btn\\important_button_2.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"ImportantBtn_IdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"ImportantBtn_IdleTex");
			mBtnComp->SetOnTex(L"ImportantBtn_OnTex");
			mBtnComp->SetDownTex(L"ImportantBtn_DownTex");

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(207, 75.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}

	void ImportantBtn::SetKBDIcon(KBDIcon::KEYICON key)
	{
		mKBDIcon = new KBDIcon(L"KeyIcon");
		mKBDIcon->SetIcon(key);

		AddChildUI((UIObject*)mKBDIcon);
	}
}