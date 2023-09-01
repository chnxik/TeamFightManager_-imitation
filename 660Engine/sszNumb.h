#pragma once
#include "sszGameObject.h"
#include "sszEnums.h"

namespace ssz
{
    class MeshRenderer;

    class Numb : public GameObject
    {
    public:
        Numb();
        virtual ~Numb();

        virtual void Initialize();

        virtual void Update();

        void InsertNumber(eDmgTextType type, UINT numb);

        // pos�� �θ�class transform addPos�� ����
        // SetPosition�� DmgText���� init�Ҷ� ����
        // ������ enum������ ��µǴ� �̹��� ����
    private:
        MeshRenderer* mMr;
        int test;
        float testratio;

        void NumbInit();
    };
}