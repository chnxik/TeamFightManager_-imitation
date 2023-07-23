#pragma once
#include "sszGameObject.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class Champ : public GameObject
    {
    public:

    private:
        AI::BT* mRootBT;
    };
}