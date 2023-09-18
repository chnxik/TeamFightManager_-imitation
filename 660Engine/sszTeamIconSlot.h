#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TeamIconSlot :
        public UIObject
    {
    public:
        TeamIconSlot(const std::wstring& key);
        virtual ~TeamIconSlot();

        virtual void Initialize() override;

        void ChangeIcon(std::wstring Texkey);
        void ChangeIcon(std::shared_ptr<Texture> Texture);

    private:
        UIObject* mTeamIcon;
    };
}