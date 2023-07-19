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

            ButtonUI* GetBtnComponent() { return mBtnComp; }

        private:
            ButtonUI* mBtnComp;
	};
}