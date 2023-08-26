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
        enum class eActiveType
        {
            IDLE,
            MOVE,
            ATTACK,
            DEAD,
            SKILL,
            ULTIMATE,
            END
        };

        struct tChampInfo // è�Ǿ� �⺻ ����
        {
            eChampType ChampType = eChampType::NONE; // è�Ǿ� Ÿ��
            UINT ATK = 0; // ���ݷ�
            float APD = 0; // ���ݼӵ�
            UINT RNG = 0; // ��Ÿ�
            UINT DEF = 0; // ����
            UINT MAXHP = 0; // ü��
            UINT SPD = 0; // �̵��ӵ�
        };

        struct tChampStatus // �ΰ��� ����
        {
            // è�Ǿ� �⺻ ����.
            tChampInfo ChampInfo;
            
            // [���� ����]
            // ���� ����
            // ���� �̸�
            // ���� Ư��
            // ���� �����
            // ���� �ɷ�ġ
            // ���� �ַ� è�Ǿ� �ɷ�ġ

            // è�Ǿ� ����
            int HP = 0;                     // ���� ü��
            float accTime_Skill = 0.f;      // ���� ��ų ��Ÿ��
            float CoolTime_Skill = 0.f;     // ��ų �ʿ� ��Ÿ��
            float UltimateUseTime = 60.f;    // �ñر� ��� ����
            bool bULTIMATE = false;         // �ñر� ��� ����
            float RespawnTime = 0.f;        // �������ð�

            // ���� ���
            UINT TotalDeal = 0;     // �� ���ط�
            UINT TotalDamaged = 0;  // ���� ���ط�
            UINT TotalHeal = 0;     // ȸ����
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
        virtual bool IsChampDead();

        void Play_Idle();
        void Play_Move();
        void Play_Attack();
        void Play_Dead();
        void Play_Skill();
        void Play_Ultimate();

        void SetChampScript(Champ_Script* script);

        // è�Ǿ� ���� ����
        const tChampInfo& GetChampInfo() { return mChampInfo; } // è�Ǿ� �⺻ ����
        void SetChampInfo(tChampInfo src) { mChampInfo = src; } // è�Ǿ� �⺻ ����
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd); // è�Ǿ� �⺻ ����
        
        tChampStatus* GetChampStatus() { return &mChampStatus; } // ��� ��� è�Ǿ� ����
        void InitChampStatus(UINT ATKpt, UINT DEFpt); // Player Ŭ������ ���ڷ� �޴´�.

        void ResetInfo();
        void RespawnInfo();

        // Pilot ����
        void RegistPilot(Pilot* pPilot) { mPilot = pPilot; }
        const Pilot* GetPilot() { return mPilot; }
        
        // �Ʊ� è�Ǿ� ����
        void RegistFriendly(Champ* pChamp) { mFriendly.emplace_back(pChamp); }
        std::vector<Champ*> GetFriendly() { return mFriendly; }
        void ClearFriendly() { mFriendly.clear(); }

        // �� �� è�Ǿ� ����
        void RegistEnemy(Champ* pChamp) { mEnemys.emplace_back(pChamp); }
        std::vector<Champ*> GetEnemys() { return mEnemys; }
        void ClearEnemys() { mEnemys.clear(); }

        // Ÿ�� ����
        void SetTarget_Enemy(Champ* pTarget) { mTargetEnemy = pTarget; }
        Champ* GetTarget_Enemy() { return mTargetEnemy; }
        void SetTarget_Friendly(Champ* pTarget) { mTargetFriendly = pTarget; }
        Champ* GetTarget_Friendly() { return mTargetFriendly; }

        void ATTACK();
        
        // ColObj ����
        ColObj* CreateColObj(eColObjType Type);
        void ColObjSetLayer(eColObjType Type);
        Collider2D* GetColObjsCol(eColObjType Type);

        virtual void SetState(eState state);

        // Animation Key
        void SetAnimKey(eActiveType eType, const std::wstring& key) { vecAnimKey[(UINT)eType] = key; }
        const std::wstring& GetAnimKey(eActiveType eType) { return vecAnimKey[(UINT)eType]; }

    private:
        tChampInfo      mChampInfo;       // è�Ǿ� �⺻ ����
        tChampStatus    mChampStatus;            // è�Ǿ� ��� ����

        Pilot*      mPilot;// ���Ϸ� ������

        std::vector<Champ*> mEnemys;    // �� è�Ǿ� ����Ʈ
        std::vector<Champ*> mFriendly;  // �Ʊ� è�Ǿ� ����Ʈ
        
        Champ* mTargetEnemy;            // ���� Ÿ��
        Champ* mTargetFriendly;         // �Ʊ� Ÿ��

        ColObj* mColObjs[(UINT)eColObjType::END];    // ����,��ų ������ �ݶ��̴� ������Ʈ
        Champ_Script* mChampScript;

        std::wstring vecAnimKey[(UINT)eActiveType::END];
    };
}