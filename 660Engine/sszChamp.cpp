#include "sszChamp.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Champ::Champ()
		: mChampInfo{} // Ã¨ÇÁ Á¤º¸
	{

	}

	Champ::~Champ()
	{

	}

	void Champ::SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd)
	{
		mChampInfo.ChampType = Type;
		mChampInfo.ATK = atk;
		mChampInfo.APD = apd;
		mChampInfo.RNG = rng;
		mChampInfo.DEF = def;
		mChampInfo.HP = hp;
		mChampInfo.SPD = spd;
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