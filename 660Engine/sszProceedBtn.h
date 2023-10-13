#pragma once
#include "sszUIObject.h"
#include "sszKBDIcon.h"

namespace ssz
{
    class ButtonUI;

	class ProceedBtn : public UIObject
	{
        public:
            ProceedBtn(const std::wstring& Key);
            virtual ~ProceedBtn();

            virtual void Initialize() override;
            virtual void Update() override;

            void MarkAnimation();

            ButtonUI* GetBtnComponent() { return mBtnComp; }
            void SetKBDIcon(KBDIcon::KEYICON key);

            void SetActionStr(std::wstring str);

        private:
            ButtonUI* mBtnComp;
            UIObject* ProceedBtnArrowMark;

            KBDIcon* mKBDIcon;
            
            UIObject* mActionStr;

            float mDefalutMarkPos_x;
	};
}