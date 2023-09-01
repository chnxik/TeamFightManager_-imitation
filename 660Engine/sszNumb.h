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

        // pos는 부모class transform addPos로 설정
        // SetPosition은 DmgText에서 init할때 결정
        // 정해준 enum값으로 출력되는 이미지 설정
    private:
        MeshRenderer* mMr;
        Rigidbody* mRb;

        float   fLifeTime;
    };
}