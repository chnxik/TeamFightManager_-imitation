#pragma once
#include "sszEngine.h"

namespace ssz
{
	class SpawnEfc;
	class Champ;

	class BattleManager
	{
	public:
		static bool ATTACK(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // 전투 함수


	public: // 리스폰
		static void Initialize();
		static void RespawnClear();
		static void Update();
		static void LateUpdate();

		static void RegistRespawnPool(Champ* Target);
		static void SpawnChamp(Champ* Target);

	private:
		static bool Damage(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // 데미지 계산 함수, HP가 0으로 떨어지면 Dead를 반환
		static void DamagePrint(unsigned int Dmg, Champ* pTarget);

		static void DamageFontInit();

	private:
		static std::list<Champ*> mRespawn;
	};
}