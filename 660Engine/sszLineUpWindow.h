#pragma once
#include "sszUIObject.h"
#include "sszLineUpTeamTitle.h"

namespace ssz
{
    class LineUpWindow : public UIObject
    {
    public:
        LineUpWindow(const std::wstring& key);
        virtual ~LineUpWindow();

        virtual void Initialize() override;

        void SetPlayerTeamTitle(eTeamColor eColor);
        void SetEnemyTeamTitle(eTeamColor eColor);

    private:
        LineUpTeamTitle* PlayerTeamTitle;
        LineUpTeamTitle* EnemyTeamTitle;
    };
}