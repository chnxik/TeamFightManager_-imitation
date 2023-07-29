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
}