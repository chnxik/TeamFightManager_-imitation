#pragma once

namespace ssz
{
    enum class eSlotState
    {
        Idle,
        Selected,
        End
    };

    enum class eTeamColor
    {
        Red,
        Blue,
        End,
    };

    enum class eCampType
    {
        Player,
        Enemy,
        End,
    };

    enum class eStatType
    {
        ATK,
        DEF,
        APD,
        HP,
        RNG,
        SPD,
        END
    };

    enum class eChamp
    {
        Archer,
        Knight
    };

    enum class eChampType
    {
        FIGHTER,    // 전사
        MARKSMAN,   // 원거리 딜러
        MAGE,       // 마법사
        CONTROLLER, // 서포터
        SLAYER,     // 암살자
        NONE,
    };

    enum class eColObjType
    {
        RANGE,
        SKILL,
        ULTIMATE,
        END
    };

    enum class eDmgTextType
    {
        DAMAGE,
        HEAL,
        END,
    };
}