#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class UI : public GameObject 
    {
    public:
        UI();
        virtual ~UI();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:

    };
}