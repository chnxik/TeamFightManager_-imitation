#pragma once

namespace ssz
{
	class Champ;
	
	class BattleManager
	{
	public:
		static bool Battle(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // ���� �Լ�

	private:
		static bool Damage(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // ������ ��� �Լ�, HP�� 0���� �������� Dead�� ��ȯ
	};
}