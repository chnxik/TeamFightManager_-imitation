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
        Team* mTeam;    // 소속 팀 : Team Class로 가진다.
        
        // 캐릭터 헤어 logo (몸체 Animator와 별도로)
        std::wstring mPilotName;    // 이름   : wstring
        UINT iPilotATK; // 공격력 : UINT
        UINT iPilotDEF; // 방어력 : UINt
        
        UINT iPilotAge; // 나이   : UINT
        
        // 아바타 정보
        std::wstring mHairTexKey;
        std::wstring mGlassTexKey;

        // 처치 ( 시즌 )    // IG 종료후 
        // 도움 ( 시즌 )
        // 통산 처치 ( 전체 시즌 )
        // 통산 도움 ( 전체 시즌 )

        // 사용하고있는 Champ*
    };
}