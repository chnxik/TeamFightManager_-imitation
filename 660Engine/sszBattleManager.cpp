#pragma once
#include "sszBattleManager.h"
#include "CommonHeader.h"
#include "sszLog.h"

#include "sszChamp.h"

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
        int iDamage = Dmg;
        Transform* TargetTr = pTarget->GetComponent<Transform>();
        std::wstring mtkey = L"dmg_";

        Vector3 vCenterPos = TargetTr->GetPosition() + Vector3(20.f, 35.f, 0.f);
        vCenterPos.z = 0.1f;
        
        Numb* hundreds = nullptr;
        Numb* tens = nullptr;
        Numb* units = nullptr;

        float hundwidth = 0.f;
        float tenswidth = 0.f;
        float unitswidth = 0.f;

        // ���������� ���ʴ��
        units = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        units->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iDamage % 10));
        Transform* unitstr = units->GetComponent<Transform>();
        unitswidth = unitstr->GetScale().x / 2.f;

        iDamage /= 10;

        if (iDamage == 0)
        {
            return;
        }

        tens = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        tens->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iDamage % 10));
        Transform* tenstr = tens->GetComponent<Transform>();
        tenswidth = tenstr->GetScale().x / 2.f;

        iDamage /= 10;

        if (iDamage == 0)
        {
            tenstr->AddPosition(-tenswidth, 0.f, 0.f);
            unitstr->AddPosition(unitswidth, 0.f, 0.f);
            return;
        }

        hundreds = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        hundreds->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iDamage / 100));
        Transform* hundtr = hundreds->GetComponent<Transform>();
        hundwidth = hundtr->GetScale().x / 2.f;

        hundtr->AddPosition(-(hundwidth + tenswidth), 0.f, 0.f);
        tenstr->AddPosition(tenswidth, 0.f, 0.f);
        unitstr->AddPosition(tenswidth, 0.f, 0.f);
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

        LoadMaterial(L"dmg_0", L"SpriteShader", L"dmg_0_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_1", L"SpriteShader", L"dmg_1_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_2", L"SpriteShader", L"dmg_2_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_3", L"SpriteShader", L"dmg_3_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_4", L"SpriteShader", L"dmg_4_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_5", L"SpriteShader", L"dmg_5_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_6", L"SpriteShader", L"dmg_6_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_7", L"SpriteShader", L"dmg_7_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_8", L"SpriteShader", L"dmg_8_tex", eRenderingMode::Transparent);
        LoadMaterial(L"dmg_9", L"SpriteShader", L"dmg_9_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_0", L"SpriteShader", L"heal_0_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_1", L"SpriteShader", L"heal_1_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_2", L"SpriteShader", L"heal_2_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_3", L"SpriteShader", L"heal_3_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_4", L"SpriteShader", L"heal_4_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_5", L"SpriteShader", L"heal_5_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_6", L"SpriteShader", L"heal_6_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_7", L"SpriteShader", L"heal_7_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_8", L"SpriteShader", L"heal_8_tex", eRenderingMode::Transparent);
        LoadMaterial(L"heal_9", L"SpriteShader", L"heal_9_tex", eRenderingMode::Transparent);
    }
}