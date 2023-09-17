#include "sszWeeklyEventBtn.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	WeeklyEventBtn::WeeklyEventBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
	{
		
	}

	WeeklyEventBtn::~WeeklyEventBtn()
	{
	}
	void WeeklyEventBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"WeeklyEventRedBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_0.png");
			Resources::Load<Texture>(L"WeeklyEventRedBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_1.png");
			Resources::Load<Texture>(L"WeeklyEventGrayBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_3.png");
			Resources::Load<Texture>(L"WeeklyEventGrayBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\weekly\\weekly_event_button_4.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"WeeklyEventRedBtnIdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"WeeklyEventRedBtnIdleTex");
			mBtnComp->SetOnTex(L"WeeklyEventRedBtnOnTex");

			// type별로 활성화되지 않은 상태도 구현해야함

			// Set default Size
			GetComponent<Transform>()->SetScale(Vector3(340.f, 60.f, 1.f));
		}
#pragma endregion
	}
}
