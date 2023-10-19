#pragma once
#include "sszBattleManager.h"
#include "CommonHeader.h"
#include "sszLog.h"

#include "sszTGM.h"
#include "sszEffect.h"

#include "sszPilot.h"
#include "sszTeam.h"
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
        if (pTarget->IsPaused()) // Paused상태인지 확인, false면 Battle이 정상적으로 이루어지지 않음
            return false;

        if (Damage(pAttacker, pTarget, iDamage)) // 데미지 함수 호출, Target이 사망하면 true를 호출한다.
        {
            // Target은 사망판정
            pTarget->Dead();
            pAttacker->SetTarget_Enemy(nullptr);
            // RegistRespawnPool(pTarget); // 오브젝트 Dead가 아닌 개념상 Dead로 실제는 Pasued 상태로 전환해 Tick이 돌지 않도록한다.
            
            // 통계 기록
            pAttacker->GetTeam()->AddKillScore();
            
            Champ::tChampStatus* AttackerStat = pAttacker->GetChampStatus();
            Champ::tChampStatus* TargetStat = pTarget->GetChampStatus();

            AttackerStat->KILLPOINT += 1;
            TargetStat->DEATHPOINT += 1;
            
            // assist 확인
            for (Champ* friendly : pAttacker->GetFriendly())
            {
                if (friendly->GetTarget_Enemy() == pTarget)
                {
                    friendly->GetChampStatus()->ASSISTPOINT += 1;
                    friendly->SetTarget_Enemy(nullptr);
                }
                else if (friendly->GetTarget_Friendly() == pAttacker)
                {
                    friendly->GetChampStatus()->ASSISTPOINT += 1;
                }
            }

            return false;
        }

        return true;
    }

    bool BattleManager::Heal(Champ* pHealer, Champ* pTarget, unsigned int iHeal)
    {
        if (pTarget->IsPaused()) // Paused상태인지 확인, false면 Battle이 정상적으로 이루어지지 않음
            return false;

        if (Healing(pHealer, pTarget, iHeal))
        {
            Transform* tr = pTarget->GetComponent<Transform>();
            Vector3 vfrontPos = tr->GetPosition();
            Vector3 vbackPos = tr->GetPosition();
            vfrontPos.z -= 0.00001f;
            vbackPos.z += 0.00001f;
            Vector3 vScale(76.f, 78.f, 0.f);

            vfrontPos.y -= 20.f;
            vbackPos.y -= 20.f;

            TGM::GetEffectObj()->Play(vfrontPos, vScale, L"heal_receive_front");
            TGM::GetEffectObj()->Play(vbackPos, vScale, L"heal_receive_back");
        }

        return true;
    }

    bool BattleManager::Healing(Champ* pHealer, Champ* pTarget, unsigned int iheal)
    {
        Champ::tChampStatus* HealerStat = pHealer->GetChampStatus();
        Champ::tChampStatus* TargetStat = pTarget->GetChampStatus();

        UINT healing = iheal;
        if (TargetStat->ChampInfo.MAXHP == TargetStat->HP)
            healing = 0; // 최대 체력 이상이면 힐량은 0 이다.
        
        else if (TargetStat->ChampInfo.MAXHP <= (TargetStat->HP + iheal))
            healing = TargetStat->ChampInfo.MAXHP - TargetStat->HP; 

        TargetStat->HP += healing;

        // 로그용
        std::wstring szbuffer;
        szbuffer = pHealer->GetName() + L" 치유, 힐량 : " + std::to_wstring(healing);
        Log::AddLog(szbuffer);

        // pTarget->GetChampScript()->Damaged(); 힐은 타격 효과가 발생하지 않음.

        // print Damage() 데미지 출력 함수 호출
        // Target의 Transform에 접근해 좌표를 받고 해당 좌표에서 데미지 UI를 출력
        HealPrint(healing, pTarget);

        // 통계 기록
        HealerStat->TotalHeal += healing;

        return true;
    }

    void BattleManager::HealPrint(unsigned int heal, Champ* pTarget)
    {
        int iheal = heal;
        Transform* TargetTr = pTarget->GetComponent<Transform>();
        std::wstring mtkey = L"heal_";

        Vector3 vCenterPos = TargetTr->GetPosition() + Vector3(20.f, 35.f, 0.f);
        vCenterPos.z = 0.1f;

        Numb* hundreds = nullptr;
        Numb* tens = nullptr;
        Numb* units = nullptr;

        float hundwidth = 0.f;
        float tenswidth = 0.f;
        float unitswidth = 0.f;

        // 위에서부터 차례대로
        units = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        units->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iheal % 10));
        Transform* unitstr = units->GetComponent<Transform>();
        unitswidth = unitstr->GetScale().x / 2.f;

        iheal /= 10;

        if (iheal == 0)
        {
            return;
        }

        tens = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        tens->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iheal % 10));
        Transform* tenstr = tens->GetComponent<Transform>();
        tenswidth = tenstr->GetScale().x / 2.f;

        iheal /= 10;

        if (iheal == 0)
        {
            tenstr->AddPosition(-tenswidth, 0.f, 0.f);
            unitstr->AddPosition(unitswidth, 0.f, 0.f);
            return;
        }

        hundreds = Instantiate<Numb>(vCenterPos, eLayerType::DmgBox);
        hundreds->PrintDamageBox(eDmgBoxType::DAMAGE, mtkey + std::to_wstring(iheal / 100));
        Transform* hundtr = hundreds->GetComponent<Transform>();
        hundwidth = hundtr->GetScale().x / 2.f;

        hundtr->AddPosition(-(hundwidth + tenswidth), 0.f, 0.f);
        tenstr->AddPosition(tenswidth, 0.f, 0.f);
        unitstr->AddPosition(tenswidth, 0.f, 0.f);
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

        Transform* SpawnTr = Target->GetComponent<Transform>();
        SpawnTr->GetPosition();
        Vector3 SpawnPoint = SpawnTr->GetPosition();
        SpawnPoint.x = (float)(rand() % 500);
        SpawnPoint.y = (float)(rand() % 400) - 300.f;

        SpawnTr->SetPosition(SpawnPoint);

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
        szbuffer = Target->GetName() + L" 스폰";
        Log::AddLog(szbuffer);
    }

    bool BattleManager::Damage(Champ* pAttacker, Champ* pTarget, unsigned int iDamage)
    {
        Champ::tChampStatus* AttackerStat = pAttacker->GetChampStatus();
        Champ::tChampStatus* TargetStat = pTarget->GetChampStatus();
        int FinalDamage = iDamage - (int)(iDamage * ((float)(TargetStat->ChampInfo.DEF) / 100.f));

        if (FinalDamage <= 0)
            FinalDamage = 1; // 방어력보다 공격력이 같거나 낮을 경우 최소데미지인 1로 고정한다.

        TargetStat->HP -= FinalDamage;

        // 로그용
        std::wstring szbuffer;
        szbuffer = pAttacker->GetName() + L" 공격, 데미지 : " + std::to_wstring(FinalDamage);
        Log::AddLog(szbuffer);

        pTarget->GetChampScript()->Damaged();

        // print Damage() 데미지 출력 함수 호출
        // Target의 Transform에 접근해 좌표를 받고 해당 좌표에서 데미지 UI를 출력
        DamagePrint(FinalDamage, pTarget);

        // 통계 기록
        // IGStatus에 누적공격데미지, 피격데미지, 회복량, 킬수, 사망수, 어시수 입력
        // IGStatus에 Target의 받은 데미지 증가, Attacker의 공격 데미지 증가.
        AttackerStat->TotalDeal += FinalDamage;
        TargetStat->TotalDamaged += FinalDamage;

        if (0 >= TargetStat->HP) // Target의 최종 데미지가 0이하로 떨어질 경우
        {
            

            TargetStat->HP = 0; // 0 으로 고정.
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

        // 위에서부터 차례대로
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