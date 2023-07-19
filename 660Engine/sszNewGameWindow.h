#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class NewGameWindow :
        public UIObject
    {
    public:
        NewGameWindow(const std::wstring& key);
        virtual ~NewGameWindow();

    private:
    };
}