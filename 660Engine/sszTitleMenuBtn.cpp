#include "sszTitleMenuBtn.h"
#include "CommonHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	TitleMenuBtn::TitleMenuBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, mLeftSwordObj(nullptr)
		, mRightSwordObj(nullptr)
		, fRatio(0.f)
		, vOnSize{}
		, vOffSize{}
	{
	}

	TitleMenuBtn::~TitleMenuBtn()
	{
	}
	
	void TitleMenuBtn::Initialize()
	{
		std::wstring mtKey(mUIKey + L"_BtnMt");
		ssz::object::LoadMaterial(mtKey, L"SpriteShader", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", mtKey);
		
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(155.f, 42.f, 0.f));

		mBtnComp = AddComponent<ButtonUI>();
		mBtnComp->Initialize();

		
		Resources::Load<Texture>(L"Title_sel_indicator_Atlas", L"..\\Resources\\useResource\\Title\\menu\\select_indicator_sword_animation.png");
		LoadMaterial(L"LTitle_sel_indicator_Atlas_Mt", L"AnimationShader", L"Title_sel_indicator_Atlas", eRenderingMode::Transparent);
		LoadMaterial(L"RTitle_sel_indicator_Atlas_Mt", L"AnimationShader", L"Title_sel_indicator_Atlas", eRenderingMode::Transparent);
		
		mLeftSwordObj = Instantiate<GameObject>(eLayerType::ObjectForUI);
		mLeftSwordObj->GetComponent<Transform>()->SetScale(Vector3(54.f, 21.f, 1.f));
		mLeftSwordObj->SetPaused();
		mLeftSwordObj->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LTitle_sel_indicator_Atlas_Mt");
		Animator* LindicatorAnim = mLeftSwordObj->AddComponent<Animator>();
		LindicatorAnim->Create(L"Title_sel_indicator_Left", L"Title_sel_indicator_Atlas", Vector2(0.f, 0.f), Vector2(18.f, 7.f), 5, Vector2(0.f, 0.f), 8.f);

		mRightSwordObj = Instantiate<GameObject>(eLayerType::ObjectForUI);
		mRightSwordObj->GetComponent<Transform>()->SetScale(Vector3(54.f, 21.f, 1.f));
		mRightSwordObj->SetPaused();
		mRightSwordObj->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"RTitle_sel_indicator_Atlas_Mt");
		Animator* RindicatorAnim = mRightSwordObj->AddComponent<Animator>();
		RindicatorAnim->Create(L"Title_sel_indicator_Right", L"Title_sel_indicator_Atlas", Vector2(0.f, 7.f), Vector2(18.f, 7.f), 5, Vector2(0.f, 0.f), 8.f);
	}
	
	void TitleMenuBtn::Update()
	{
		if (IsMouseOn())
		{
			fRatio += DT;

			if (1.f < fRatio)
			{
				fRatio = 0.f;

				mLeftSwordObj->GetComponent<Animator>()->PlayAnimation(L"Title_sel_indicator_Left",false);
				mRightSwordObj->GetComponent<Animator>()->PlayAnimation(L"Title_sel_indicator_Right",false);
			}
		}

		UIObject::Update();
	}
	
	void TitleMenuBtn::LateUpdate()
	{
		UIObject::LateUpdate();
	}
	
	void TitleMenuBtn::Render()
	{
		UIObject::Render();
	}
	
	void TitleMenuBtn::SetNewGameBtn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 trScale = { 132.f, 42.f, 0.f };
		tr->SetScale(trScale);

		Resources::Load<Texture>(L"Title_NewGame_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_NewGame_Idle.png");
		Resources::Load<Texture>(L"Title_NewGame_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_NewGame_Over.png");
		mBtnComp->SetIdleTex(L"Title_NewGame_Idle");
		mBtnComp->SetOnTex(L"Title_NewGame_Over");
		mBtnComp->SetDownTex(L"Title_NewGame_Over");

		Vector3 LeftPos = tr->GetPosition();
		LeftPos.x -= 15.f + trScale.x;
		Vector3 RightPos = tr->GetPosition();
		RightPos.x += 15.f + trScale.x;

		mRightSwordObj->GetComponent<Transform>()->SetPosition(RightPos);
		mLeftSwordObj->GetComponent<Transform>()->SetPosition(LeftPos);

		vOnSize = trScale * 1.15f;
		vOffSize = trScale;
	}
	
	void TitleMenuBtn::SetLoadBtn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 trScale = { 152.f, 42.f, 0.f };
		tr->SetScale(trScale);

		Resources::Load<Texture>(L"Title_Load_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_Load_Idle.png");
		Resources::Load<Texture>(L"Title_Load_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_Load_Over.png");
		mBtnComp->SetIdleTex(L"Title_Load_Idle");
		mBtnComp->SetOnTex(L"Title_Load_Over");
		mBtnComp->SetDownTex(L"Title_Load_Over");

		Vector3 LeftPos = tr->GetPosition();
		LeftPos.x -= 15.f + trScale.x;
		Vector3 RightPos = tr->GetPosition();
		RightPos.x += 15.f + trScale.x;

		mRightSwordObj->GetComponent<Transform>()->SetPosition(RightPos);
		mLeftSwordObj->GetComponent<Transform>()->SetPosition(LeftPos);

		vOnSize = trScale * 1.15f;
		vOffSize = trScale;
	}
	
	void TitleMenuBtn::SetExitBtn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 trScale = { 155.f, 42.f, 0.f };
		
		tr->SetScale(trScale);

		Resources::Load<Texture>(L"Title_Exit_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_Exit_Idle.png");
		Resources::Load<Texture>(L"Title_Exit_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_Exit_Over.png");
		mBtnComp->SetIdleTex(L"Title_Exit_Idle");
		mBtnComp->SetOnTex(L"Title_Exit_Over");
		mBtnComp->SetDownTex(L"Title_Exit_Over");

		Vector3 LeftPos = tr->GetPosition();
		LeftPos.x -= 15.f + trScale.x;
		Vector3 RightPos = tr->GetPosition();
		RightPos.x += 15.f + trScale.x;

		mRightSwordObj->GetComponent<Transform>()->SetPosition(RightPos);
		mLeftSwordObj->GetComponent<Transform>()->SetPosition(LeftPos);

		vOnSize = trScale * 1.15f;
		vOffSize = trScale;
	}
	
	void TitleMenuBtn::MouseUp()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(vOnSize);

		mRightSwordObj->SetActive();
		mLeftSwordObj->SetActive();

		mLeftSwordObj->GetComponent<Animator>()->PlayAnimation(L"Title_sel_indicator_Left", false);
		mRightSwordObj->GetComponent<Animator>()->PlayAnimation(L"Title_sel_indicator_Right", false);
	}

	void TitleMenuBtn::MouseAway()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(vOffSize);

		mRightSwordObj->SetPaused();
		mLeftSwordObj->SetPaused();
	}
}