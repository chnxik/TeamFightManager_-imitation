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

        void SetPlayerTeamTitle(ssz::LineUpTeamTitle::eColorType eColor);
        void SetEnemyTeamTitle(ssz::LineUpTeamTitle::eColorType eColor);

    private:
        LineUpTeamTitle* PlayerTeamTitle;
        LineUpTeamTitle* EnemyTeamTitle;
    };
}