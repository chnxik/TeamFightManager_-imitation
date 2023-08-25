#pragma once
#include "sszChamp.h"
#include "CommonObjHeader.h"

#include "sszBattleManager.h"
#include "sszChamp_Script.h"
#include "sszLog.h"

namespace ssz
{
	Champ::Champ()
		: mFriendly{}
		, mPilot(nullptr)
		, mChampInfo{} // 챔프 정보
		, mTargetFriendly(nullptr)
		, mTargetEnemy(nullptr)
		, mColObjs{}
		, mChampScript(nullptr)
		, vecAnimKey{}
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
		Text* tx = AddComponent<Text>();

		tx->SetOffsetPos(Vector3(20.f, -50.f, -0.1f));
		tx->SetFontSize(40.f);
		tx->SetFontColor(255, 255, 255, 255);
	}

	void Champ::Update()
	{
		if (mChampStatus.accTime_Skill < mChampStatus.CoolTime_Skill)
		{
			mChampStatus.accTime_Skill += (float)Time::DeltaTime();
		}

		GameObject::Update();
	}

	void Champ::LateUpdate()
	{
		if (mTargetEnemy != nullptr && !(mTargetEnemy->IsActive()))
			mTargetEnemy = nullptr;
		if (mTargetFriendly != nullptr && !(mTargetFriendly->IsActive()))
			mTargetFriendly = nullptr;

		GameObject::LateUpdate();

		GetComponent<Text>()->SetString(std::to_wstring(mChampStatus.HP));
	}

	void Champ::Render()
	{
		GameObject::Render();
	}

	void Champ::Dead()
	{
		Play_Dead();
		
		Collider2D* Col = GetComponent<Collider2D>();
		
		if(!Col->IsPaused())
			Col->ColliderPaused();

		std::wstring szbuffer;
		szbuffer = GetName() + L" 사망";
		Log::AddLog(szbuffer);
	}

	void Champ::Play_Idle()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::IDLE], true);
	}

	void Champ::Play_Move()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::MOVE], true);
	}

	void Champ::Play_Attack()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::ATTACK], false);
	}

	void Champ::Play_Dead()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::DEAD], false);
	}


	void Champ::Play_Skill()
	{
		
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::SKILL], true);
	}


	void Champ::Play_Ultimate()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::ULTIMATE], true);
	}

	void Champ::SetChampScript(Champ_Script* script)
	{
		mChampScript = script;
	}

	void Champ::SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd)
	{
		mChampInfo.ChampType = Type;
		mChampInfo.ATK = atk;
		mChampInfo.APD = apd;
		mChampInfo.RNG = rng;
		mChampInfo.DEF = def;
		mChampInfo.MAXHP = hp;
		mChampInfo.SPD = spd;
	}

	void Champ::InitChampStatus(UINT ATKpt, UINT DEFpt)
	{
		mChampStatus.ChampInfo = mChampInfo;
		mChampStatus.ChampInfo.ATK = mChampInfo.ATK + ATKpt;    // 공격력
		mChampStatus.ChampInfo.DEF = mChampInfo.DEF + DEFpt;    // 방어력

		mChampStatus.HP = mChampStatus.ChampInfo.MAXHP;         // 현재 체력
		mChampStatus.accTime_Skill = 0.f;						// 공격 쿨타임
		mChampStatus.CoolTime_Skill = 0.f;						// 스킬 쿨타임

		mChampStatus.UltimateUseTime = 60.f;					// 궁극기 사용 시점
		mChampStatus.bULTIMATE = false;							// 궁극기 사용 여부

		mChampStatus.RespawnTime = 0.f;

		mChampStatus.TotalDeal = 0;
		mChampStatus.TotalDamaged = 0;
		mChampStatus.TotalHeal = 0;
		mChampStatus.KILLPOINT = 0;
		mChampStatus.DEATHPOINT = 0;
		mChampStatus.ASSISTPOINT = 0;
	}

	void Champ::ResetInfo()
	{
		mPilot = nullptr;

		mFriendly.clear();
		mEnemys.clear();
		mTargetEnemy = nullptr;
		mTargetFriendly = nullptr;

		InitChampStatus(0, 0);
	}

	void Champ::RespawnInfo()
	{
		mTargetEnemy = nullptr;
		mTargetFriendly = nullptr;

		mChampStatus.HP = mChampStatus.ChampInfo.MAXHP;         // 현재 체력
		mChampStatus.accTime_Skill = 0.f;						// 공격 쿨타임
		mChampStatus.CoolTime_Skill = 0.f;						// 스킬 쿨타임

		mChampStatus.RespawnTime = 0.f;
	}

	void Champ::ATTACK()
	{
		BattleManager::ATTACK(this, mTargetEnemy, mChampStatus.ChampInfo.ATK);
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
	void Champ::SetState(eState state)
	{
		GameObject::SetState(state);

		for (ColObj* object : mColObjs)
		{
			if (object != nullptr)
				object->SetState(state);
		}
	}
}