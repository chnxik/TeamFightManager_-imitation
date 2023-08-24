#include "sszLog.h"
#include "CommonObjHeader.h"

namespace ssz
{
	std::wstring Log::mLogStr;

	void Log::AddLog(const std::wstring& string)
	{
		if (!(mLogStr.empty()))
			mLogStr += L"\n";

		mLogStr += string;
	}

	void Log::Render()
	{
		FontWrapper::DrawFont(mLogStr.c_str(), 10.f, 120.f, 20.f, FONT_RGBA(255, 255, 255, 255));
	}

	void Log::Clear()
	{
		mLogStr.clear();
		mLogStr = L"�α� �׽�Ʈ";
	}
}