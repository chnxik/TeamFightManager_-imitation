#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Champ;
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
        
        void RegistGame(Champ* champ); // è�Ǿ� ���

    private:
        Champ* mOwnerChamp;         // ���� è�Ǿ� ������
        Text* mPilotName;           // ���Ϸ� �̸� ��� ������Ʈ
        GameObject* mHPBar;         // ü�� ��
        GameObject* mCoolTimeBar;   // ��ų������
        GameObject* mUseUltIcon;    // �ñر� ������ ������Ʈ

        UINT* mChampHP;             // ü�� ��ġ ������
        float* mSkillCoolTime;      // ��ų�� ������������

    };
}