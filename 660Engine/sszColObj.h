#pragma once
#include "sszGameObject.h"
// Type
// 1. 챔프에게 붙어있는 근거리 공격타입
// 2. 발사되는 투사체 타입
// 3. 설치하는 설치 타입
// 위치는 객체마다 구사함.


namespace ssz
{
    class Champ;
    class ColObj : public GameObject
    {
    public:
        void AddTarget(Champ* pTarget) { mTargets.emplace_back(pTarget); }
        void SetOwner(Champ* pOwner) { mOwner = pOwner; }

        Champ* GetOwner() { return mOwner; }
        std::vector<Champ*>& GetTargets() { return mTargets; }

    private:
        Champ* mOwner;                  // 부모 객체
        std::vector<Champ*> mTargets;   // 타겟 객체
    };
}