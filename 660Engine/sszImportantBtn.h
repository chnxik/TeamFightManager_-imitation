#pragma once
#include "sszUIObject.h"
#include "sszKBDIcon.h"

namespace ssz
{
	class ButtonUI;

	class ImportantBtn : public UIObject
	{
	public:
		ImportantBtn(const std::wstring& Key);
		virtual ~ImportantBtn();

		virtual void Initialize() override;

		ButtonUI* GetBtnComponent() { return mBtnComp; }
		void SetKBDIcon(KBDIcon::KEYICON key);

	private:
		ButtonUI* mBtnComp;
		KBDIcon* mKBDIcon;
	};
}