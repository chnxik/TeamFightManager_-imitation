#pragma once
#include "sszUIObject.h"
#include "CommonObjHeader.h"

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

    private:
        StatIcon* mStatIcon;
    };
}