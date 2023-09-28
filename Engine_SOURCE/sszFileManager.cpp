#include "sszFileManager.h"

namespace ssz
{
	std::wifstream* ssz::FileManager::mLoadFile = nullptr;
	std::wofstream* ssz::FileManager::mSaveFile = nullptr;

	HRESULT FileManager::OpenLoadFile(const std::wstring& _FileName)
	{
		std::wstring FilePath = L"..\\Resources\\Data\\";
		FilePath += _FileName;
		mLoadFile->open(FilePath, std::ios::in | std::ios::binary);

		if (!mLoadFile->is_open())					// 파일 열람 검사
		{
			std::wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
			errMsg += FilePath;
			MessageBox(nullptr, errMsg.c_str(), L"파일 불러오기 실패", MB_OK);
			return S_FALSE;
		}

		return S_OK;
	}
	
	HRESULT FileManager::OpenSaveFile(const std::wstring& _FileName)
	{
		std::locale::global(std::locale("Korean"));

		std::wstring FilePath = L"..\\Resources\\Data\\";
		FilePath += _FileName;
		mSaveFile->open(FilePath, std::ios::out | std::ios::binary);

		if (!mSaveFile->is_open())					// 파일 열람 검사
		{
			std::wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
			errMsg += FilePath;
			MessageBox(nullptr, errMsg.c_str(), L"파일 불러오기 실패", MB_OK);
			return S_FALSE;
		}

		return S_OK;
	}

	void FileManager::Initialize()
	{
		std::locale::global(std::locale("Korean"));

		mLoadFile = new std::wifstream();
		mSaveFile = new std::wofstream();
	}

	void FileManager::CloseLoadFile()
	{
		if (mLoadFile->is_open())
			mLoadFile->close();
	}

	void FileManager::CloseSaveFile()
	{
		if (mSaveFile->is_open())
			mSaveFile->close();
	}

	void FileManager::Release()
	{
		if (mLoadFile->is_open())
			mLoadFile->close();

		if (mSaveFile->is_open())
			mSaveFile->close();

		delete mLoadFile;
		delete mSaveFile;
	}
	
	HRESULT FileManager::DeleteLine()
	{
		std::wstring GarbageLine;
		std::getline(*mLoadFile, GarbageLine);

		return S_OK;
	}
	
	HRESULT FileManager::DataLoad(std::wstring& dest)
	{
		wchar_t szbuff[50] = {};
		mLoadFile->getline(szbuff, 50);
		std::wstringstream(szbuff) >> dest;

		if (mLoadFile->eof())
			return S_FALSE;

		return S_OK;
	}

	HRESULT FileManager::DataLoad(std::wstring& dest, wchar_t Delim)
	{
		wchar_t szbuff[50] = {};
		mLoadFile->getline(szbuff, 50, Delim);
		std::wstringstream(szbuff) >> dest;

		if (mLoadFile->eof())
			return S_FALSE;

		return S_OK;
	}
	
	HRESULT FileManager::DataLoad(int& dest, wchar_t Delim)
	{
		wchar_t szbuff[50] = {};
		mLoadFile->getline(szbuff, 50, Delim);
		std::wstringstream(szbuff) >> dest;

		if (mLoadFile->eof())
			return S_FALSE;

		return S_OK;
	}
	
	HRESULT FileManager::DataLoad(float& dest, wchar_t Delim)
	{
		wchar_t szbuff[50] = {};
		mLoadFile->getline(szbuff, 50, Delim);
		std::wstringstream(szbuff) >> dest;

		if (mLoadFile->eof())
			return S_FALSE;

		return S_OK;
	}
	
	HRESULT FileManager::DataSave(std::wstring& source)
	{
		// wstring += std::to_wstring(data) + L',';
		// wstring += std::to_wstring(data) + L'\n';
		
		mSaveFile->write(source.c_str(), source.size());
		
		
		return E_NOTIMPL;
	}
}