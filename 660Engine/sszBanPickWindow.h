#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"

namespace ssz
{
    class BanPickStat;
    class BanLine;

    class BanPickWindow : public UIObject
    {
    public:
        BanPickWindow(const std::wstring& key);
        virtual ~BanPickWindow();

        virtual void Initialize() override;

        void Done();

    private:
        BanLine* mBanLine;
        BanPickStat* mBanPickStat[(UINT)eStatType::END];
    };
}