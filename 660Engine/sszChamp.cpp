#include "sszChamp.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Champ::Champ()
		: mDefaultInfo{} // è�� ����
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
		mIGStatus.ATK =	mDefaultInfo.ATK + ATKpt;           // ���ݷ�
		mIGStatus.APD = mDefaultInfo.APD;        // ���ݼӵ�
		mIGStatus.RNG = mDefaultInfo.RNG;           // ��Ÿ�
		mIGStatus.DEF = mDefaultInfo.DEF + DEFpt;           // ����
		mIGStatus.MAXHP = mDefaultInfo.HP;         // �ִ� ü��
		mIGStatus.SPD = mDefaultInfo.SPD;           // �̵��ӵ�

		mIGStatus.HP = mIGStatus.MAXHP;             // ���� ü��
		mIGStatus.COOLTIME = 0.f;   // ��ų1 ��Ÿ��
		mIGStatus.bULTIMATE = false; // �ñر� ��� ����
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