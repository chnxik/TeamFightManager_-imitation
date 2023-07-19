#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class StatIcon;
    class BanPickStat : public UIObject
    {
    public:
        enum eStatType
        {
            ATK,
            DEF,
            APD,
            HP,
            RNG,
            SPD,
            END
        };

        BanPickStat(const std::wstring& key);
        virtual ~BanPickStat();

        void SetSlot(eStatType eType);

    private:
        StatIcon* mStatIcon;
    };
}