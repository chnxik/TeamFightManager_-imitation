#include "sszChamp.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Champ::Champ()
		: mDefaultInfo{} // 챔프 정보
	{

	}

	Champ::~Champ()
	{

	}

	void Champ::Dead()
	{
	}

	void Champ::SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd)
	{
		mDefaultInfo.ChampType = Type;
		mDefaultInfo.ATK = atk;
		mDefaultInfo.APD = apd;
		mDefaultInfo.RNG = rng;
		mDefaultInfo.DEF = def;
		mDefaultInfo.HP = hp;
		mDefaultInfo.SPD = spd;
	}

	void Champ::SetIGStatus(UINT ATKpt, UINT DEFpt)
	{
		mIGStatus.ATK =	mDefaultInfo.ATK + ATKpt;           // 공격력
		mIGStatus.APD = mDefaultInfo.APD;        // 공격속도
		mIGStatus.RNG = mDefaultInfo.RNG;           // 사거리
		mIGStatus.DEF = mDefaultInfo.DEF + DEFpt;           // 방어력
		mIGStatus.MAXHP = mDefaultInfo.HP;         // 최대 체력
		mIGStatus.SPD = mDefaultInfo.SPD;           // 이동속도

		mIGStatus.HP = mIGStatus.MAXHP;             // 현재 체력
		mIGStatus.COOLTIME = 0.f;   // 스킬1 쿨타임
		mIGStatus.bULTIMATE = false; // 궁극기 사용 여부
	}

	ColObj* Champ::CreateColObj(const std::wstring& key)
	{
		ColObj* NewObj = nullptr;
		switch (GetLayerType())
		{
		case ssz::enums::eLayerType::Player:
			NewObj = Instantiate<ColObj>(eLayerType::PlayerInteraction);
			break;
		case ssz::enums::eLayerType::Enemy:
			NewObj = Instantiate<ColObj>(eLayerType::EnemyInteraction);
			break;
		}

		if (NewObj == nullptr)
			return nullptr;

		NewObj->SetName(key);
		NewObj->AddComponent<Collider2D>();
		mColObjs.insert(std::make_pair(key, NewObj));

		return NewObj;
	}

	Collider2D* Champ::FindColObjsCol(const std::wstring& key)
	{
		std::map<std::wstring, ColObj*>::iterator iter
			= mColObjs.find(key);

		if (iter != mColObjs.end())
			return iter->second->GetComponent<Collider2D>();

		return nullptr;
	}
	
	void Champ::RegistEnemy(const std::wstring& key, Champ* pChamp)
	{
		std::map<std::wstring, Champ*>::iterator iter
			= mEnemyTeam.find(key);

		if (iter != mEnemyTeam.end())
			return;

		mEnemyTeam.insert(std::make_pair(key, pChamp));
	}

	Champ* Champ::GetEnemy(const std::wstring& key)
	{
		std::map<std::wstring, Champ*>::iterator iter
			= mEnemyTeam.find(key);
		if (iter != mEnemyTeam.end())
			return nullptr;

		return iter->second;
	}
}