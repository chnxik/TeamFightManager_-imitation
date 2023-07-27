#pragma once
#include "sszResource.h"

namespace ssz
{
    class File : public Resource
    {
    public:
        File();
        ~File();

        HRESULT Load(const std::wstring& path);
        void CloseLoadFile();
        void CloseSaveFile();

        HRESULT OpenSaveFile(const std::wstring& path);
        HRESULT OpenLoadFile(const std::wstring& path);

        HRESULT DeleteLine();
        HRESULT SetData(std::wstring& dest, wchar_t Delim);
        HRESULT SetData(int& dest, wchar_t Delim);
        HRESULT SetData(float& dest, wchar_t Delim);

        bool IsEOF();
        
    private:
        std::wifstream mLoadFile;
        std::wofstream mSaveFile;
    };
}