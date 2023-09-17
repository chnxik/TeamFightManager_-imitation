#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class TeamIcon;

    class SelectBtn :
        public UIObject
    {
    public:
        SelectBtn(const std::wstring& key);
        virtual ~SelectBtn();

        virtual void Initialize() override;

        void InitCheckSelected(UIObject** object);
        void InitItemTex(std::wstring Texkey, UINT idx, Vector3 Pos, Vector3 Scale, UIObject* parent);

    private:
        UIObject*   mItemObj;
        bool        bSelected;
    };
}