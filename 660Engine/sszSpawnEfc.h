#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class SpawnEfc : public GameObject
    {
    public:
        SpawnEfc();
        virtual ~SpawnEfc();

        virtual void Initialize() override;

        bool IsPlay() { return bPlay; }

        void SetLayer();

        void Play(Vector3 vPos);
        void reset() { bPlay = false; }

    private:
        GameObject* mFront;
        GameObject* mBack;

        bool bPlay;
    };
}