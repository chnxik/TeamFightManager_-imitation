#pragma once
#include "sszBattleManager.h"
#include "sszChamp.h"

namespace ssz
{
    bool BattleManager::Battle(Champ* pAttacker, Champ* pTarget, UINT iDamage)
    {
        if (pTarget->IsPaused()) // Paused상태인지 확인, false면 Battle이 정상적으로 이루어지지 않음
            return false;

        if (Damage(pAttacker, pTarget, iDamage)) // 데미지 함수 호출, Target이 사망하면 true를 호출한다.
        {
            // Target은 사망판정
            // pTarget->SetDead(); 오브젝트 Dead가 아닌 개념상 Dead로 실제는 Pasued 상태로 전환해 Tick이 돌지 않도록한다.
            // respawn Pool에 TargetPtr을 집어넣는다.
            
            // 통계 기록
            // Attacker의 Kill 수 증가
            // Target의 Dead수 증가
            
            // assist 확인
            // Attacker Team의 OtherChamp의 타겟 확인. pTarget과 같으면 OtherChamp의 Assist 증가
            // OtherChamp의 Target nullptr.

        }

        return true;
    }

    bool BattleManager::Damage(Champ* pAttacker, Champ* pTarget, UINT iDamage)
    {
        Champ::IGStatus* TargetStat = pTarget->GetIGStatus();
        UINT FinalDamage = iDamage - TargetStat->ChampInfo.DEF;
        
        if (FinalDamage <= 0)
            FinalDamage = 1; // 방어력보다 공격력이 같거나 낮을 경우 최소데미지인 1로 고정한다.

        TargetStat->HP -= FinalDamage;

        // print Damage() 데미지 출력 함수 호출
        // Target의 Transform에 접근해 좌표를 받고 해당 좌표에서 데미지 UI를 출력

        // 통계 기록
        // IGStatus에 누적공격데미지, 피격데미지, 회복량, 킬수, 사망수, 어시수 입력
        // IGStatus에 Target의 받은 데미지 증가, Attacker의 공격 데미지 증가.

        if (0 <= TargetStat->HP) // Target의 최종 데미지가 0이하로 떨어질 경우
        {
            TargetStat->HP = 0; // 0 으로 고정.
            return true;
        }
        
        return false;
    }
}