#pragma once
#include "sszEngine.h"

namespace ssz
{
	class FileManager
	{
	public:
		static HRESULT OpenLoadFile(const std::wstring& _Filepath);
		static HRESULT OpenSaveFile(const std::wstring& _Filepath);
		
		static void Initialize();

		static void CloseLoadFile();
		static void CloseSaveFile();
		
		static void Release();

		static std::wifstream* GetLoadFile() { return mLoadFile; }
		static std::wofstream* GetSaveFile() { return mSaveFile; }

		static HRESULT DeleteLine();

		static HRESULT DataLoad(std::wstring& dest);
		static HRESULT DataLoad(std::wstring& dest, wchar_t Delim);
		static HRESULT DataLoad(int& dest, wchar_t Delim);
		static HRESULT DataLoad(float& dest, wchar_t Delim);

		static HRESULT DataSave(std::wstring& source);

	public:
		static std::wifstream* mLoadFile;
		static std::wofstream* mSaveFile;
	};
}

