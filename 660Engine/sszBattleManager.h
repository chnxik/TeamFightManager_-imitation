#pragma once

namespace ssz
{
	class Champ;

	class BattleManager
	{
	public:
		static bool Battle(Champ* pAttacker, Champ* pTarget, UINT iDamage); // ���� �Լ�

	private:
		static bool Damage(Champ* pAttacker, Champ* pTarget, UINT iDamage); // ������ ��� �Լ�, HP�� 0���� �������� Dead�� ��ȯ
	};
}