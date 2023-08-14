#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class ColObj;
    class Pilot;
    class Champ_Script;
    
    class Champ : public GameObject
    {
    public:
        struct DefaultInfo // 챔피언 기본 정보
        {
            eChampType ChampType = eChampType::NONE; // 챔피언 타입
            UINT ATK = 0; // 공격력
            float APD = 0; // 공격속도
            UINT RNG = 0; // 사거리
            UINT DEF = 0; // 방어력
            UINT MAXHP = 0; // 체력
            UINT SPD = 0; // 이동속도
        };

        struct IGStatus // 인게임 정보
        {
            // 챔피언 기본 정보.
            DefaultInfo ChampInfo;
            
            // [게임 정보]
            // 선수 정보
            // 선수 이름
            // 선수 특성
            // 선수 컨디션
            // 선수 능력치
            // 선수 주력 챔피언 능력치

            // 챔피언 정보
            int HP = 0;             // 현재 체력
            float COOLTIME = 0.f;   // 스킬1 쿨타임
            bool bULTIMATE = false; // 궁극기 사용 여부

            // 게임 통계
            UINT TotalDeal = 0;     // 준 피해량
            UINT TotalDamaged = 0;  // 받은 피해량
            UINT TotalHeal = 0;     // 회복량
            UINT KILLPOINT = 0;     // Kill
            UINT DEATHPOINT = 0;    // Death
            UINT ASSISTPOINT = 0;   // Assist
        };

        Champ();
        virtual ~Champ();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void Dead();

        virtual void Play_Idle();
        virtual void Play_Move();
        virtual void Play_Attack();
        virtual void Play_Dead();
        virtual void Play_Skill1();
        virtual void Play_Skill2();

        void SetChampScript(Champ_Script* script);

        // 챔피언 정보 관리
        const DefaultInfo& GetChampInfo() { return mDefaultInfo; } // 챔피언 기본 정보
        void SetChampInfo(DefaultInfo src) { mDefaultInfo = src; } // 챔피언 기본 정보
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd); // 챔피언 기본 정보
        
        IGStatus* GetIGStatus() { return &mIGInfo; } // 경기 사용 챔피언 정보
        void InitIGInfo(UINT ATKpt, UINT DEFpt); // Player 클래스를 인자로 받는다.

        void ResetInfo();

        // Pilot 정보
        void RegistPilot(Pilot* pPilot) { mPilot = pPilot; }
        const Pilot* GetPilot() { return mPilot; }
        
        // 아군 챔피언 관리
        void RegistFriendly(Champ* pChamp) { mFriendly.emplace_back(pChamp); }
        std::vector<Champ*> GetFriendly() { return mFriendly; }
        void ClearFriendly() { mFriendly.clear(); }

        // 적 팀 챔피언 관리
        void RegistEnemy(Champ* pChamp) { mEnemys.emplace_back(pChamp); }
        std::vector<Champ*> GetEnemys() { return mEnemys; }
        void ClearEnemys() { mEnemys.clear(); }

        // 타겟 지정
        void SetTargetEnemy(Champ* pTarget) { mTargetEnemy = pTarget; }
        Champ* GetTargetEnemy() { return mTargetEnemy; }
        
        // ColObj 관리
        ColObj* CreateColObj(eColObjType Type);
        void ColObjSetLayer(eColObjType Type);
        Collider2D* GetColObjsCol(eColObjType Type);

    private:
        DefaultInfo mDefaultInfo;       // 챔피언 기본 정보
        IGStatus    mIGInfo;            // 챔피언 경기 정보

        Pilot*      mPilot;// 파일럿 포인터

        std::vector<Champ*> mFriendly;  // 아군 챔피언 리스트
        std::vector<Champ*> mEnemys;    // 적 챔피언 리스트
        
        Champ* mTargetEnemy;            // 공격 타겟

        ColObj* mColObjs[(UINT)eColObjType::END];    // 공격,스킬 판정용 콜라이더 오브젝트
        Champ_Script* mChampScript;
    };
}