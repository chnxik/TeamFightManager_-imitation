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
        void RegistGame(Pilot* Pilot); // è�Ǿ� ���

    private:
        Champ* mOwnerChamp;         // ���� è�Ǿ� ������
        Text* mPilotName;           // ���Ϸ� �̸� ��� ������Ʈ
        
        GameObject* mGuageBg;       // ������ ���
        GameObject* mHPBar;         // ü�� ��
        GameObject* mCoolTimeBar;   // ��ų������
        GameObject* mUseUltIcon;    // �ñر� ������ ������Ʈ

        bool* bUseUlt;


    };
}