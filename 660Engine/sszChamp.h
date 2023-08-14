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
        struct DefaultInfo // è�Ǿ� �⺻ ����
        {
            eChampType ChampType = eChampType::NONE; // è�Ǿ� Ÿ��
            UINT ATK = 0; // ���ݷ�
            float APD = 0; // ���ݼӵ�
            UINT RNG = 0; // ��Ÿ�
            UINT DEF = 0; // ����
            UINT MAXHP = 0; // ü��
            UINT SPD = 0; // �̵��ӵ�
        };

        struct IGStatus // �ΰ��� ����
        {
            // è�Ǿ� �⺻ ����.
            DefaultInfo ChampInfo;
            
            // [���� ����]
            // ���� ����
            // ���� �̸�
            // ���� Ư��
            // ���� �����
            // ���� �ɷ�ġ
            // ���� �ַ� è�Ǿ� �ɷ�ġ

            // è�Ǿ� ����
            int HP = 0;             // ���� ü��
            float COOLTIME = 0.f;   // ��ų1 ��Ÿ��
            bool bULTIMATE = false; // �ñر� ��� ����

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

        virtual void Play_Idle();
        virtual void Play_Move();
        virtual void Play_Attack();
        virtual void Play_Dead();
        virtual void Play_Skill1();
        virtual void Play_Skill2();

        void SetChampScript(Champ_Script* script);

        // è�Ǿ� ���� ����
        const DefaultInfo& GetChampInfo() { return mDefaultInfo; } // è�Ǿ� �⺻ ����
        void SetChampInfo(DefaultInfo src) { mDefaultInfo = src; } // è�Ǿ� �⺻ ����
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd); // è�Ǿ� �⺻ ����
        
        IGStatus* GetIGStatus() { return &mIGInfo; } // ��� ��� è�Ǿ� ����
        void InitIGInfo(UINT ATKpt, UINT DEFpt); // Player Ŭ������ ���ڷ� �޴´�.

        void ResetInfo();

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
        void SetTargetEnemy(Champ* pTarget) { mTargetEnemy = pTarget; }
        Champ* GetTargetEnemy() { return mTargetEnemy; }
        
        // ColObj ����
        ColObj* CreateColObj(eColObjType Type);
        void ColObjSetLayer(eColObjType Type);
        Collider2D* GetColObjsCol(eColObjType Type);

    private:
        DefaultInfo mDefaultInfo;       // è�Ǿ� �⺻ ����
        IGStatus    mIGInfo;            // è�Ǿ� ��� ����

        Pilot*      mPilot;// ���Ϸ� ������

        std::vector<Champ*> mFriendly;  // �Ʊ� è�Ǿ� ����Ʈ
        std::vector<Champ*> mEnemys;    // �� è�Ǿ� ����Ʈ
        
        Champ* mTargetEnemy;            // ���� Ÿ��

        ColObj* mColObjs[(UINT)eColObjType::END];    // ����,��ų ������ �ݶ��̴� ������Ʈ
        Champ_Script* mChampScript;
    };
}