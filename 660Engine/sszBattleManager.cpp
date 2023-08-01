#pragma once
#include "sszBattleManager.h"
#include "sszChamp.h"

namespace ssz
{
    bool BattleManager::Battle(Champ* pAttacker, Champ* pTarget, UINT iDamage)
    {
        if (pTarget->IsPaused()) // Paused�������� Ȯ��, false�� Battle�� ���������� �̷������ ����
            return false;

        if (Damage(pAttacker, pTarget, iDamage)) // ������ �Լ� ȣ��, Target�� ����ϸ� true�� ȣ���Ѵ�.
        {
            // Target�� �������
            // pTarget->SetDead(); ������Ʈ Dead�� �ƴ� ����� Dead�� ������ Pasued ���·� ��ȯ�� Tick�� ���� �ʵ����Ѵ�.
            // respawn Pool�� TargetPtr�� ����ִ´�.
            
            // ��� ���
            // Attacker�� Kill �� ����
            // Target�� Dead�� ����
            
            // assist Ȯ��
            // Attacker Team�� OtherChamp�� Ÿ�� Ȯ��. pTarget�� ������ OtherChamp�� Assist ����
            // OtherChamp�� Target nullptr.

        }

        return true;
    }

    bool BattleManager::Damage(Champ* pAttacker, Champ* pTarget, UINT iDamage)
    {
        Champ::IGStatus* TargetStat = pTarget->GetIGStatus();
        UINT FinalDamage = iDamage - TargetStat->ChampInfo.DEF;
        
        if (FinalDamage <= 0)
            FinalDamage = 1; // ���º��� ���ݷ��� ���ų� ���� ��� �ּҵ������� 1�� �����Ѵ�.

        TargetStat->HP -= FinalDamage;

        // print Damage() ������ ��� �Լ� ȣ��
        // Target�� Transform�� ������ ��ǥ�� �ް� �ش� ��ǥ���� ������ UI�� ���

        // ��� ���
        // IGStatus�� �������ݵ�����, �ǰݵ�����, ȸ����, ų��, �����, ��ü� �Է�
        // IGStatus�� Target�� ���� ������ ����, Attacker�� ���� ������ ����.

        if (0 <= TargetStat->HP) // Target�� ���� �������� 0���Ϸ� ������ ���
        {
            TargetStat->HP = 0; // 0 ���� ����.
            return true;
        }
        
        return false;
    }
}