#pragma once
#include "sszChamp.h"

namespace ssz
{
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

        virtual void Attack();
        virtual void Dead();

    private:

    };

}