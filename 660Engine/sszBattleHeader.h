#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class BattleHeader : public UIObject
    {
    public:
        BattleHeader(const std::wstring& key);
        virtual ~BattleHeader();

        virtual void Initialize() override;
        virtual void Update() override;

    private:
    };
}