#pragma once
#include "sszGameObject.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class ColObj;
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
            UINT HP = 0; // 체력
            UINT SPD = 0; // 이동속도
        };

        struct IGStatus // 인게임 정보
        {
            UINT ATK = 0;           // 공격력
            float APD = 0.f;        // 공격속도
            UINT RNG = 0;           // 사거리
            UINT DEF = 0;           // 방어력
            UINT MAXHP = 0;         // 최대 체력
            UINT SPD = 0;           // 이동속도

            int HP = 0;             // 현재 체력
            float COOLTIME = 0.f;   // 스킬1 쿨타임
            bool bULTIMATE = false; // 궁극기 사용 여부

            // 누적 공격 데미지
            // 누적 피격 데미지

        };

        Champ();
        virtual ~Champ();

        virtual void Initialize() {};
        virtual void Update() {};
        virtual void LateUpdate() {};
        virtual void Render() {};

        virtual void Dead();

        virtual void Play_Idle() {};
        virtual void Play_Move() {};
        virtual void Play_Attack() {};
        virtual void Play_Dead() {};
        virtual void Play_Skill1() {};
        virtual void Play_Skill2() {};

        // 챔피언 정보 관리
        const DefaultInfo& GetChampInfo() { return mDefaultInfo; }
        void SetChampInfo(DefaultInfo src) { mDefaultInfo = src; }
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd);
        
        const IGStatus& GetIGStatus() { return mIGStatus; }
        void SetIGStatus(UINT ATKpt, UINT DEFpt);

        // ColObj 관리
        ColObj* CreateColObj(const std::wstring& key);
        Collider2D* FindColObjsCol(const std::wstring& key);

        // 적 팀 챔피언 등록
        void RegistEnemy(const std::wstring& key, Champ* pChamp);
        Champ* GetEnemy(const std::wstring& key);
        std::map<std::wstring, Champ*> GetEnemys() { return mEnemyTeam; }
        void ClearEnemyTeam() { mEnemyTeam.clear(); }

        // 타겟 지정
        void SetTargetEnemy(Champ* pTarget) { mTargetEnemy = pTarget; }
        Champ* GetTargetEnemy() { return mTargetEnemy; }

    private:
        DefaultInfo mDefaultInfo;
        IGStatus    mIGStatus;

        std::map<std::wstring, Champ*> mEnemyTeam;
        Champ* mTargetEnemy;

        std::map<std::wstring, ColObj*>mColObjs;
    };
}