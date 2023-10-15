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

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void SetPilotName(std::wstring PilotName);
        void SetPilotData(UINT ATK, UINT DEF, UINT AGE);
        void RegistTeam(Team* _Team);

        std::wstring GetTeamName();
        std::wstring GetPilotName() { return mPilotName; }
        UINT GetPilotATK() { return iPilotATK; }
        UINT GetPilotDEF() { return iPilotDEF; }
        UINT GetPilotAge() { return iPilotAge; }
    
    private:
        Team* mTeam;    // �Ҽ� �� : Team Class�� ������.
        
        // ĳ���� ��� logo (��ü Animator�� ������)
        std::wstring mPilotName;    // �̸�   : wstring
        UINT iPilotATK; // ���ݷ� : UINT
        UINT iPilotDEF; // ���� : UINt
        
        UINT iPilotAge; // ����   : UINT
        
        // �ƹ�Ÿ ����
        std::wstring mHairTexKey;
        std::wstring mGlassTexKey;

        // óġ ( ���� )    // IG ������ 
        // ���� ( ���� )
        // ��� óġ ( ��ü ���� )
        // ��� ���� ( ��ü ���� )

        // ����ϰ��ִ� Champ*
    };
}