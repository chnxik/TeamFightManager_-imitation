#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TypeUI;
    class TeamIconSlot;
    class AvatarSlot;
    class ImportantBtn;
    class DefaultBtn;


    class NewGameWindow :
        public UIObject
    {
    public:
        NewGameWindow(const std::wstring& key);
        virtual ~NewGameWindow();

        virtual void Initialize() override;
        virtual void Update() override;

        void GameStart();

    private:
        UIObject* mSelectedLogo;
        UIObject* mSelectedHair;

        TeamIconSlot* mTeamIconSlot;
        AvatarSlot* mAvatarSlot;

        TypeUI* mTeamNameType;
        TypeUI* mCoachType;

        ImportantBtn* NewGameStartBtn;
        DefaultBtn* NewGameUICloseBtn;
    };
}