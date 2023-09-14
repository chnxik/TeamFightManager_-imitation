#include "sszLogoSelectBtn.h"
#include "CommonObjHeader.h"

#include "sszSelectBtnUI.h"

namespace ssz
{
	LogoSelectBtn::LogoSelectBtn(const std::wstring& key)
		: UIObject(key)
		, mTeamIcon(nullptr)
		, bSelected(false)
	{
	}

	LogoSelectBtn::~LogoSelectBtn()
	{
	}
	
	void LogoSelectBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

		Resources::Load<Texture>(L"LogoBtn_Idle", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");	// 기본 일반
		Resources::Load<Texture>(L"LogoBtn_Idle_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_1.png"); // 기본 마우스 커서
		Resources::Load<Texture>(L"LogoBtn_Sel", L"..\\Resources\\useResource\\UI\\slot_bg_2.png");	// 선택 일반
		Resources::Load<Texture>(L"LogoBtn_Sel_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_3.png");	// 선택 마우스 커서

		ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"LogoBtn_Idle", eRenderingMode::Transparent);

		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		SelectBtnUI* Btn = AddComponent<SelectBtnUI>();
		Btn->Initialize();

		// 클릭하면 Selected로 변경
		Btn->SetIdleTex(L"LogoBtn_Idle");
		Btn->SetOnTex(L"LogoBtn_Idle_Csr");
		Btn->SetDownTex(L"LogoBtn_Sel");
		Btn->SetSelTempTex(L"LogoBtn_Sel_Csr");

		Transform* tr = GetComponent<Transform>();
		tr->SetTransType(ssz::Transform::eTransType::PosAdd);

		AddComponent<Collider2D>();
	}

	void LogoSelectBtn::InitCheckSelected(UIObject** object)
	{
		SelectBtnUI* Btn = GetComponent<SelectBtnUI>();
		Btn->InitCheckSelected(object);
	}
}