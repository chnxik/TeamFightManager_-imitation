#pragma once
#include "sszUIObject.h"
#include "CommonHeader.h"

namespace ssz
{
    class StatIcon;
    class BanPickStat : public UIObject
    {
    public:
        BanPickStat(const std::wstring& key);
        virtual ~BanPickStat();

        virtual void Initialize() override;

        void SetSlot(eStatType eType);
        void SetValue(UINT value);
        void SetValue(float value);

    private:
        StatIcon* mStatIcon;
        Text* mSlotName;
        Text* mStatValue;
    };
}