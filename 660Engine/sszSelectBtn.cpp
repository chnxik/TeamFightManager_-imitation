#pragma once
#include "sszSelectBtn.h"
#include "CommonObjHeader.h"

#include "sszSelectBtnUI.h"

namespace ssz
{
	SelectBtn::SelectBtn(const std::wstring& key)
		: UIObject(key)
		, mItemObj(nullptr)
		, bSelected(false)
	{
	}

	SelectBtn::~SelectBtn()
	{
	}
	
	void SelectBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

		Resources::Load<Texture>(L"SelBtn_Idle", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");	// �⺻ �Ϲ�
		Resources::Load<Texture>(L"SelBtn_Idle_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_1.png"); // �⺻ ���콺 Ŀ��
		Resources::Load<Texture>(L"SelBtn_Sel", L"..\\Resources\\useResource\\UI\\slot_bg_2.png");	// ���� �Ϲ�
		Resources::Load<Texture>(L"SelBtn_Sel_Csr", L"..\\Resources\\useResource\\UI\\slot_bg_3.png");	// ���� ���콺 Ŀ��

		ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"SelBtn_Idle", eRenderingMode::Transparent);

		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		SelectBtnUI* Btn = AddComponent<SelectBtnUI>();
		Btn->Initialize();

		// Ŭ���ϸ� Selected�� ����
		Btn->SetIdleTex(L"SelBtn_Idle");
		Btn->SetOnTex(L"SelBtn_Idle_Csr");
		Btn->SetDownTex(L"SelBtn_Sel");
		Btn->SetSelTempTex(L"SelBtn_Sel_Csr");

		Transform* tr = GetComponent<Transform>();
		tr->SetTransType(ssz::Transform::eTransType::PosAdd);

		AddComponent<Collider2D>();
	}

	

	void SelectBtn::InitCheckSelected(UIObject** object)
	{
		SelectBtnUI* Btn = GetComponent<SelectBtnUI>();
		Btn->InitCheckSelected(object);
	}

	void SelectBtn::InitItemTex(wstring Texkey, UINT idx, Vector3 Pos, Vector3 Scale, UIObject* parent)
	{
		Pos.z -= 0.00001f;
		
		wstring objname = GetName();
		mItemObj = InstantiateUI<UIObject>(Pos, Scale, parent, objname);
		
		Transform* TeamIconTr = mItemObj->GetComponent<Transform>();
		TeamIconTr->SetTransType(Transform::eTransType::PosAdd);
		
		std::wstring MtKey(objname + L"_Mt");
		ssz::object::LoadMaterial(MtKey, L"SpriteShader", Texkey, eRenderingMode::Transparent);
		
		MeshRenderer* Mr = mItemObj->AddComponent<MeshRenderer>();
		Mr->SetMeshRenderer(L"RectMesh", MtKey);
	}
}