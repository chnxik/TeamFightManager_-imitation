#include "sszProceedBtn.h"
#include "CommonObjHeader.h"

namespace ssz
{
	ProceedBtn::ProceedBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
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
			float BtnPosz = GetComponent<Transform>()->GetPosition().y;

			UIObject* ProceedBtnArrowMark = ssz::object::InstantiateUI<UIObject>(Vector3(80.f, 0.f, BtnPosz - 0.0001f), Vector3(170.f, 120.f, 1.f), this, L"ProceedArrowMark");
			ProceedBtnArrowMark->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ProceedBtnArrowMarkMt");
			ProceedBtnArrowMark->GetComponent<Transform>()->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}
}
