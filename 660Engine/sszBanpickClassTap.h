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

        ButtonUI* GetBtnComponent() { return mBtnComp; }

    private:
        ButtonUI* mBtnComp;
    };
}