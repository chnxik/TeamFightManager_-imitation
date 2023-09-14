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

		Resources::Load<Texture>(L"LogoBtn_Idle", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");	// �⺻ �Ϲ�
		Resources::Load<Texture>(L"LogoBtn_Idle_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_1.png"); // �⺻ ���콺 Ŀ��
		Resources::Load<Texture>(L"LogoBtn_Sel", L"..\\Resources\\useResource\\UI\\slot_bg_2.png");	// ���� �Ϲ�
		Resources::Load<Texture>(L"LogoBtn_Sel_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_3.png");	// ���� ���콺 Ŀ��

		ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"LogoBtn_Idle", eRenderingMode::Transparent);

		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		SelectBtnUI* Btn = AddComponent<SelectBtnUI>();
		Btn->Initialize();

		// Ŭ���ϸ� Selected�� ����
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