#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class Team;
    class TeamIconSlot;
    class League;

    class BattleHeader : public UIObject
    {
    public:
        enum class eHeaderTextType
        {
            RoundTitle,
            GameTime,
        };
        
        BattleHeader(const std::wstring& key);
        virtual ~BattleHeader();

        virtual void Initialize() override;
        virtual void Update() override;

        void RegistTeam();
        void SetTimeType();
        void SetTitleType();

    private:
        eHeaderTextType mHeaderTextType;

        League* mLeagueManager;

        Text* mHeaderText;

        TeamIconSlot* BlueTeam;
        TeamIconSlot* RedTeam;

        Text* BlueTeamName;
        Text* RedTeamName;

        Text* BlueTemaScore;
        Text* RedTeamScore;
        const UINT* BlueTKScoreValue;
        const UINT* RedTKScoreValue;

        UIObject* BlueRoundIcon;
        UIObject* RedRoundIcon;
    };
}