#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class ButtonUI;

	class WeeklyEventBtn : public UIObject
	{
	public:
		WeeklyEventBtn(const std::wstring& Key);
		virtual ~WeeklyEventBtn();

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
	};
}