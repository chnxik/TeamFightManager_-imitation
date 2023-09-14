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

        virtual void Initialize() override;

    private:
        UIObject* mSelectedLogo;
    };
}