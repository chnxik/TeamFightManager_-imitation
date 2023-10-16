#include "sszChampSelectSlot.h"

#include "sszTGM.h"

#include "sszChamp.h"

#include "sszButtonUI.h"
#include "sszBanPickWindow.h"

#include "sszAnimator.h"

namespace ssz
{
	ChampSelectSlot::ChampSelectSlot(const std::wstring& Key)
		: UIObject(Key)
		, OwnerWindowUI(nullptr)
		, mRegistedChamp(nullptr)
		, mChampName(nullptr)
		, mChampTex(nullptr)
		, mSelectLine(nullptr)
		, mPickedOutline(nullptr)
		, mPickedBg(nullptr)
		, bBanned(false)
		, bSelected(false)
	{
	}

	ChampSelectSlot::~ChampSelectSlot()
	{
	}

	void ChampSelectSlot::Initialize()
	{
		AddComponent<PanelUI>();

		Resources::Load<Texture>(L"ChampSlotBgTex", L"..\\Resources\\useResource\\Banpick\\champion_slot_bg.png");
		LoadMaterial(L"ChampSlotBgMt", L"SpriteShader", L"ChampSlotBgTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ChampSlotBgMt");

		AddComponent<ButtonUI>();

		Transform* BgTr = GetComponent<Transform>();
		BgTr->SetTransType(Transform::eTransType::PosAdd);
		BgTr->SetScale(Vector3(120.f, 162.f, 0.f));

		mChampName = AddComponent<Text>();
		mChampName->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -60.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mChampName->SetString(L"NONE");
		
	}

	void ChampSelectSlot::Update()
	{
		UIObject::Update();
		// 선택상태에따라 Mt를 바꾸는 방법.
		// 평소상태에선 SpriteShader 를 사용한 Mt
		// MouseOn 혹은 선택시 AnimationShader를 사용한 Mt로 변경
		// BanPick시에는 SpriteShader를 사용하나 상수버퍼로 Gray값 전달

	}

	void ChampSelectSlot::LateUpdate()
	{
		UIObject::LateUpdate();
	}

	void ChampSelectSlot::Render()
	{
		UIObject::Render();
	}

	void ChampSelectSlot::SetState(eState state)
	{
	}

	void ChampSelectSlot::RegistRespawnPool()
	{
	}

	void ChampSelectSlot::SetActive()
	{
	}

	void ChampSelectSlot::SetPaused()
	{
	}

	void ChampSelectSlot::MouseLbtnDown()
	{
	}

	void ChampSelectSlot::MouseLbtnUp()
	{
	}

	void ChampSelectSlot::MouseLbtnClicked()
	{
		if (bBanned == false && bSelected == false)
		{
			if (!mRegistedChamp)
				return;

			std::wstring ChampName = mRegistedChamp->GetChampName();
			std::wstring Selectkey = ChampName + L"_Select";
			
			Animator* ChampAnim = mChampTex->GetComponent<Animator>();
			ChampAnim->PlayAnimation(Selectkey, true);

			mChampTex->GetComponent<Masking>()->UseMasking();
		}
	}

	void ChampSelectSlot::MouseOn()
	{
	}

	void ChampSelectSlot::MouseUp()
	{
		if (bBanned == false && bSelected == false)
		{
			if (!mRegistedChamp)
				return;

			std::wstring ChampName = mRegistedChamp->GetChampName();
			
			std::wstring OnAnikey = ChampName + L"_On";

			Animator* ChampAnim = mChampTex->GetComponent<Animator>();
			ChampAnim->PlayAnimation(OnAnikey, true);
		}
	}

	void ChampSelectSlot::MouseAway()
	{
		if (!mRegistedChamp)
			return;

		std::wstring ChampName = mRegistedChamp->GetChampName();
		Animator* ChampAnim = mChampTex->GetComponent<Animator>();
		std::wstring Idlekey = ChampName + L"idle";
		ChampAnim->PlayAnimation(Idlekey, false);

		mChampTex->GetComponent<Masking>()->StopMasking();
	}

	void ChampSelectSlot::RegistChamp(eChamp champ)
	{
		mRegistedChamp = TGM::GetChamp(champ);
		
		if (mRegistedChamp == nullptr)
			return;

		// SlotAnimationSet
		
		SlotAnimationSet(champ);
	}

	void ChampSelectSlot::RegistWindowUI(BanPickWindow* BPWin)
	{
		OwnerWindowUI = BPWin;
	}

	void ChampSelectSlot::SlotAnimationSet(eChamp champ)
	{
		// Champ Tex Create
		std::wstring ChampTexKey = GetName() + L"TexObj";
		Transform* SlotTr = GetComponent<Transform>();

		// Create ChampTex Obj
		mChampTex = InstantiateUI<UIObject>(Vector3(0.f, 0.f, GetComponent<Transform>()->GetPosition().z), this, ChampTexKey);
		mChampTex->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		
		// CreateAnimation
		std::wstring ChampName = mRegistedChamp->GetChampName();
		std::wstring Atlaskey = ChampName + L"_sprite";
		
		std::shared_ptr<Texture> atlas = Resources::Find<Texture>(Atlaskey);

		LoadMaterial(ChampTexKey + L"Mt", L"AnimationShader", atlas, eRenderingMode::Transparent);
		mChampTex->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", ChampTexKey + L"Mt");

		Animator* SlotChampAnim = mChampTex->AddComponent<Animator>();
		
		std::wstring Idlekey = ChampName + L"idle";
		std::wstring OnAnikey = ChampName + L"_On";
		std::wstring Selectkey = ChampName + L"_Select";

		Vector2 FrmSize = {};
		Vector3 ChampScale = {};
		UINT	AtkFrm = 1;

		switch (champ)
		{
		case ssz::eChamp::Archer:
		{
			ChampScale = { 128.f, 128.f, 0.f };
			FrmSize = { 64.f, 64.f };
			AtkFrm = 7;
			break;
		}
		case ssz::eChamp::Knight:
		{
			ChampScale = { 170.f, 170.f, 0.f };
			FrmSize = { 96.f, 96.f };
			AtkFrm = 7;
			break;
		}
		case ssz::eChamp::Fighter:
			break;
		case ssz::eChamp::Monk:
			break;
		case ssz::eChamp::SwordMan:
			break;
		case ssz::eChamp::Pyromancer:
			break;
		case ssz::eChamp::Priest:
			break;
		case ssz::eChamp::Ninja:
			break;
		case ssz::eChamp::NONE:
			break;
		}

		ChampScale *= 1.3f;
		
		SlotChampAnim->Create(Idlekey, Atlaskey, Vector2(0.f, 0.f), FrmSize, 1, Vector2(0.f, 0.f), 7.f);
		SlotChampAnim->Create(OnAnikey, Atlaskey, Vector2(0.f, 0.f), FrmSize, 4, Vector2(0.f, 0.f), 7.f);
		SlotChampAnim->Create(Selectkey, Atlaskey, Vector2(0.f, FrmSize.y * 2) , FrmSize, AtkFrm, Vector2(0.f, 0.f), 7.f);

		Transform* ChampTexTr = mChampTex->GetComponent<Transform>();
		ChampTexTr->SetScale(ChampScale);

		Vector3 Pos = (SlotTr->GetPosition() + ChampTexTr->GetPosition());
		Vector3 Scale = SlotTr->GetScale() * 0.9f;

		Masking* Mask = mChampTex->AddComponent<Masking>();
		Mask->SetMaskArea(Pos, Scale);
		Mask->StopMasking();	// masking 멈춤

		SlotChampAnim->PlayAnimation(Idlekey, true);

		mChampName->SetString(mRegistedChamp->GetChampKrName());
	}

	void ChampSelectSlot::StateClear()
	{
		bBanned = false;
		bSelected = false;
	}
}