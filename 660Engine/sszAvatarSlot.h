#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class AvatarSlot :
        public UIObject
    {
    public:
        AvatarSlot(const std::wstring& key);
        virtual ~AvatarSlot();

        virtual void Initialize() override;

        void ChangeHair(std::wstring Texkey);

    private:
        UIObject* mAvatarBody;
        UIObject* mAvatarHair;
    };
}