#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class TestEditBox : public GameObject
    {
    public:
        TestEditBox();
        virtual ~TestEditBox();

        virtual void Initialize();
        virtual void Update();

    private:

    };
}