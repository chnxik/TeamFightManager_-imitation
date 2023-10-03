#include "sszBanPickWindow.h"

#include "sszBanPickStat.h"

namespace ssz
{
	BanPickWindow::BanPickWindow(const std::wstring& key)
		: mBanLine(nullptr)
		, mBanPickStat{}
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

	}

	void BanPickWindow::Done()
	{
	}
}