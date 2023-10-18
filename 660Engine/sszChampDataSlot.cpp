#include "sszChampDataSlot.h"
#include "sszPlayerCardSlot.h"

#include "CommonHeader.h"

#include "sszChamp.h"
#include "sszPilot.h"


namespace ssz
{
	ChampDataSlot::ChampDataSlot(const std::wstring& key)
		: mOwnerSlot(nullptr)
		, mRegistedChamp(nullptr)
		, mSlotTitle(nullptr)	// 정보
		, mScoreTypeK(nullptr)	// K
		, mScoreTypeD(nullptr)	// D
		, mScoreTypeA(nullptr)	// A
		, mScoreK(nullptr)	// K
		, mScoreD(nullptr)	// D
		, mScoreA(nullptr)	// A
		, mDeal(nullptr)
		, mDamaged(nullptr)
		, mHeal(nullptr)
	{
	}

	ChampDataSlot::~ChampDataSlot()
	{
	}
	
	void ChampDataSlot::LateUpdate()
	{
		Champ::tChampStatus* Info = mRegistedChamp->GetChampStatus();
		
		UINT Deal = Info->TotalDeal;
		UINT Damaged = Info->TotalDamaged;
		UINT Heal = Info->TotalHeal;
		UINT K = Info->KILLPOINT;
		UINT D = Info->DEATHPOINT;
		UINT A = Info->ASSISTPOINT;

		mScoreK->SetString(	std::to_wstring(K));
		mScoreD->SetString(std::to_wstring(D));
		mScoreA->SetString(std::to_wstring(A));
		mDeal->SetString(std::to_wstring(Deal));
		mDamaged->SetString(std::to_wstring(Damaged));
		mHeal->SetString(std::to_wstring(Heal));

		UIObject::LateUpdate();
	}

	void ChampDataSlot::Initialize()
	{
		Resources::Load<Texture>(L"data_ui_blueTex", L"..\\Resources\\useResource\\stadium\\data_ui_bg_0.png");
		Resources::Load<Texture>(L"data_ui_redTex", L"..\\Resources\\useResource\\stadium\\data_ui_bg_1.png");

		LoadMaterial(L"data_ui_blueMt", L"SpriteShader", L"data_ui_blueTex", eRenderingMode::Transparent);
		LoadMaterial(L"data_ui_redMt", L"SpriteShader", L"data_ui_redTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"data_ui_blueMt");

		mSlotTitle = AddComponent<Text>();	// 정보
		mScoreTypeK = AddComponent<Text>();	// K
		mScoreTypeD = AddComponent<Text>();	// D
		mScoreTypeA = AddComponent<Text>();	// A
		mScoreK = AddComponent<Text>();	// K
		mScoreD = AddComponent<Text>();	// D
		mScoreA = AddComponent<Text>();	// A
		mDeal = AddComponent<Text>();
		mDamaged = AddComponent<Text>();
		mHeal = AddComponent<Text>();

		mSlotTitle->SetString(L"정보");
		mScoreTypeK->SetString(L"K");
		mScoreTypeD->SetString(L"D");
		mScoreTypeA->SetString(L"A");
		mScoreK->SetString(L"0");
		mScoreD->SetString(L"0");
		mScoreA->SetString(L"0");
		mDeal->SetString(L"0");
		mDamaged->SetString(L"0");
		mHeal->SetString(L"0");

		mSlotTitle->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, 90.f, 0.f), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		
		mScoreTypeK->TextInit(Text::eFonts::Galmuri9, Vector3(-35.f, 47.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mScoreTypeD->TextInit(Text::eFonts::Galmuri9, Vector3(0.f, 47.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mScoreTypeA->TextInit(Text::eFonts::Galmuri9, Vector3(35.f, 47.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		
		mScoreK->TextInit(Text::eFonts::Galmuri9, Vector3(-35.f, 17.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mScoreD->TextInit(Text::eFonts::Galmuri9, Vector3(0.f, 17.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mScoreA->TextInit(Text::eFonts::Galmuri9, Vector3(35.f, 17.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		
		mDeal->TextInit(Text::eFonts::Galmuri9, Vector3(20.f, -25.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mDamaged->TextInit(Text::eFonts::Galmuri9, Vector3(20.f, -60.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mHeal->TextInit(Text::eFonts::Galmuri9, Vector3(20.f, -95.f, 0.f), 30, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
	}

	void ChampDataSlot::RegistPlayerCardSlot(PlayerCardSlot* Slot)
	{
		mOwnerSlot = Slot;
		
		Transform* OwnerTr = mOwnerSlot->GetComponent<Transform>();
		Vector3 scale = OwnerTr->GetScale();
		float OwnerScale = scale.x;
		scale.x = scale.y * 0.525f;
		GetComponent<Transform>()->SetScale(scale);

		MeshRenderer* Mr = GetComponent<MeshRenderer>();

		switch (mOwnerSlot->GetTeamColor())
		{
		case ssz::eTeamColor::Red:
		{
			Mr->SetMaterial(L"data_ui_redMt");
			break;
		}
		case ssz::eTeamColor::Blue:
		{
			Mr->SetMaterial(L"data_ui_blueMt");
			break;
		}
		}
	}
}