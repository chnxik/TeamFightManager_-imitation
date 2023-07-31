#pragma once
#include "sszGameObject.h"
// Type
// 1. è������ �پ��ִ� �ٰŸ� ����Ÿ��
// 2. �߻�Ǵ� ����ü Ÿ��
// 3. ��ġ�ϴ� ��ġ Ÿ��
// ��ġ�� ��ü���� ������.


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
        Champ* mOwner;                  // �θ� ��ü
        std::vector<Champ*> mTargets;   // Ÿ�� ��ü
    };
}