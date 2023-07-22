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

		virtual void Initialize() override;

		ButtonUI* GetBtnComponent() { return mBtnComp; }

	private:
		ButtonUI* mBtnComp;
	};
}