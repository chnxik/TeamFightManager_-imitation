#pragma once
#include "sszEngine.h"

namespace ssz
{
	class Log
	{
	public:
		static void AddLog(const std::wstring& string);
		static void Render();
		static void Clear();

		static int GetLogCnt() { return iLogCnt; }

	private:
		static std::wstring mLogStr;
		static int iLogCnt;
	};
}