#pragma once
#include "sszGameObject.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class Champ : public GameObject
    {
    public:
        struct StatusInfo
        {
            eChampType ChampType = eChampType::NONE; // è�Ǿ� Ÿ��
            UINT ATK = 0; // ���ݷ�
            float APD = 0; // ���ݼӵ�
            UINT RNG = 0; // ��Ÿ�
            UINT DEF = 0; // ����
            UINT HP = 0; // ü��
            UINT SPD = 0; // �̵��ӵ�
        };

        Champ();
        virtual ~Champ();

        virtual void Initialize() {};
        virtual void Update() {};
        virtual void LateUpdate() {};
        virtual void Render() {};

        virtual void Play_Idle() {};
        virtual void Play_Move() {};
        virtual void Play_Attack() {};
        virtual void Play_Dead() {};
        virtual void Play_Skill1() {};
        virtual void Play_Skill2() {};

        const StatusInfo& GetChampInfo() { return mChampInfo; }
        void SetChampInfo(StatusInfo src) { mChampInfo = src; }
        void SetChampInfo(eChampType Type, UINT atk, float apd, UINT rng, UINT def, UINT hp, UINT spd);

        virtual void RegistEnemy(const std::wstring& key, Champ* pChamp);
        virtual Champ* GetEnemy(const std::wstring& key);
        virtual std::map<std::wstring, Champ*> GetEnemys() { return mEnemyTeam; }
        virtual void ClearEnemyTeam() { mEnemyTeam.clear(); }

    private:
        StatusInfo mChampInfo;
        std::map<std::wstring, Champ*> mEnemyTeam;
    };
}