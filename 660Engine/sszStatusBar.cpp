#include "sszStatusBar.h"
#include "sszTGM.h"

#include "CommonHeader.h"

#include "sszGuageScript.h"

#include "sszPilot.h"
#include "sszTeam.h"
#include "sszChamp.h"

namespace ssz
{
	StatusBar::StatusBar()
		: mOwnerChamp(nullptr)
		, mPilotName(nullptr)
		, mGuageBg(nullptr)
		, mHPBar(nullptr)
		, mCoolTimeBar(nullptr)
		, mUseUltIcon(nullptr)
		, bUseUlt(nullptr)
	{
	}

	StatusBar::~StatusBar()
	{
		delete mGuageBg;
		delete mHPBar;
		delete mCoolTimeBar;
		delete mUseUltIcon;
		
		mGuageBg = nullptr;
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
		Tr->SetPosition(Vector3(20.f, -50.f, -0.0000001f));

		Resources::Load<Texture>(L"GuageBarTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_5.png");
		LoadMaterial(L"GuageBarMt", L"SpriteShader", L"GuageBarTex", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh",L"GuageBarMt");

		// GuageBar Bg
		Resources::Load<Texture>(L"PlayerGuageBgTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_1.png");
		Resources::Load<Texture>(L"EnemyGuageBgTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_0.png");
		LoadMaterial(L"PlayerGuageBgMt", L"SpriteShader", L"PlayerGuageBgTex", eRenderingMode::Transparent);
		LoadMaterial(L"EnemyGuageBgMt", L"SpriteShader", L"EnemyGuageBgTex", eRenderingMode::Transparent);


		mGuageBg = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), Scale);
		Transform* GuageBgTr = mGuageBg->GetComponent<Transform>();
		GuageBgTr->SetParent(Tr);
		GuageBgTr->SetTransType(Transform::eTransType::PosAdd);
		mGuageBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerGuageBgMt");
		

		// HP Guage
		mHPBar = Instantiate<GameObject>(Vector3(-1.f, 3.f, 0.f), Vector3(89.f, 8.f, 1.f));
		Transform* HPTr = mHPBar->GetComponent<Transform>();
		HPTr->SetParent(Tr);
		HPTr->SetTransType(Transform::eTransType::PosAdd);
		GuageScript* HPg = mHPBar->AddComponent<GuageScript>();

		Resources::Load<Texture>(L"PlayerHPGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_4.png");
		Resources::Load<Texture>(L"EnemyHPGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_3.png");
		LoadMaterial(L"PlayerHPGuageMt", L"GuageShader", L"PlayerHPGuageTex", eRenderingMode::Transparent);
		LoadMaterial(L"EnemyHPGuageMt", L"GuageShader", L"EnemyHPGuageTex", eRenderingMode::Transparent);
		mHPBar->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerHPGuageMt");

		// CoolTime
		mCoolTimeBar = Instantiate<GameObject>(Vector3(0.f, -5.f, 0.f), Vector3(90.f, 5.f, 1.f));
		Transform* CoolTr = mCoolTimeBar->GetComponent<Transform>();
		CoolTr->SetParent(Tr);
		CoolTr->SetTransType(Transform::eTransType::PosAdd);
		GuageScript* Coolg = mCoolTimeBar->AddComponent<GuageScript>();

		Resources::Load<Texture>(L"CoolGuageTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\player_ingame_guage_2.png");
		LoadMaterial(L"CoolGuageMt", L"GuageShader", L"CoolGuageTex", eRenderingMode::Transparent);
		mCoolTimeBar->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CoolGuageMt");


		// ult icon
		mUseUltIcon = Instantiate<GameObject>(Vector3(-63.f, -6.f, 0.f), Vector3(36.f, 36.f, 1.f));
		Transform* UltTr = mUseUltIcon->GetComponent<Transform>();
		UltTr->SetParent(Tr);
		UltTr->SetTransType(Transform::eTransType::PosAdd);

		Resources::Load<Texture>(L"UltIconTex", L"..\\Resources\\useResource\\ChampSprite\\StatusBar\\ult_on_ui.png");
		LoadMaterial(L"UltIconMt", L"SpriteShader", L"UltIconTex", eRenderingMode::Transparent);
		mUseUltIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"UltIconMt");

		// PilotName

		Vector3 PilotNamePos(-40.f, -23.f, 0.f);

		mPilotName = AddComponent<Text>();
		mPilotName->TextInit(Text::eFonts::Silver, PilotNamePos, 30.f, FONT_RGBA(255, 255, 255, 255), FW1_LEFT | FW1_VCENTER);
		mPilotName->SetString(L"NONE");
	}

	void StatusBar::Update()
	{
		GameObject::Update();
		mGuageBg->Update();
		mHPBar->Update();
		mCoolTimeBar->Update();
		mUseUltIcon->Update();
	}

	void StatusBar::LateUpdate()
	{
		GameObject::LateUpdate();
		mGuageBg->LateUpdate();
		mHPBar->LateUpdate();
		mCoolTimeBar->LateUpdate();
		mUseUltIcon->LateUpdate();
	}

	void StatusBar::Render()
	{
		mGuageBg->Render();
		mHPBar->Render();
		mCoolTimeBar->Render();
		mUseUltIcon->Render();
		GameObject::Render();
	}

	void StatusBar::RegistChamp(Champ* champ)
	{
		mOwnerChamp = champ;

		Transform* tr = GetComponent<Transform>();
		Transform* ChampTr = champ->GetComponent<Transform>();
		tr->SetParent(ChampTr);
		tr->SetTransType(Transform::eTransType::PosAdd);

		int HP = mOwnerChamp->GetChampStatus()->ChampInfo.MAXHP;
		mHPBar->GetComponent<GuageScript>()->SetValue(mOwnerChamp->GetChampStatus()->ChampInfo.MAXHP, mOwnerChamp->GetChampHPptr());
		mCoolTimeBar->GetComponent<GuageScript>()->SetValue(mOwnerChamp->GetChampStatus()->CoolTime_Skill, mOwnerChamp->GetChampCoolptr());

	}

	void StatusBar::RegistGame(Pilot* Pilot)
	{
		std::wstring PlayerTeamName = TGM::GetPlayerTeam()->GetTeamName();
		std::wstring ThisTeamName = mOwnerChamp->GetTeam()->GetTeamName();
		
		mPilotName->SetString(Pilot->GetPilotName());

		if (PlayerTeamName == ThisTeamName)
		{
			mHPBar->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerHPGuageMt");
			mGuageBg->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerGuageBgMt");
			// mPilotName->SetFontColor(0, 255, 0, 255);
		}
		else
		{
			mHPBar->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"EnemyHPGuageMt");
			mGuageBg->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"EnemyGuageBgMt");
			// mPilotName->SetFontColor(255, 0, 0, 255);
		}
	}
}