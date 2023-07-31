#pragma once
#include "sszChamp.h"

namespace ssz
{
    class ColObj; // 공격 에어리어

    class Champ_Archer : public Champ
    {
    public:
        Champ_Archer();
        virtual ~Champ_Archer();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void SetAnimator();

        virtual void Play_Idle();
        virtual void Play_Move();
        virtual void Play_Attack();
        virtual void Play_Dead();
        virtual void Play_Skill1();

    private:
        ColObj* mATKArea;
    };

}