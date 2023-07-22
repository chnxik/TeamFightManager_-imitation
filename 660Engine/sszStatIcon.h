#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class StatIcon : public UIObject
	{
    public:
        
        StatIcon(const std::wstring& key);
        virtual ~StatIcon();

        virtual void Initialize() override;

        void SetIcon(eStatType eType);

    private:
        std::shared_ptr<Texture> mStatIconTex[(UINT)eStatType::END];
	};
}