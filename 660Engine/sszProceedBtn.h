#pragma once
#include "sszUIObject.h"

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

        private:
            ButtonUI* mBtnComp;
            UIObject* ProceedBtnArrowMark;

            float mDefalutMarkPos_x;
	};
}