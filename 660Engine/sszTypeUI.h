#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class TypeUI : public UIObject
	{
	public:
		TypeUI(const std::wstring& key);
		virtual ~TypeUI();

		virtual void Initialize();
		virtual void Update();

	private:
		bool bTypeMode;
		bool bPrevSelected;
	};
}