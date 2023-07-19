#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class ButtonUI;

	class ImportantBtn : public UIObject
	{
	public:
		ImportantBtn(const std::wstring& Key);
		virtual ~ImportantBtn();

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
	};
}