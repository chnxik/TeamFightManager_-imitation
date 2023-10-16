#pragma once

namespace ssz
{
    enum class eSlotState
    {
        Idle,
        Togle,
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
        Knight,
        Fighter,
        Monk,
        SwordMan,
        Pyromancer,
        Priest,
        Ninja,
        NONE
    };

    enum class eChampType
    {
        eFIGHTER,    // 전사
        eMARKSMAN,   // 원거리 딜러
        eMAGE,       // 마법사
        eCONTROLLER, // 서포터
        eSLAYER,     // 암살자
        NONE,
    };

    enum class eColObjType
    {
        RANGE,
        SKILL,
        ULTIMATE,
        END
    };

    enum class eDmgBoxType
    {
        DAMAGE,
        HEAL,
        END,
    };
}