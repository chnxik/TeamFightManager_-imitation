#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class ButtonUI;

    class BanpickClassTap : public UIObject
    {
    public:
        BanpickClassTap(const std::wstring& Key);
        virtual ~BanpickClassTap();

        virtual void Initialize() override;

        ButtonUI* GetBtnComponent() { return mBtnComp; }

    private:
        ButtonUI* mBtnComp;
    };
}