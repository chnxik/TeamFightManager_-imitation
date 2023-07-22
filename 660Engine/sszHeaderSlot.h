#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class HeaderSlot :
        public UIObject
    {
    public:
        HeaderSlot(const std::wstring& key);
        virtual ~HeaderSlot();

        virtual void Initialize() override;

    private:

    };
}