#pragma once
#include "sszUIObject.h"
#include "sszKBDIcon.h"

namespace ssz
{
	class ButtonUI;

    class DefaultBtn : public UIObject
    {
	public:
		DefaultBtn(const std::wstring& Key);
		virtual ~DefaultBtn();

		virtual void Initialize() override;

		ButtonUI* GetBtnComponent() { return mBtnComp; }
		void SetKBDIcon(KBDIcon::KEYICON key);


	private:
		ButtonUI* mBtnComp;
		KBDIcon* mKBDIcon;
    };
}