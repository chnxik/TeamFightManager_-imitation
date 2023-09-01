#pragma once
#include "sszBattleManager.h"
#include "CommonObjHeader.h"
#include "sszLog.h"

#include "sszChamp_Script.h"
#include "sszSpawnEfc.h"
#include "sszNumb.h"

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

    void BattleManager::Initialize()
    {
        DamageFontInit();
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
            float* rtime = &((*iter)->GetChampStatus()->RespawnTime);
            *rtime += (float)Time::DeltaTime();
            

            if (*rtime >= RESPAWNTIME)
            {
                SpawnChamp((*iter));
                iter = mRespawn.erase(iter);
            }


            else
            {
                SpawnEfc* efc = (*iter)->GetEfc();

                if (*rtime >= RESPAWNTIME - 0.3f
                    && !efc->IsPlay())
                {
                    Vector3 pos = (*iter)->GetComponent<Transform>()->GetPosition();
                    efc->Play(pos);
                }

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

    void BattleManager::SpawnChamp(Champ* Target)
    {
        if (Target->IsPaused())
            Target->SetState(GameObject::eState::Active);
        Target->GetEfc()->reset();
        Target->RespawnInfo();
        Target->GetComponent<Collider2D>()->ColliderActive();
        Target->Play_Idle();
        

        std::wstring szbuffer;
        szbuffer = Target->GetName() + L" ����";
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
        szbuffer = pAttacker->GetName() + L" ����, ������ : " + std::to_wstring(FinalDamage);
        Log::AddLog(szbuffer);

        pTarget->GetChampScript()->Damaged();

        // print Damage() ������ ��� �Լ� ȣ��
        // Target�� Transform�� ������ ��ǥ�� �ް� �ش� ��ǥ���� ������ UI�� ���
        DamagePrint(FinalDamage, pTarget);

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
    void BattleManager::DamagePrint(unsigned int Dmg, Champ* pTarget)
    {
        Transform* TargetTr = pTarget->GetComponent<Transform>();
        wstring mtkey = L"dmg_" + std::to_wstring(Dmg % 10);
        // �۾��ؾ���
        Numb* units = Instantiate<Numb>(Vector3(10.f,30.f,0.f), eLayerType::DmgBox);
        Transform* unitstr = units->GetComponent<Transform>();
        unitstr->SetParent(TargetTr);
        unitstr->SetTransType(Transform::eTransType::PosAdd);

        units->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey);

        // tens
        // hundreds
    }
    void BattleManager::DamageFontInit()
    {
        Resources::Load<Texture>(L"dmg_0_tex", L"..\\Resources\\useResource\\numb\\dmg_0.png");
        Resources::Load<Texture>(L"dmg_1_tex", L"..\\Resources\\useResource\\numb\\dmg_1.png");
        Resources::Load<Texture>(L"dmg_2_tex", L"..\\Resources\\useResource\\numb\\dmg_2.png");
        Resources::Load<Texture>(L"dmg_3_tex", L"..\\Resources\\useResource\\numb\\dmg_3.png");
        Resources::Load<Texture>(L"dmg_4_tex", L"..\\Resources\\useResource\\numb\\dmg_4.png");
        Resources::Load<Texture>(L"dmg_5_tex", L"..\\Resources\\useResource\\numb\\dmg_5.png");
        Resources::Load<Texture>(L"dmg_6_tex", L"..\\Resources\\useResource\\numb\\dmg_6.png");
        Resources::Load<Texture>(L"dmg_7_tex", L"..\\Resources\\useResource\\numb\\dmg_7.png");
        Resources::Load<Texture>(L"dmg_8_tex", L"..\\Resources\\useResource\\numb\\dmg_8.png");
        Resources::Load<Texture>(L"dmg_9_tex", L"..\\Resources\\useResource\\numb\\dmg_9.png");
        Resources::Load<Texture>(L"heal_0_tex", L"..\\Resources\\useResource\\numb\\heal_0.png");
        Resources::Load<Texture>(L"heal_1_tex", L"..\\Resources\\useResource\\numb\\heal_1.png");
        Resources::Load<Texture>(L"heal_2_tex", L"..\\Resources\\useResource\\numb\\heal_2.png");
        Resources::Load<Texture>(L"heal_3_tex", L"..\\Resources\\useResource\\numb\\heal_3.png");
        Resources::Load<Texture>(L"heal_4_tex", L"..\\Resources\\useResource\\numb\\heal_4.png");
        Resources::Load<Texture>(L"heal_5_tex", L"..\\Resources\\useResource\\numb\\heal_5.png");
        Resources::Load<Texture>(L"heal_6_tex", L"..\\Resources\\useResource\\numb\\heal_6.png");
        Resources::Load<Texture>(L"heal_7_tex", L"..\\Resources\\useResource\\numb\\heal_7.png");
        Resources::Load<Texture>(L"heal_8_tex", L"..\\Resources\\useResource\\numb\\heal_8.png");
        Resources::Load<Texture>(L"heal_9_tex", L"..\\Resources\\useResource\\numb\\heal_9.png");

        LoadMaterial(DMGNUMB_0, L"SpriteShader", L"dmg_0_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_1, L"SpriteShader", L"dmg_1_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_2, L"SpriteShader", L"dmg_2_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_3, L"SpriteShader", L"dmg_3_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_4, L"SpriteShader", L"dmg_4_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_5, L"SpriteShader", L"dmg_5_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_6, L"SpriteShader", L"dmg_6_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_7, L"SpriteShader", L"dmg_7_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_8, L"SpriteShader", L"dmg_8_tex", eRenderingMode::Transparent);
        LoadMaterial(DMGNUMB_9, L"SpriteShader", L"dmg_9_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_0, L"SpriteShader", L"heal_0_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_1, L"SpriteShader", L"heal_1_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_2, L"SpriteShader", L"heal_2_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_3, L"SpriteShader", L"heal_3_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_4, L"SpriteShader", L"heal_4_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_5, L"SpriteShader", L"heal_5_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_6, L"SpriteShader", L"heal_6_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_7, L"SpriteShader", L"heal_7_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_8, L"SpriteShader", L"heal_8_tex", eRenderingMode::Transparent);
        LoadMaterial(HEALNUMB_9, L"SpriteShader", L"heal_9_tex", eRenderingMode::Transparent);
    }
}