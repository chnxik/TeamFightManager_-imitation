#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TeamIcon : public UIObject
    {
    public:
        TeamIcon(const std::wstring& key);
        virtual ~TeamIcon();

        virtual void Initialize() override;

        void ChangeLogo(std::wstring Texkey);

    private:
        UIObject* mBackGround;
    };
}