#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"
#include "sszTexture.h"

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
        std::shared_ptr<graphics::Texture> mStatIconTex[(UINT)eStatType::END];
	};
}