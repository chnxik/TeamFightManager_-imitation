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
        FIGHTER,    // ����
        MARKSMAN,   // ���Ÿ� ����
        MAGE,       // ������
        CONTROLLER, // ������
        SLAYER,     // �ϻ���
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