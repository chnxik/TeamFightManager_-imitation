#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Cursor : public GameObject
    {
    public:
        Cursor();
        virtual ~Cursor();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:

    };
}