#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class StatIcon : public UIObject
	{
    public:
        enum eStatType
        {
            ATK,
            DEF,
            APD,
            HP,
            RNG,
            SPD,
            END
        };
        StatIcon(const std::wstring& key);
        virtual ~StatIcon();

        void SetIcon(eStatType eType);

    private:
        std::shared_ptr<Texture> mStatIconTex[eStatType::END];
	};
}