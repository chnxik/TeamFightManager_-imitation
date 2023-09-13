#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class LogoSelectBtn :
        public UIObject
    {
    public:
        LogoSelectBtn(const std::wstring& key);
        virtual ~LogoSelectBtn();

        virtual void Initialize() override;
        virtual void MouseLbtnClicked() override;

    private:
        GameObject* mTeamIcon;
        bool        bSelected;
    };
}