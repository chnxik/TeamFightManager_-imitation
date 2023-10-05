#include "sszTypeUI.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

extern wchar_t g_strText[_MAX_FNAME];        // 텍스트를 저장하기 위한 변수
extern wchar_t g_strCombine[10];             // 조합 중인 문자
extern wchar_t g_strSpecial[_MAX_FNAME];     // 특수 문자를 위한 변수namespace ssz

namespace ssz
{
	TypeUI::TypeUI(const std::wstring& key)
		: UIObject(key)
		, bTypeMode(false)
		, bPrevSelected(false)
		, istrLen(0)
	{
	}

	TypeUI::~TypeUI()
	{
	}
	
	void TypeUI::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_TypeMt");

		Resources::Load<Texture>(L"TypeBtn_Idle", L"..\\Resources\\useResource\\UI\\type_ui_0.png");
		Resources::Load<Texture>(L"TypeBtn_On", L"..\\Resources\\useResource\\UI\\type_ui_1.png");
		Resources::Load<Texture>(L"TypeBtn_Down", L"..\\Resources\\useResource\\UI\\type_ui_2.png");

		ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"TypeBtn_Idle", eRenderingMode::Transparent);
		
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		ButtonUI* Btn = AddComponent<ButtonUI>();
		Btn->Initialize();
		
		Btn->SetBtnType(ssz::ButtonUI::eBtnType::Togle);

		Btn->SetIdleTex(L"TypeBtn_Idle");
		Btn->SetOnTex(L"TypeBtn_On");
		Btn->SetDownTex(L"TypeBtn_Down");

		Transform* tr = GetComponent<Transform>();
		tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		float FontSize = tr->GetScale().y / 2.f;
		istrLen = (UINT)((tr->GetScale().x / FontSize) - 1);

		Vector3 OffsetPos = tr->GetScale();
		OffsetPos.x = -(OffsetPos.x / 2.f) + 20.f;
		OffsetPos.y = 0.f;
		OffsetPos.z = 0.f;

		Text* tx = AddComponent<Text>();
		tx->TextInit(L"Galmuri14", OffsetPos, FontSize, FONT_RGBA(255, 255, 255, 255), FW1_VCENTER);
	}
	
	void TypeUI::Update()
	{
		UIObject::Update();

		// Seleted 상태면
		ButtonUI* Btn =  GetComponent<ButtonUI>();
		ButtonUI::eBtnState BtnState = Btn->GetBtnState();

		Transform* tr = GetComponent<Transform>();
		tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		float FontSize = tr->GetScale().y / 2.f;

		if (BtnState == ButtonUI::eBtnState::Down)
		{
			// 최대 한글 10 글자
			bTypeMode = true;

			bPrevSelected = true;
			g_strText[istrLen] = 0;

			mStr = g_strText;
			mStr += g_strCombine;
		
			Text* tx = GetComponent<Text>();
			
			tx->SetString(mStr);

			if (Input::GetKey(eKeyCode::ENTER))
			{
				Btn->SetIdle();
			}
		}
		
		if (bPrevSelected && BtnState == ButtonUI::eBtnState::Idle)
		{
			bTypeMode = false;
			bPrevSelected = false;
		
			g_strText[0] = 0;
			g_strCombine[0] = 0;
		}
	}
}