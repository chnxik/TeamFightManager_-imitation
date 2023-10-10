#include "sszStatusBar.h"
#include "sszTGM.h"

#include "sszGuageScript.h"

#include "sszPilot.h"
#include "sszTeam.h"
#include "sszChamp.h"

namespace ssz
{
	StatusBar::StatusBar()
		: mOwnerChamp(nullptr)
		, mPilotName(nullptr)
		, mHPBar(nullptr)
		, mCoolTimeBar(nullptr)
		, mUseUltIcon(nullptr)
		, mChampHP(nullptr)
		, mSkillCoolTime(nullptr)
		, bUseUlt(nullptr)
	{
	}

	StatusBar::~StatusBar()
	{
		delete mHPBar;
		delete mCoolTimeBar;
		delete mUseUltIcon;
		
		mHPBar = nullptr;
		mCoolTimeBar = nullptr;
		mUseUltIcon = nullptr;
	}

	void StatusBar::Initialize()
	{
		// GuageBar Layout
		Transform* Tr = GetComponent<Transform>();

		Vector3 Scale = { 90.f, 18.f, 1.f };
		
		Tr->SetScale(Scale);
		Tr->SetPosition(Vector3(0.f, -50.f, 0.f));

		Resources::Load<Texture>(L"GuageBarTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		LoadMaterial(L"GuageBarMt", L"SpriteShader", L"GuageBarTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh",L"GuageBarMt");

		// HP Guage
		mHPBar = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), Scale);
		mHPBar->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		GuageScript* HPg = mHPBar->AddComponent<GuageScript>();

		Resources::Load<Texture>(L"PlayerHPGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		Resources::Load<Texture>(L"EnemyHPGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		LoadMaterial(L"PlayerHPGuageMt", L"GuageShader", L"PlayerHPGuageTex", eRenderingMode::Transparent);
		LoadMaterial(L"EnemyHPGuageMt", L"GuageShader", L"EnemyHPGuageTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerHPGuageMt");

		// CoolTime
		mCoolTimeBar = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), Scale);
		mCoolTimeBar->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		GuageScript* Coolg = mCoolTimeBar->AddComponent<GuageScript>();

		Resources::Load<Texture>(L"CoolGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		LoadMaterial(L"CoolGuageMt", L"SpriteShader", L"CoolGuageTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CoolGuageMt");


		// ult icon
		mUseUltIcon = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), Vector3(30.f, 30.f, 1.f));
		mUseUltIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		Resources::Load<Texture>(L"UltIconTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		LoadMaterial(L"UltIconMt", L"SpriteShader", L"UltIconTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UltIconMt");
		
	}

	void StatusBar::Update()
	{
		GameObject::Update();
		mHPBar->Update();
		mCoolTimeBar->Update();
		mUseUltIcon->Update();
	}

	void StatusBar::LateUpdate()
	{
		GameObject::LateUpdate();
		mHPBar->LateUpdate();
		mCoolTimeBar->LateUpdate();
		mUseUltIcon->LateUpdate();
	}

	void StatusBar::Render()
	{
		GameObject::Render();
		mHPBar->Render();
		mCoolTimeBar->Render();
		mUseUltIcon->Render();
	}

	void StatusBar::RegistGame(Champ* champ)
	{
		mOwnerChamp = champ;
		
		Transform* tr = GetComponent<Transform>();
		Transform* ChampTr = champ->GetComponent<Transform>();
		tr->SetParent(ChampTr);
		tr->SetTransType(Transform::eTransType::PosAdd);
		
		std::wstring PlayerTeamName = TGM::GetPlayerTeam()->GetTeamName();
		std::wstring ThisTeamName = mOwnerChamp->GetTeam()->GetTeamName();

		if(PlayerTeamName == ThisTeamName)
			GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerHPGuageMt");
		else
			GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"EnemyHPGuageMt");
	}
}