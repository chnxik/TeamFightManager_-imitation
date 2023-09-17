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

        void InitCheckSelected(UIObject** object);
        void InitTeamLogo(wstring Texkey, UINT idx, Vector3 Pos, UIObject* parent);

    private:
        UIObject*   mTeamIcon;
        bool        bSelected;
    };
}