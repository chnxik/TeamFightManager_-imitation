#pragma once
#include "sszGameObject.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class ColObj;
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
            UINT HP = 0; // ü��
            UINT SPD = 0; // �̵��ӵ�
        };

        struct IGStatus // �ΰ��� ����
        {
            UINT ATK = 0;           // ���ݷ�
            float APD = 0.f;        // ���ݼӵ�
            UINT RNG = 0;           // ��Ÿ�
            UINT DEF = 0;           // ����
            UINT MAXHP = 0;         // �ִ� ü��
            UINT SPD = 0;           // �̵��ӵ�

            int HP = 0;             // ���� ü��
            float COOLTIME = 0.f;   // ��ų1 ��Ÿ��
            bool bULTIMATE = false; // �ñر� ��� ����

            // ���� ���� ������
            // ���� �ǰ� ������

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

        // è�Ǿ� ���� ����
        const DefaultInfo& GetChampInfo() { return mDefaultInfo; }
        void SetChampInfo(DefaultInfo src) { mDefaultInfo = src; }
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd);
        
        const IGStatus& GetIGStatus() { return mIGStatus; }
        void SetIGStatus(UINT ATKpt, UINT DEFpt);

        // ColObj ����
        ColObj* CreateColObj(const std::wstring& key);
        Collider2D* FindColObjsCol(const std::wstring& key);

        // �� �� è�Ǿ� ���
        void RegistEnemy(const std::wstring& key, Champ* pChamp);
        Champ* GetEnemy(const std::wstring& key);
        std::map<std::wstring, Champ*> GetEnemys() { return mEnemyTeam; }
        void ClearEnemyTeam() { mEnemyTeam.clear(); }

        // Ÿ�� ����
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