#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class ButtonUI;

    class DefaultBtn : public UIObject
    {
	public:
		DefaultBtn(const std::wstring& Key);
		virtual ~DefaultBtn();

		virtual void Initialize() override;
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
    };
}