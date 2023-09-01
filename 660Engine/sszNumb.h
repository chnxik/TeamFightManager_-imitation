#pragma once
#include "sszGameObject.h"
#include "sszEnums.h"

namespace ssz
{
    class MeshRenderer;
    class Rigidbody;

    class Numb : public GameObject
    {
    public:
        Numb();
        virtual ~Numb();

        virtual void Update();

        virtual void Initialize();

        void PrintDamageBox(eDmgBoxType type, wstring numbstr);

        // pos�� �θ�class transform addPos�� ����
        // SetPosition�� DmgText���� init�Ҷ� ����
        // ������ enum������ ��µǴ� �̹��� ����
    private:
        MeshRenderer* mMr;
        Rigidbody* mRb;

        float   fLifeTime;
    };
}