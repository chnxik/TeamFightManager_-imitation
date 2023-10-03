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

        virtual void CreatePilot(std::wstring Name, UINT ATK, UINT DEF, UINT AGE);

    private:
        // 소속 팀 : Team Class로 가진다.
        
        // 캐릭터 헤어 logo (몸체 Animator와 별도로)
        std::wstring mPilotName;    // 이름   : wstring
        UINT iPilotATK; // 공격력 : UINT
        UINT iPilotDEF; // 방어력 : UINt
        // 컨디션 : enum class
        
        // 챔프 숙련도 : struct (구조체로 가진다 : 챔피언Key, 수치, 경험치)
        
        UINT iPilotAge; // 나이   : UINT
        
        // 처치 ( 시즌 )    // IG 종료후 
        // 도움 ( 시즌 )
        // 통산 처치 ( 전체 시즌 )
        // 통산 도움 ( 전체 시즌 )

        // 사용하고있는 Champ*
    };
}