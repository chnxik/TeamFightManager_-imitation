#include "sszProceedBtn.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	ProceedBtn::ProceedBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, ProceedBtnArrowMark(nullptr)
		, mDefalutMarkPos_x(80.f)
		, mKBDIcon(nullptr)
	{
	}

	ProceedBtn::~ProceedBtn()
	{
	}
	void ProceedBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"ProceedBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_0.png");
			Resources::Load<Texture>(L"ProceedBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_1.png");
			Resources::Load<Texture>(L"ProceedBtnDownTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_3.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"ProceedBtnIdleTex", eRenderingMode::Transparent);

			Resources::Load<Texture>(L"ProceedBtnArrowMarkTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\proceed\\proceed_button_2.png");

			ssz::object::LoadMaterial(L"ProceedBtnArrowMarkMt", L"SpriteShader", L"ProceedBtnArrowMarkTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"ProceedBtnIdleTex");
			mBtnComp->SetOnTex(L"ProceedBtnOnTex");
			mBtnComp->SetDownTex(L"ProceedBtnDownTex");

			// Set default Size
			GetComponent<Transform>()->SetScale(Vector3(340.f, 120.f, 1.f));
		}
#pragma endregion
#pragma region Mark
		{
			// SetPanel
			AddComponent<PanelUI>();

			// Add MarkTex
			float BtnPosz = GetComponent<Transform>()->GetPosition().z;

			ProceedBtnArrowMark = ssz::object::InstantiateUI<UIObject>(Vector3(mDefalutMarkPos_x, 0.f, BtnPosz - 0.0001f), Vector3(170.f, 120.f, 0.f), this, L"ProceedArrowMark");
			ProceedBtnArrowMark->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ProceedBtnArrowMarkMt");
			ProceedBtnArrowMark->GetComponent<Transform>()->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}

	void ProceedBtn::Update()
	{
		if (mBtnComp->GetBtnState() == ButtonUI::eBtnState::On ||
			mBtnComp->GetBtnState() == ButtonUI::eBtnState::Down)
		{
			MarkAnimation();
		}
		else
		{
			Transform* Tr = ProceedBtnArrowMark->GetComponent<Transform>();
			Vector3 Pos = Tr->GetPosition();
			Pos.x = mDefalutMarkPos_x;
			Tr->SetPosition(Pos);
		}

		GameObject::Update();
	}
	void ProceedBtn::MarkAnimation()
	{
		Transform* Tr = ProceedBtnArrowMark->GetComponent<Transform>();
		Vector3 Pos = Tr->GetPosition();

		float fForce = (mDefalutMarkPos_x - Pos.x) + 1;

		Pos.x += fForce * 4.f * (float)Time::DeltaTime();

		// 0부터 80 까지
		if (mDefalutMarkPos_x < Pos.x)
			Pos.x = 40.f;

		Tr->SetPosition(Pos);
	}
	void ProceedBtn::SetKBDIcon(KBDIcon::KEYICON key)
	{
		mKBDIcon = new KBDIcon(L"KeyIcon");
		mKBDIcon->SetIcon(key);

		AddChildUI((UIObject*)mKBDIcon);
	}
}
