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
		, mDefaultInfo{} // 챔프 정보
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
		GameObject::Update();
	}

	void Champ::LateUpdate()
	{
		GameObject::LateUpdate();
		GetComponent<Text>()->SetString(std::to_wstring(mIGInfo.HP));
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
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::IDLE], true);
	}

	void Champ::Play_Move()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::MOVE], true);
	}

	void Champ::Play_Attack()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::ATTACK], false);
	}

	void Champ::Play_Dead()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::DEAD], false);
	}


	void Champ::Play_Skill1()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::SKILL1], true);
	}


	void Champ::Play_Skill2()
	{
		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eAnimType::SKILL2], true);
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
		InitIGInfo(0, 0); //
	}

	void Champ::Battle()
	{
		if(mTargetEnemy != nullptr)
			BattleManager::Battle(this, mTargetEnemy, mIGInfo.ChampInfo.ATK);
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