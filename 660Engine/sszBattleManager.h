#pragma once

namespace ssz
{
	class SpawnEfc;

	class BattleManager
	{
	public:
		static bool ATTACK(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // ���� �Լ�


	public: // ������
		static void RespawnClear();
		static void Update();
		static void LateUpdate();

		static void RegistRespawnPool(Champ* Target);
		static void SpawnChamp(Champ* Target);

	private:
		static bool Damage(Champ* pAttacker, Champ* pTarget, unsigned int iDamage); // ������ ��� �Լ�, HP�� 0���� �������� Dead�� ��ȯ

	private:
		static std::list<Champ*> mRespawn;
	};
}