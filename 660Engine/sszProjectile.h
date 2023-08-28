#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Champ;
    class ProjScript;

    class Projectile :
        public GameObject
    {
    public:
        Projectile();
        virtual ~Projectile();

        virtual void Initialize();

        bool IsProjCanUse() { return bCanUse; }

        void Shoot(Champ* Src, Champ* Dest, Vector3 ProjScale, const std::wstring& Materialkey, UINT Dmg); // �߻� �Լ�

    private:
        bool bCanUse;

        friend class ProjScript;
    };
}