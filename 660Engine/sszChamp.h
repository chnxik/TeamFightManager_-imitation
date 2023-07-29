#pragma once
#include "sszGameObject.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class Champ : public GameObject
    {
    public:
        struct StatusInfo
        {
            eChampType ChampType = eChampType::NONE; // 챔피언 타입
            UINT ATK = 0; // 공격력
            float APD = 0; // 공격속도
            UINT RNG = 0; // 사거리
            UINT DEF = 0; // 방어력
            UINT HP  = 0; // 체력
            UINT SPD = 0; // 이동속도
        };

        Champ();
        virtual ~Champ();

        virtual void Initialize() {};
        virtual void Update() {};
        virtual void LateUpdate() {};
        virtual void Render() {};

        const StatusInfo& GetChampInfo() { return mChampInfo; }
        void SetChampInfo(StatusInfo src) { mChampInfo = src; }
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd);
    private:
        StatusInfo mChampInfo;
    };
}