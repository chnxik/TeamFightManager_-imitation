#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Effect :public GameObject
    {
    public:
        Effect();
        virtual ~Effect();

        virtual void Initialize() override;

        void SkillInit();

        bool IsPlay() { return bPlay; }

        void Play(Vector3 vPos, Vector3 Scale, const std::wstring& animkey);
        void reset() { bPlay = false; }
        void Complete();

    private:
        bool bPlay;
        int iefcNumb;
    };
}