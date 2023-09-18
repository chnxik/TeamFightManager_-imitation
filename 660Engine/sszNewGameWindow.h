#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TypeUI;

    class NewGameWindow :
        public UIObject
    {
    public:
        NewGameWindow(const std::wstring& key);
        virtual ~NewGameWindow();

        virtual void Initialize() override;

        void GameStart();

    private:
        UIObject* mSelectedLogo;
        UIObject* mSelectedHair;

        TypeUI* mTeamNameType;
        TypeUI* mCoachType;
    };
}