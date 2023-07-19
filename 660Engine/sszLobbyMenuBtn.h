#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class ButtonUI;

    class LobbyMenuBtn :
        public UIObject
    {
    public:
        LobbyMenuBtn(const std::wstring& Key);
        virtual ~LobbyMenuBtn();

        ButtonUI* GetBtnComponent() { return mBtnComp; }

    private:
        ButtonUI* mBtnComp;
    };
}