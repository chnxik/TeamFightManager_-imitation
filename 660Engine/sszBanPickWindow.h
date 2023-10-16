#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"

namespace ssz
{
    class BanPickStat;
    class BanLine;
    class Champ;
    class Text;

    class BanPickWindow : public UIObject
    {
    public:
        BanPickWindow(const std::wstring& key);
        virtual ~BanPickWindow();

        virtual void Initialize() override;
        
        void PreviewChampInfo(Champ* champ);

        void Done();

    private:
        BanLine* mBanLine;
        BanPickStat* mBanPickStat[(UINT)eStatType::END];

        Text* mClassTypeText;
        Text* mClassNameText;

        UIObject* mChampPreview;

        UIObject* mSkillIcon;
        UIObject* mUltIcon;
        
        UIObject* mSkillCoolIcon;
        UIObject* mUltCoolIcon;

        Text* mSkillCool;
        Text* mUltCool;

        Text* mSkillInfo;
        Text* mUltInfo;
    };
}