#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"

namespace ssz
{
    class BanLine : public UIObject
    {
    public:
        BanLine(const std::wstring& key);
        virtual ~BanLine();

        virtual void Initialize() override;

        virtual void Update() override;
        virtual void LateUpdate() override;

        void ChangeTurn(eTeamColor TeamColor);

    private:
        eTeamColor mCurTeamColor;
        UIObject* mArrowMark;
        Text* mPhaseCenterStr;
        Text* mPhaseSideStr;

        
    };
}