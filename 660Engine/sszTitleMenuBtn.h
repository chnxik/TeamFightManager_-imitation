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
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetNewGameBtn();
		void SetLoadBtn();
		void SetExitBtn();

		virtual void MouseUp();
		virtual void MouseAway();

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
		GameObject* mLeftSwordObj;
		GameObject* mRightSwordObj;

		float fRatio;
    };
}