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

        virtual void Initialize() override;

        ButtonUI* GetBtnComponent() { return mBtnComp; }
        void InitBtnIcon(std::wstring Texkey, std::wstring MenuName);

    private:
        ButtonUI* mBtnComp;
        UIObject* mBtnIcon;
    };
}