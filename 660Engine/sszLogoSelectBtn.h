#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TeamIcon;

    class LogoSelectBtn :
        public UIObject
    {
    public:
        LogoSelectBtn(const std::wstring& key);
        virtual ~LogoSelectBtn();

        virtual void Initialize() override;

        void InitCheckSelected(UIObject** object);
        void InitTeamLogo(wstring Texkey, UINT idx, Vector3 Pos, UIObject* parent, TeamIcon* Delegate);

        const std::wstring& GetTexkey() { return mTexkey; }

    private:
        UIObject*   mTeamIcon;
        bool        bSelected;

        wstring mTexkey;
    };
}