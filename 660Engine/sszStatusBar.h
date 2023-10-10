#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Champ;
    class Pilot;
    class Text;

    class StatusBar :
        public GameObject
    {
    public:
        StatusBar();
        virtual ~StatusBar();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
        
        void RegistChamp(Champ* champ);
        void RegistGame(Pilot* Pilot); // 챔피언 등록

    private:
        Champ* mOwnerChamp;         // 장착 챔피언 포인터
        Text* mPilotName;           // 파일럿 이름 출력 오브젝트
        
        GameObject* mGuageBg;       // 게이지 배경
        GameObject* mHPBar;         // 체력 바
        GameObject* mCoolTimeBar;   // 스킬게이지
        GameObject* mUseUltIcon;    // 궁극기 아이콘 오브젝트

        bool* bUseUlt;


    };
}