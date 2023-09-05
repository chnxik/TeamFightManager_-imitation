#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class KBDIcon : public UIObject
    {
    public:
        enum KEYICON
        {
            A, C, D, E, F, Q, R, S, V, Z, END
        };
    public:
        KBDIcon(const std::wstring& key);
        virtual ~KBDIcon();

        virtual void Initialize() override;

        void SetIcon(KEYICON key);

    private:
        KEYICON mKey;
    };
}