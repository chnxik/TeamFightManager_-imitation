#include "sszChamp.h"
#include "CommonObjHeader.h"

#include "sszChamp_Script.h"

namespace ssz
{
	Champ::Champ()
		: mFriendly{}
		, mPilot(nullptr)
		, mDefaultInfo{} // 챔프 정보
		, mTargetEnemy(nullptr)
		, mColObjs{}
		, mChampScript(nullptr)
	{

	}

	Champ::~Champ()
	{
		for (ColObj* object : mColObjs)
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}
	}

	void Champ::Initialize()
	{
	}

	void Champ::Update()
	{
		GameObject::Update();
	}

	void Champ::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Champ::Render()
	{
		GameObject::Render();
	}

	void Champ::Dead()
	{
	}

	void Champ::Play_Idle()
	{
		mChampScript->Play_Idle();
	}

	void Champ::Play_Move()
	{
		mChampScript->Play_Move();
	}

	void Champ::Play_Attack()
	{
		mChampScript->Play_Attack();
	}

	void Champ::Play_Dead()
	{
		mChampScript->Play_Dead();
	}


	void Champ::Play_Skill1()
	{
		mChampScript->Play_Skill1();
	}


	void Champ::Play_Skill2()
	{
		mChampScript->Play_Skill2();
	}

	void Champ::SetChampScript(Champ_Script* script)
	{
		mChampScript = script;
	}

	void Champ::SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd)
	{
		mDefaultInfo.ChampType = Type;
		mDefaultInfo.ATK = atk;
		mDefaultInfo.APD = apd;
		mDefaultInfo.RNG = rng;
		mDefaultInfo.DEF = def;
		mDefaultInfo.MAXHP = hp;
		mDefaultInfo.SPD = spd;
	}

	void Champ::InitIGInfo(UINT ATKpt, UINT DEFpt)
	{
		mIGInfo.ChampInfo = mDefaultInfo;
		mIGInfo.ChampInfo.ATK = mDefaultInfo.ATK + ATKpt;           // 공격력
		mIGInfo.ChampInfo.DEF = mDefaultInfo.DEF + DEFpt;           // 방어력

		mIGInfo.HP = mIGInfo.ChampInfo.MAXHP;             // 현재 체력
		mIGInfo.COOLTIME = 0.f;   // 스킬1 쿨타임
		mIGInfo.bULTIMATE = false; // 궁극기 사용 여부

		mIGInfo.TotalDeal = 0;
		mIGInfo.TotalDamaged = 0;
		mIGInfo.TotalHeal = 0;
		mIGInfo.KILLPOINT = 0;
		mIGInfo.DEATHPOINT = 0;
		mIGInfo.ASSISTPOINT = 0;
	}

	void Champ::ResetInfo()
	{
		mFriendly.clear();
		mPilot = nullptr;
		mTargetEnemy = nullptr;
		InitIGInfo(0, 0);
	}

	ColObj* Champ::CreateColObj(eColObjType Type)
	{
		if (mColObjs[(UINT)Type] != nullptr)
			return mColObjs[(UINT)Type];

		mColObjs[(UINT)Type] = Instantiate<ColObj>();
		mColObjs[(UINT)Type]->AddComponent<Collider2D>();

		return mColObjs[(UINT)Type];
	}

	void Champ::ColObjSetLayer(eColObjType Type)
	{
		if (mColObjs[(UINT)Type] == nullptr)
			assert(nullptr);

		switch (GetLayerType())
		{
		case ssz::enums::eLayerType::Player:
		{
			mColObjs[(UINT)Type]->SetLayerType(eLayerType::PlayerInteraction);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerInteraction, mColObjs[(UINT)Type]);
			break;
		}
		case ssz::enums::eLayerType::Enemy:
		{
			mColObjs[(UINT)Type]->SetLayerType(eLayerType::EnemyInteraction);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyInteraction, mColObjs[(UINT)Type]);
			break;
		}
		}
	}

	Collider2D* Champ::GetColObjsCol(eColObjType Type)
	{
		if (mColObjs[(UINT)Type] == nullptr)
			return nullptr;

		return mColObjs[(UINT)Type]->GetComponent<Collider2D>();
	}
}