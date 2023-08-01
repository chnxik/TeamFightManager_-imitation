#include "sszChamp.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Champ::Champ()
		: mFriendly{}
		, mDefaultInfo{} // è�� ����
		, mTargetEnemy(nullptr)
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
		mDefaultInfo.MAXHP = hp;
		mDefaultInfo.SPD = spd;
	}

	void Champ::InitIGInfo(UINT ATKpt, UINT DEFpt)
	{
		mIGInfo.ChampInfo = mDefaultInfo;
		mIGInfo.ChampInfo.ATK = mDefaultInfo.ATK + ATKpt;           // ���ݷ�
		mIGInfo.ChampInfo.DEF = mDefaultInfo.DEF + DEFpt;           // ����

		mIGInfo.HP = mIGInfo.ChampInfo.MAXHP;             // ���� ü��
		mIGInfo.COOLTIME = 0.f;   // ��ų1 ��Ÿ��
		mIGInfo.bULTIMATE = false; // �ñر� ��� ����

		mIGInfo.TotalDeal = 0;
		mIGInfo.TotalDamaged = 0;
		mIGInfo.TotalHeal = 0;
		mIGInfo.KILLPOINT = 0;
		mIGInfo.DEATHPOINT = 0;
		mIGInfo.ASSISTPOINT = 0;
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
}