#pragma once
#include "sszUIObject.h"

namespace ssz
{
    class ButtonUI;

    class TitleMenuBtn : public UIObject
    {
    public:
        TitleMenuBtn(const std::wstring& Key);
        virtual ~TitleMenuBtn();

		virtual void Initialize() override;
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetNewGameBtn();
		void SetLoadBtn();
		void SetExitBtn();

		virtual void MouseUp();
		virtual void MouseAway();

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
    };
}