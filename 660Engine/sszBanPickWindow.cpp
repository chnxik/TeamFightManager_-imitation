#include "sszBanPickWindow.h"

#include "sszBanPickStat.h"
#include "sszChamp.h"
#include "sszBanPickStat.h"

#include "sszTGM.h"
#include "sszText.h"

namespace ssz
{
	BanPickWindow::BanPickWindow(const std::wstring& key)
		: mBanLine(nullptr)
		, mBanPickStat{}
		, mClassTypeText(nullptr)
		, mClassNameText(nullptr)
		, mChampPreview(nullptr)
		, mSkillIcon(nullptr)
		, mUltIcon(nullptr)
		, mSkillCoolIcon(nullptr)
		, mUltCoolIcon(nullptr)
		, mSkillCool(nullptr)
		, mUltCool(nullptr)
		, mSkillInfo(nullptr)
		, mUltInfo(nullptr)
	{
	}

	BanPickWindow::~BanPickWindow()
	{
	}

	void BanPickWindow::Initialize()
	{
		std::wstring MtKey(mUIKey + L"WindowMt");

		Resources::Load<Texture>(L"BanpickBgTex", L"..\\Resources\\useResource\\BanPick\\banpick_ui_bg.png");
		ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BanpickBgTex", eRenderingMode::Transparent);

		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		AddComponent<PanelUI>();
		AddComponent<Collider2D>();

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(1920.f, 1080.f, 1.f));

		// StatSlot
		mBanPickStat[(UINT)eStatType::ATK] = InstantiateUI<BanPickStat>(Vector3(-375.f, -116.f, 1.02f), this, L"ATKStatSlot");
		mBanPickStat[(UINT)eStatType::DEF] = InstantiateUI<BanPickStat>(Vector3(-215.f, -116.f, 1.02f), this, L"DEFStatSlot");
		mBanPickStat[(UINT)eStatType::APD] = InstantiateUI<BanPickStat>(Vector3(-375.f, -185, 1.02f), this, L"APDStatSlot");
		mBanPickStat[(UINT)eStatType::HP] = InstantiateUI<BanPickStat>(Vector3(-215.f, -185, 1.02f), this, L"HPStatSlot");
		mBanPickStat[(UINT)eStatType::RNG] = InstantiateUI<BanPickStat>(Vector3(-375.f, -254.f, 1.02f), this, L"RNGStatSlot");
		mBanPickStat[(UINT)eStatType::SPD] = InstantiateUI<BanPickStat>(Vector3(-215.f, -254.f, 1.02f), this, L"SPDStatSlot");

		mBanPickStat[(UINT)eStatType::ATK]->SetSlot(eStatType::ATK);
		mBanPickStat[(UINT)eStatType::DEF]->SetSlot(eStatType::DEF);
		mBanPickStat[(UINT)eStatType::APD]->SetSlot(eStatType::APD);
		mBanPickStat[(UINT)eStatType::HP]->SetSlot(eStatType::HP);
		mBanPickStat[(UINT)eStatType::RNG]->SetSlot(eStatType::RNG);
		mBanPickStat[(UINT)eStatType::SPD]->SetSlot(eStatType::SPD);

		float mainz = GetComponent<Transform>()->GetPosition().z;

		// ChampPreview
		mChampPreview = InstantiateUI<UIObject>(Vector3(-535.f, -180.f, mainz), Vector3(116.f, 116.f, 0.f), this, L"ChampPreview");
		mChampPreview->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		
		LoadMaterial(L"ChampPreviewMt", L"SpriteShader", eRenderingMode::Transparent);
		mChampPreview->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ChampPreviewMt");

		mClassTypeText = mChampPreview->AddComponent<Text>();
		mClassNameText = mChampPreview->AddComponent<Text>();
		
		mClassTypeText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, 78.f, mainz), 25, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mClassNameText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -85.f, mainz), 25, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		

		// Skill & Ult
		mSkillIcon = InstantiateUI<UIObject>(Vector3(0.f, 50.f, mainz), Vector3(50.f, 50.f, 0.f), this, L"PreviewSkillIcon");
		mUltIcon = InstantiateUI<UIObject>(Vector3(0.f, -50.f, mainz), Vector3(50.f, 50.f, 0.f), this, L"PreviewUltIcon");
		mSkillCoolIcon = InstantiateUI<UIObject>(Vector3(20.f, 0.f, mainz), Vector3(50.f, 50.f, 0.f), this, L"PreviewSkillCoolIcon");
		mUltCoolIcon = InstantiateUI<UIObject>(Vector3(20.f, 0.f, mainz), Vector3(50.f, 50.f, 0.f), this, L"PreviewUltCoolIcon");

		mSkillIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		mUltIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		mSkillCoolIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		mUltCoolIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		
		Text* SkillText = mSkillIcon->AddComponent<Text>();
		Text* UltText = mUltIcon->AddComponent<Text>();

		SkillText->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		UltText->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);

		SkillText->SetString(L"���");
		UltText->SetString(L"�ñر�");

		mSkillCool = mSkillIcon->AddComponent<Text>();
		mUltCool = mUltIcon->AddComponent<Text>();
		mSkillInfo = mSkillIcon->AddComponent<Text>();
		mUltInfo = mUltIcon->AddComponent<Text>();

		mSkillCool->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mUltCool->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mSkillInfo->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mUltInfo->TextInit(Text::eFonts::Galmuri14, Vector3(30.f, 0.f, mainz), 20, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);

		
		PreviewChampInfo(TGM::GetChamp(eChamp::Archer));
	}

	void BanPickWindow::PreviewChampInfo(Champ* champ)
	{
		Champ::tChampInfo champinfo = champ->GetChampInfo();
		
		mChampPreview->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(champ->GetSlotTex());

		mClassTypeText->SetString(champ->GetChampClassType());
		mClassNameText->SetString(champ->GetChampKrName());

		mSkillCool->SetString(L"��ų��");
		mUltCool->SetString(L"�ñ���");
		mSkillInfo->SetString(L"��ų����");
		mUltInfo->SetString(L"�ñؼ���");

		mBanPickStat[(UINT)eStatType::ATK]->SetValue(champinfo.ATK);
		mBanPickStat[(UINT)eStatType::DEF]->SetValue(champinfo.DEF);
		mBanPickStat[(UINT)eStatType::APD]->SetValue(champinfo.APD);
		mBanPickStat[(UINT)eStatType::HP] ->SetValue(champinfo.MAXHP);
		mBanPickStat[(UINT)eStatType::RNG]->SetValue(champinfo.RNG);
		mBanPickStat[(UINT)eStatType::SPD]->SetValue(champinfo.SPD);


	}

	void BanPickWindow::Done()
	{
	}
}