#include "sszDefaultBtn.h"
#include "CommonObjHeader.h"

namespace ssz
{
	DefaultBtn::DefaultBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
	{
	}

	DefaultBtn::~DefaultBtn()
	{
	}
	void DefaultBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"DefaultBtn_IdleTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_0.png");
			Resources::Load<Texture>(L"DefaultBtn_OnTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_1.png");
			Resources::Load<Texture>(L"DefaultBtn_DownTex", L"..\\Resources\\useResource\\CommonUI\\btn\\default_button_2.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"DefaultBtn_IdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"DefaultBtn_IdleTex");
			mBtnComp->SetOnTex(L"DefaultBtn_OnTex");
			mBtnComp->SetDownTex(L"DefaultBtn_DownTex");

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(207, 75.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}
	void DefaultBtn::Update()
	{
		UIObject::Update();
	}
	void DefaultBtn::LateUpdate()
	{
		UIObject::LateUpdate();
	}
	void DefaultBtn::Render()
	{
		UIObject::Render();
	}
}