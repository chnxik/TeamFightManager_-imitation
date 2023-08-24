#pragma once
#include "sszBattleManager.h"
#include "CommonObjHeader.h"
#include "sszLog.h"

#define RESPAWNTIME 3.0f

namespace ssz
{
    std::list<Champ*> BattleManager::mRespawn;

    bool BattleManager::ATTACK(Champ* pAttacker, Champ* pTarget, unsigned int iDamage)
    {
        if (pTarget->IsPaused()) // Paused�������� Ȯ��, false�� Battle�� ���������� �̷������ ����
            return false;

        if (Damage(pAttacker, pTarget, iDamage)) // ������ �Լ� ȣ��, Target�� ����ϸ� true�� ȣ���Ѵ�.
        {
            // Target�� �������
            pTarget->Dead();
            pAttacker->SetTarget_Enemy(nullptr);
            // RegistRespawnPool(pTarget); // ������Ʈ Dead�� �ƴ� ����� Dead�� ������ Pasued ���·� ��ȯ�� Tick�� ���� �ʵ����Ѵ�.
            
            // ��� ���
            // Attacker�� Kill �� ����
            // Target�� Dead�� ����
            
            // assist Ȯ��
            // Attacker Team�� OtherChamp�� Ÿ�� Ȯ��. pTarget�� ������ OtherChamp�� Assist ����
            // OtherChamp�� Target nullptr.
            return false;
        }

        return true;
    }

    void BattleManager::RespawnClear()
    {
        std::list<Champ*>::iterator iter = mRespawn.begin();

        while (iter != mRespawn.end())
            iter = mRespawn.erase(iter);
    }

    void BattleManager::Update()
    {
        std::list<Champ*>::iterator iter = mRespawn.begin();

        while (iter != mRespawn.end())
        {
            (*iter)->GetChampStatus()->RespawnTime += (float)Time::DeltaTime();
            
            if ((*iter)->GetChampStatus()->RespawnTime > RESPAWNTIME)
            {
                RespawnChamp((*iter));
                iter = mRespawn.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    void BattleManager::LateUpdate()
    {
    }

    void BattleManager::RegistRespawnPool(Champ* Target)
    {
        if (Target->IsActive())
            Target->SetState(GameObject::eState::Paused);

        Target->GetChampStatus()->RespawnTime = 0.f;
        
        mRespawn.push_back(Target);
    }

    void BattleManager::RespawnChamp(Champ* Target)
    {
        if (Target->IsPaused())
            Target->SetState(GameObject::eState::Active);

        Target->ResetInfo();
        Target->GetComponent<Collider2D>()->ColliderActive();
        Target->Play_Idle();

        std::wstring szbuffer;
        szbuffer = Target->GetName() + L" ������";
        Log::AddLog(szbuffer);
    }

    bool BattleManager::Damage(Champ* pAttacker, Champ* pTarget, unsigned int iDamage)
    {
        Champ::tChampStatus* TargetStat = pTarget->GetChampStatus();
        int FinalDamage = iDamage - TargetStat->ChampInfo.DEF;
        
        if (FinalDamage <= 0)
            FinalDamage = 1; // ���º��� ���ݷ��� ���ų� ���� ��� �ּҵ������� 1�� �����Ѵ�.

        TargetStat->HP -= FinalDamage;

        // �α׿�
        std::wstring szbuffer;
        szbuffer = pAttacker->GetName() + L" ����, ������ : " + std::to_wstring(iDamage);
        Log::AddLog(szbuffer);

        // print Damage() ������ ��� �Լ� ȣ��
        // Target�� Transform�� ������ ��ǥ�� �ް� �ش� ��ǥ���� ������ UI�� ���

        // ��� ���
        // IGStatus�� �������ݵ�����, �ǰݵ�����, ȸ����, ų��, �����, ��ü� �Է�
        // IGStatus�� Target�� ���� ������ ����, Attacker�� ���� ������ ����.

        if (0 >= TargetStat->HP) // Target�� ���� �������� 0���Ϸ� ������ ���
        {
            TargetStat->HP = 0; // 0 ���� ����.
            return true;
        }
        
        return false;
    }
}