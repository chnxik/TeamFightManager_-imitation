#include "sszLog.h"
#include "CommonObjHeader.h"

namespace ssz
{
	std::wstring Log::mLogStr;
	int Log::iLogCnt = 0;

	void Log::AddLog(const std::wstring& string)
	{
		if (!(mLogStr.empty()))
			mLogStr += L"\n";

		mLogStr += string;
		iLogCnt++;
	}

	void Log::Render()
	{
		FontWrapper::DrawFont(mLogStr.c_str(), 10.f, 120.f, 20.f, FONT_RGBA(255, 255, 255, 255));
	}

	void Log::Clear()
	{
		iLogCnt = 0;
		mLogStr.clear();
		mLogStr = L"로그 테스트";
	}
}