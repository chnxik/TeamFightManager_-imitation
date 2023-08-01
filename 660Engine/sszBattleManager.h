#pragma once

namespace ssz
{
	class Champ;

	class BattleManager
	{
	public:
		static bool Battle(Champ* pAttacker, Champ* pTarget, UINT iDamage); // 전투 함수

	private:
		static bool Damage(Champ* pAttacker, Champ* pTarget, UINT iDamage); // 데미지 계산 함수, HP가 0으로 떨어지면 Dead를 반환
	};
}