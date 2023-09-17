#pragma once
#include "sszLogoSelectBtn.h"
#include "CommonObjHeader.h"

#include "sszSelectBtnUI.h"
#include "sszTeamIcon.h"

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

	void LogoSelectBtn::InitTeamLogo(wstring Texkey, UINT idx, Vector3 Pos, UIObject* parent, TeamIcon* Delegate)
	{
		mTexkey = Texkey;
		
		GetComponent<SelectBtnUI>()->SetDelegateW(Delegate, (DELEGATEW)&TeamIcon::ChangeLogo, Texkey);

		Pos.z -= 0.00001f;
		
		wstring objname = L"TeamLogoObj_" + std::to_wstring(idx);
		mTeamIcon = InstantiateUI<UIObject>(Pos, Vector3(100.f, 100.f, 1.f), parent, objname);
		
		Transform* TeamIconTr = mTeamIcon->GetComponent<Transform>();
		TeamIconTr->SetTransType(Transform::eTransType::PosAdd);
		
		std::wstring MtKey(objname + L"_Mt");
		ssz::object::LoadMaterial(MtKey, L"SpriteShader", Texkey, eRenderingMode::Transparent);
		
		MeshRenderer* Mr = mTeamIcon->AddComponent<MeshRenderer>();
		Mr->SetMeshRenderer(L"RectMesh", MtKey);
	}
}