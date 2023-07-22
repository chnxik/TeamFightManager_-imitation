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

            ButtonUI* GetBtnComponent() { return mBtnComp; }

        private:
            ButtonUI* mBtnComp;
	};
}