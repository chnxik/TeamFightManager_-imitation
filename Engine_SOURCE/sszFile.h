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
        std::wifstream& GetFile() { return mFile; }
        void FileClose();

        HRESULT DeleteLine();
        HRESULT SetData(std::wstring& dest, wchar_t Delim);
        HRESULT SetData(int& dest, wchar_t Delim);
        HRESULT SetData(float& dest, wchar_t Delim);

        bool IsEOF();
        
    private:
        std::wifstream mFile;
    };
}