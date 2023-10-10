#pragma once
#include "sszScript.h"

#include "CommonHeader.h"
#include "sszAIBB.h"
#include "sszBT.h"

namespace ssz
{
    class Champ_Script : public Script
    {
    public:
        Champ_Script();
        virtual ~Champ_Script();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Binds() override;

        virtual void BindsClear() override;

        virtual void DamageCBClear();

        virtual void InitChampInfo() = 0;   // 챔프 정보 설정
        virtual void InitChampAnim() = 0;   // 챔프 애니메이션 설정
        virtual void InitColObj() = 0;      // 챔프 콜라이더오브젝트 설정
        virtual void InitAudio() = 0;
        virtual void InitBT() = 0;          // 챔프 AI 설정

        virtual void Attack();
        virtual void AttackComplete();
        virtual void Skill() {};
        virtual void Ultimate() {};

        virtual void ResetAIBB();
        virtual void Dead() = 0;

        virtual void Damaged() { fDamageRatio = 1.f; }
        

    private:
        AI::Root_Node* mRoot;
        float fDamageRatio;

    protected:
        AI::Root_Node* CreateRootNode(std::shared_ptr<AI::AIBB> pAIBB);
        std::shared_ptr<AI::AIBB> InstantiateAIBB();
        AI::Root_Node* GetRootNode();
    };
}