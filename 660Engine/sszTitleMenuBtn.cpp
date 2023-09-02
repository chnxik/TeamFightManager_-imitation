#include "sszTitleMenuBtn.h"
#include "CommonObjHeader.h"

namespace ssz
{
	TitleMenuBtn::TitleMenuBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
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
	}
	
	void TitleMenuBtn::Update()
	{
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
		tr->SetScale(Vector3(132.f, 42.f, 0.f));

		Resources::Load<Texture>(L"Title_NewGame_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_NewGame_Idle.png");
		Resources::Load<Texture>(L"Title_NewGame_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_NewGame_Over.png");
		mBtnComp->SetIdleTex(L"Title_NewGame_Idle");
		mBtnComp->SetOnTex(L"Title_NewGame_Over");
		mBtnComp->SetDownTex(L"Title_NewGame_Over");
	}
	
	void TitleMenuBtn::SetLoadBtn()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(152.f, 42.f, 0.f));

		Resources::Load<Texture>(L"Title_Load_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_Load_Idle.png");
		Resources::Load<Texture>(L"Title_Load_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_Load_Over.png");
		mBtnComp->SetIdleTex(L"Title_Load_Idle");
		mBtnComp->SetOnTex(L"Title_Load_Over");
		mBtnComp->SetDownTex(L"Title_Load_Over");
	}
	
	void TitleMenuBtn::SetExitBtn()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(155.f, 42.f, 0.f));

		Resources::Load<Texture>(L"Title_Exit_Idle", L"..\\Resources\\useResource\\Title\\menu\\Title_Exit_Idle.png");
		Resources::Load<Texture>(L"Title_Exit_Over", L"..\\Resources\\useResource\\Title\\menu\\Title_Exit_Over.png");
		mBtnComp->SetIdleTex(L"Title_Exit_Idle");
		mBtnComp->SetOnTex(L"Title_Exit_Over");
		mBtnComp->SetDownTex(L"Title_Exit_Over");
	}
	void TitleMenuBtn::MouseUp()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 vPos = tr->GetScale();
		vPos *= 0.1f;
		tr->AddScale(vPos.x, vPos.y, 0);
	}
	void TitleMenuBtn::MouseAway()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 vPos = tr->GetScale();
		vPos *= 0.1f;
		tr->AddScale(-vPos.x, -vPos.y, 0);
	}
}