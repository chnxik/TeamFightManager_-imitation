#include "sszStatusBar.h"
#include "CommonObjHeader.h"

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
	{
	}

	StatusBar::~StatusBar()
	{
	}

	void StatusBar::Initialize()
	{

	}

	void StatusBar::Update()
	{
	}

	void StatusBar::LateUpdate()
	{
	}

	void StatusBar::Render()
	{
	}

	void StatusBar::RegistGame(Champ* champ)
	{
		mOwnerChamp = champ;
		
		Transform* tr = GetComponent<Transform>();
		Transform* ChampTr = champ->GetComponent<Transform>();
		tr->SetParent(ChampTr);
		tr->SetTransType(Transform::eTransType::PosAdd);

		

	}
}