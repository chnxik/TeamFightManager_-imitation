#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Team;


    class Pilot : public GameObject
    {
    public:
        Pilot();
        virtual ~Pilot();

    private:
        // �Ҽ� �� : Team Class�� ������.
        
        // ĳ���� ��� logo (��ü Animator�� ������)
        std::wstring mPilotName;    // �̸�   : wstring
        UINT iPilotATK; // ���ݷ� : UINT
        UINT iPilotDEF; // ���� : UINt
        // ����� : enum class
        
        // è�� ���õ� : struct (����ü�� ������ : è�Ǿ�Key, ��ġ, ����ġ)
        
        UINT iPilotAge; // ����   : UINT
        UINT iPilotCareer;  // ������� : UINT
        UINT iPilotContractCoast;   // ���� ��� : UINT
        
        // óġ ( ���� )    // IG ������ 
        // ���� ( ���� )
        // ��� óġ ( ��ü ���� )
        // ��� ���� ( ��ü ���� )

        // ����ϰ��ִ� Champ*
    };
}