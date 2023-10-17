#include "sszChampSelectSlot.h"

#include "sszTGM.h"

#include "sszBanPickScene.h"

#include "sszChamp.h"
#include "sszPilot.h"

#include "sszButtonUI.h"
#include "sszBanPickWindow.h"
#include "sszPlayerCardSlot.h"

#include "sszAnimator.h"

namespace ssz
{
	ChampSelectSlot::ChampSelectSlot(const std::wstring& Key)
		: UIObject(Key)
		, mPhase(ePhase::BanPhase)
		, OwnerWindowUI(nullptr)
		, mRegistedChamp(nullptr)
		, mChampName(nullptr)
		, mChampTex(nullptr)
		, mSelectLine(nullptr)
		, mPickedOutline(nullptr)
		, mPickedBg(nullptr)
		, bBanned(false)
		, bSelected(false)
		, bPlayerTurn(false)
		, mPickedNumb(nullptr)
		, mBanLine(nullptr)
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
		float OwnerZ = BgTr->GetPosition().z;

		mChampName = AddComponent<Text>();
		mChampName->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -60.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mChampName->SetString(L"NONE");

		// Select Line
		mSelectLine = InstantiateUI<UIObject>(this, L"SlotOutLine");
		Transform* OutlineTr = mSelectLine->GetComponent<Transform>();
		OutlineTr->SetTransType(Transform::eTransType::PosAdd);
		OutlineTr->SetScale(Vector3(130.f, 172.f, 0.002f));
		
		Resources::Load<Texture>(L"SelectLineTex", L"..\\Resources\\useResource\\Banpick\\champion_slot_hover_0.png");
		LoadMaterial(L"SelectLineTexMt", L"SpriteShader", L"SelectLineTex", eRenderingMode::Transparent);
		mSelectLine->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SelectLineTexMt");
		mSelectLine->SetPaused();
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
		if (mPickedOutline->IsActive())
		{
			Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
			Vector3 OlScale = OutlineTr->GetScale();
			float OwnerScalex = GetComponent<Transform>()->GetScale().x;

			if (OwnerScalex < OlScale.x)
			{
				OlScale.x -= 500.f * DT;
				OlScale.y -= 500.f * DT;
				OutlineTr->SetScale(OlScale);
			}
			else if (OwnerScalex > OlScale.x)
			{
				OutlineTr->SetScale(GetComponent<Transform>()->GetScale());
			}
		}

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

	void ChampSelectSlot::MouseLbtnClicked()
	{
		if (!bPlayerTurn)
			return;

		UIObject::MouseLbtnClicked();

		if (bBanned == false && bSelected == false)
		{
			switch (mPhase)
			{
			case ssz::ChampSelectSlot::ePhase::BanPhase:
			{
				mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"BanOutLineMt");

				Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
				Vector3 OlScale = OutlineTr->GetScale();
				OlScale.x *= 1.3f;
				OlScale.y *= 1.3f;
				OutlineTr->SetScale(OlScale);

				Text* OutlineText = mPickedOutline->GetComponent<Text>();
				OutlineText->SetFontColor(10, 10, 10, 255);

				mPickedOutline->SetActive();

				mChampTex->GetComponent<GrayScript>()->UseGrayScript();
				
				std::wstring ChampName = mRegistedChamp->GetChampName();
				Animator* ChampAnim = mChampTex->GetComponent<Animator>();

				std::wstring Idlekey = ChampName + L"_idle";

				ChampAnim->PlayAnimation(Idlekey, false);
				
				bBanned = true;

				BanPickScene* CurScene = (BanPickScene*)SceneManager::GetActiveScene();
				
				mBanLine->GetComponent<Animator>()->PlayAnimation(L"Banned",false);
				mBanLine->SetActive();

				mPickedNumb->SetPaused();

				if (CurScene)
					CurScene->NextPhase();

				break;
			}
			case ssz::ChampSelectSlot::ePhase::SelectPhase:
			{
				std::wstring ChampName = mRegistedChamp->GetChampName();
				std::wstring Selectkey = ChampName + L"_Select";
			
				BanPickScene* CurScene = (BanPickScene*)SceneManager::GetActiveScene();

				if (CurScene)
				{
					PlayerCardSlot* CurPilotSlot = CurScene->GetSelectSlot();
					CurPilotSlot->GetPilot()->RegistChamp(mRegistedChamp);

					switch (CurPilotSlot->GetSlotNumb())
					{
					case 1:
					{
						mPickedNumb->GetComponent<MeshRenderer>()->SetMaterial(L"PickNumb_1Mt");
						break;
					}
					case 2:
					{
						mPickedNumb->GetComponent<MeshRenderer>()->SetMaterial(L"PickNumb_2Mt");
						break;
					}
					}

					mPickedNumb->SetActive();
					bSelected = true;
					
					switch (CurPilotSlot->GetTeamColor())
					{
					case ssz::eTeamColor::Red:
					{
						mPickedBg->GetComponent<MeshRenderer>()->SetMaterial(L"RedChampSlotBgMt");
						mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"RedPickedOutLineMt");
						mPickedBg->SetActive();
						
						Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
						Vector3 OlScale = OutlineTr->GetScale();
						OlScale.x *= 1.3f;
						OlScale.y *= 1.3f;
						OutlineTr->SetScale(OlScale);
						
						mPickedOutline->SetActive();
						break;
					}
					case ssz::eTeamColor::Blue:
					{
						mPickedBg->GetComponent<MeshRenderer>()->SetMaterial(L"BlueChampSlotBgMt");
						mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"BluePickedOutLineMt");
						mPickedBg->SetActive();
						mPickedOutline->SetActive();

						Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
						Vector3 OlScale = OutlineTr->GetScale();
						OlScale.x *= 1.3f;
						OlScale.y *= 1.3f;
						OutlineTr->SetScale(OlScale);

						break;
					}
					}
					

					Animator* ChampAnim = mChampTex->GetComponent<Animator>();
					ChampAnim->PlayAnimation(Selectkey, false);
				}

				break;
			}
			default:
				break;
			}
			
		}
	}

	void ChampSelectSlot::MouseUp()
	{
		OwnerWindowUI->PreviewChampInfo(mRegistedChamp);

		mSelectLine->SetActive();

		if (bBanned == false && bSelected == false)
		{
			if (bPlayerTurn)
			{
				std::wstring ChampName = mRegistedChamp->GetChampName();
				std::wstring OnAnikey = ChampName + L"_On";
				std::wstring Selectkey = ChampName + L"_Select";

				Animator* ChampAnim = mChampTex->GetComponent<Animator>();

				if (ChampAnim->GetCurAnimationKey() != Selectkey)
					ChampAnim->PlayAnimation(OnAnikey, true);
			}
		}

	}

	void ChampSelectSlot::MouseAway()
	{
		mSelectLine->SetPaused();

		std::wstring ChampName = mRegistedChamp->GetChampName();
		Animator* ChampAnim = mChampTex->GetComponent<Animator>();
		
		std::wstring Idlekey = ChampName + L"_idle";
		std::wstring Selectkey = ChampName + L"_Select";
		
		if(ChampAnim->GetCurAnimationKey() != Selectkey)
			ChampAnim->PlayAnimation(Idlekey, false);
		
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

	void ChampSelectSlot::AiPick()
	{
		if (bBanned == false && bSelected == false)
		{
			switch (mPhase)
			{
			case ssz::ChampSelectSlot::ePhase::BanPhase:
			{
				mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"BanOutLineMt");

				Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
				Vector3 OlScale = OutlineTr->GetScale();
				OlScale.x *= 1.3f;
				OlScale.y *= 1.3f;
				OutlineTr->SetScale(OlScale);

				Text* OutlineText = mPickedOutline->GetComponent<Text>();
				OutlineText->SetFontColor(10, 10, 10, 255);

				mPickedOutline->SetActive();

				mChampTex->GetComponent<GrayScript>()->UseGrayScript();

				std::wstring ChampName = mRegistedChamp->GetChampName();
				Animator* ChampAnim = mChampTex->GetComponent<Animator>();

				std::wstring Idlekey = ChampName + L"_idle";

				ChampAnim->PlayAnimation(Idlekey, false);

				bBanned = true;

				BanPickScene* CurScene = (BanPickScene*)SceneManager::GetActiveScene();

				mBanLine->GetComponent<Animator>()->PlayAnimation(L"Banned", false);
				mBanLine->SetActive();

				mPickedNumb->SetPaused();

				if (CurScene)
					CurScene->NextPhase();

				break;
			}
			case ssz::ChampSelectSlot::ePhase::SelectPhase:
			{
				std::wstring ChampName = mRegistedChamp->GetChampName();
				std::wstring Selectkey = ChampName + L"_Select";

				BanPickScene* CurScene = (BanPickScene*)SceneManager::GetActiveScene();

				if (CurScene)
				{
					PlayerCardSlot* CurPilotSlot = CurScene->GetSelectSlot();
					CurPilotSlot->GetPilot()->RegistChamp(mRegistedChamp);

					switch (CurPilotSlot->GetSlotNumb())
					{
					case 1:
					{
						mPickedNumb->GetComponent<MeshRenderer>()->SetMaterial(L"PickNumb_1Mt");
						break;
					}
					case 2:
					{
						mPickedNumb->GetComponent<MeshRenderer>()->SetMaterial(L"PickNumb_2Mt");
						break;
					}
					}
					
					mPickedNumb->SetActive();
					bSelected = true;

					switch (CurPilotSlot->GetTeamColor())
					{
					case ssz::eTeamColor::Red:
					{
						mPickedBg->GetComponent<MeshRenderer>()->SetMaterial(L"RedChampSlotBgMt");
						mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"RedPickedOutLineMt");
						mPickedBg->SetActive();

						Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
						Vector3 OlScale = OutlineTr->GetScale();
						OlScale.x *= 1.3f;
						OlScale.y *= 1.3f;
						OutlineTr->SetScale(OlScale);

						mPickedOutline->SetActive();
						break;
					}
					case ssz::eTeamColor::Blue:
					{
						mPickedBg->GetComponent<MeshRenderer>()->SetMaterial(L"BlueChampSlotBgMt");
						mPickedOutline->GetComponent<MeshRenderer>()->SetMaterial(L"BluePickedOutLineMt");
						mPickedBg->SetActive();
						mPickedOutline->SetActive();

						Transform* OutlineTr = mPickedOutline->GetComponent<Transform>();
						Vector3 OlScale = OutlineTr->GetScale();
						OlScale.x *= 1.3f;
						OlScale.y *= 1.3f;
						OutlineTr->SetScale(OlScale);

						break;
					}
					}


					Animator* ChampAnim = mChampTex->GetComponent<Animator>();
					ChampAnim->PlayAnimation(Selectkey, false);
				}

				break;
			}
			default:
				break;
			}

		}
	}

	void ChampSelectSlot::SlotAnimationSet(eChamp champ)
	{
		// Champ Tex Create
		std::wstring ChampTexKey = GetName() + L"TexObj";
		Transform* SlotTr = GetComponent<Transform>();
		
		float mainz = GetComponent<Transform>()->GetPosition().z;
		// Create ChampTex Obj
		mChampTex = InstantiateUI<UIObject>(Vector3(0.f, 0.f, mainz - 0.002f), this, ChampTexKey);
		mChampTex->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		
		// CreateAnimation
		std::wstring ChampName = mRegistedChamp->GetChampName();
		std::wstring Atlaskey = ChampName + L"_sprite";
		
		std::shared_ptr<Texture> atlas = Resources::Find<Texture>(Atlaskey);

		LoadMaterial(ChampTexKey + L"Mt", L"AnimationShader", atlas, eRenderingMode::Transparent);
		mChampTex->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", ChampTexKey + L"Mt");

		Animator* SlotChampAnim = mChampTex->AddComponent<Animator>();
		
		std::wstring Idlekey = ChampName + L"_idle";
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
		{
			ChampScale = { 256.f, 256.f, 0.f };
			FrmSize = { 128.f, 128.f };
			AtkFrm = 7;
			break;
		}
		case ssz::eChamp::Monk:
		{
			ChampScale = { 128.f, 128.f, 0.f };
			FrmSize = { 64.f, 64.f };
			AtkFrm = 6;
			break;
		}
		case ssz::eChamp::SwordMan:
		{
			ChampScale = { 256.f, 256.f, 0.f };
			FrmSize = { 128.f, 128.f };
			AtkFrm = 5;
			break;
		}
		case ssz::eChamp::Pyromancer:
		{
			ChampScale = { 170.f, 170.f, 0.f };
			FrmSize = { 96.f, 96.f };
			AtkFrm = 8;
			break;
		}
		case ssz::eChamp::Priest:
		{
			ChampScale = { 256.f, 256.f, 0.f };
			FrmSize = { 128.f, 128.f };
			AtkFrm = 10;
			break;
		}
		case ssz::eChamp::Ninja:
		{
			ChampScale = { 256.f, 256.f, 0.f };
			FrmSize = { 128.f, 128.f };
			AtkFrm = 5;
			break;
		}
		case ssz::eChamp::NONE:
			break;
		}

		ChampScale *= 1.3f;
		
		SlotChampAnim->Create(Idlekey, Atlaskey, Vector2(0.f, 0.f), FrmSize, 1, Vector2(0.f, 0.f), 7.f);
		SlotChampAnim->Create(OnAnikey, Atlaskey, Vector2(FrmSize.x, 0.f), FrmSize, 4, Vector2(0.f, 0.f), 7.f);
		SlotChampAnim->Create(Selectkey, Atlaskey, Vector2(0.f, FrmSize.y * 2) , FrmSize, AtkFrm, Vector2(0.f, 0.f), 7.f);

		Transform* ChampTexTr = mChampTex->GetComponent<Transform>();
		ChampTexTr->SetScale(ChampScale);

		Vector3 Pos = (SlotTr->GetPosition() + ChampTexTr->GetPosition());
		Vector3 Scale = SlotTr->GetScale() * 0.9f;
		Scale.y -= 20.f;

		Masking* Mask = mChampTex->AddComponent<Masking>();
		Mask->SetMaskArea(Pos, Scale);
		Mask->StopMasking();	// masking 멈춤
		
		mChampTex->AddComponent<GrayScript>();

		SlotChampAnim->StartEvent(Selectkey) = std::bind(&Masking::UseMasking, mChampTex->GetComponent<Masking>());
		SlotChampAnim->CompleteEvent(Selectkey) = std::bind(&ChampSelectSlot::ChampSelected, this);

		SlotChampAnim->PlayAnimation(Idlekey, true);

		mChampName->SetString(mRegistedChamp->GetChampKrName());

		// SlotPickBg
		mPickedBg = InstantiateUI<UIObject>(this, L"SlotPickBg");
		Transform* PickedBgTr = mPickedBg->GetComponent<Transform>();
		PickedBgTr->SetTransType(Transform::eTransType::PosAdd);
		PickedBgTr->SetPosition(Vector3(0.f, 21.f, mainz - 0.001f));
		PickedBgTr->SetScale(Vector3(121.f, 122.f, 0.f));

		Resources::Load<Texture>(L"SlotPickBg_BlueTex", L"..\\Resources\\useResource\\Banpick\\picked_slot_bg_0.png");
		Resources::Load<Texture>(L"SlotPickBg_RedTex", L"..\\Resources\\useResource\\Banpick\\picked_slot_bg_1.png");
		LoadMaterial(L"BlueChampSlotBgMt", L"SpriteShader", L"SlotPickBg_BlueTex", eRenderingMode::Transparent);
		LoadMaterial(L"RedChampSlotBgMt", L"SpriteShader", L"SlotPickBg_RedTex", eRenderingMode::Transparent);
		mPickedBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BlueChampSlotBgMt");
		mPickedBg->SetPaused();

		// Picked OutLine
		mPickedOutline = InstantiateUI<UIObject>(this, L"PickedOutLine");
		mPickedOutline->AddComponent<PanelUI>();
		Transform* PickedOutLineTr = mPickedOutline->GetComponent<Transform>();
		PickedOutLineTr->SetTransType(Transform::eTransType::PosAdd);
		PickedOutLineTr->SetPosition(Vector3(0.f, 0.f, mainz - 0.003f));
		PickedOutLineTr->SetScale(SlotTr->GetScale());

		Resources::Load<Texture>(L"PickedOutLine_BanTex", L"..\\Resources\\useResource\\Banpick\\banned_slot_front.png");
		Resources::Load<Texture>(L"PickedOutLine_BlueTex", L"..\\Resources\\useResource\\Banpick\\picked_slot_bg_2.png");
		Resources::Load<Texture>(L"PickedOutLine_RedTex", L"..\\Resources\\useResource\\Banpick\\picked_slot_bg_3.png");
		LoadMaterial(L"BanOutLineMt", L"SpriteShader", L"PickedOutLine_BanTex", eRenderingMode::Transparent);
		LoadMaterial(L"BluePickedOutLineMt", L"SpriteShader", L"PickedOutLine_BlueTex", eRenderingMode::Transparent);
		LoadMaterial(L"RedPickedOutLineMt", L"SpriteShader", L"PickedOutLine_RedTex", eRenderingMode::Transparent);
		
		mPickedOutline->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BluePickedOutLineMt");

		Text* OutlineText = mPickedOutline->AddComponent<Text>();
		OutlineText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -60.f, 0.f), 27, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		OutlineText->SetString(mRegistedChamp->GetChampKrName());

		mPickedOutline->SetPaused();

		// Banline
		mBanLine = InstantiateUI<UIObject>(this, L"BanLine");
		Transform* mBanLineTr = mBanLine->GetComponent<Transform>();
		mBanLineTr->SetTransType(Transform::eTransType::PosAdd);
		mBanLineTr->SetPosition(Vector3(0.f, 0.f, mainz - 0.004f));
		mBanLineTr->SetScale(SlotTr->GetScale());

		Resources::Load<Texture>(L"BanLineAtlas", L"..\\Resources\\useResource\\Banpick\\anim\\bananim.png");

		LoadMaterial(L"BannedAnimMt", L"AnimationShader", L"BanLineAtlas", eRenderingMode::Transparent);
		mBanLine->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BannedAnimMt");

		Animator* BanAnim = mBanLine->AddComponent<Animator>();
		BanAnim->Create(L"Banned", L"BanLineAtlas", Vector2(0.f, 0.f), Vector2(52.f, 76.f), 5, Vector2(0.f, 0.f), 24.f);

		BanAnim->CompleteEvent(L"Banned") = std::bind(&UIObject::SetPaused, mBanLine);
		mBanLine->SetPaused();

		// PickedNumb;
		mPickedNumb = InstantiateUI<UIObject>(mPickedOutline, L"PickedNumb");
		Transform* NumbTr = mPickedNumb->GetComponent<Transform>();
		NumbTr->SetTransType(Transform::eTransType::PosAdd);
		NumbTr->SetPosition(Vector3(41.f, 62.f, mainz - 0.005f));
		NumbTr->SetScale(Vector3(24.f, 29.f, 0.f));
		

		Resources::Load<Texture>(L"PickNumb_1Tex", L"..\\Resources\\useResource\\Banpick\\pick_number_0.png");
		Resources::Load<Texture>(L"PickNumb_2Tex", L"..\\Resources\\useResource\\Banpick\\pick_number_1.png");
		LoadMaterial(L"PickNumb_1Mt", L"SpriteShader", L"PickNumb_1Tex", eRenderingMode::Transparent);
		LoadMaterial(L"PickNumb_2Mt", L"SpriteShader", L"PickNumb_2Tex", eRenderingMode::Transparent);
		mPickedNumb->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PickNumb_1Mt");
	}

	void ChampSelectSlot::ChampSelected()
	{
		std::wstring ChampName = mRegistedChamp->GetChampName();
		Animator* ChampAnim = mChampTex->GetComponent<Animator>();

		std::wstring Idlekey = ChampName + L"_idle";
		ChampAnim->PlayAnimation(Idlekey, false);

		BanPickScene* CurScene = (BanPickScene*)SceneManager::GetActiveScene();

		if (CurScene)
			CurScene->NextPhase();

		// 마스킹 끝
		Masking* Mask = mChampTex->GetComponent<Masking>();
		Mask->StopMasking();
	}

	void ChampSelectSlot::StateClear()
	{
		mChampTex->GetComponent<GrayScript>()->StopGrayScript();
		mPickedOutline->GetComponent<Text>()->SetFontColor(255, 255, 255, 255);
		mPickedBg->SetPaused();
		mPickedOutline->SetPaused();

		bPlayerTurn = false;
		bBanned = false;
		bSelected = false;
	}
}