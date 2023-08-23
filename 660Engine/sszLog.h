#pragma once

namespace ssz
{
	class Log
	{
	public:
		static void AddLog(const std::wstring& string);
		static void Render();
		static void Clear();

	private:

	private:
		static std::wstring mLogStr;
	};
}