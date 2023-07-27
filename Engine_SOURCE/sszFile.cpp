#include "sszFile.h"

namespace ssz
{
    File::File()
        : Resource(enums::eResourceType::File)
    {
    }
    File::~File()
    {
        FileClose();
    }
    HRESULT File::Load(const std::wstring& path)
    {
        wchar_t szExtension[50] = {}; // 확장자 판단
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

        std::wstring extension = szExtension;

        mFile.open(path);

        if (!mFile.is_open())					// 파일 열람 검사
        {
            std::wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"파일 불러오기 실패", MB_OK);
            return S_FALSE;
        }

        return S_OK;
    }
    void File::FileClose()
    {
        if (mFile.is_open())
            mFile.close();
    }
    HRESULT File::DeleteLine()
    {
        std::wstring GarbageLine;
        std::getline(mFile, GarbageLine);

        return S_OK;
    }
    HRESULT File::SetData(std::wstring& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mFile.eof())
            return S_FALSE;

        return S_OK;
    }
    HRESULT File::SetData(int& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mFile.eof())
            return S_FALSE;

        return S_OK;
    }
    HRESULT File::SetData(float& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mFile.eof())
            return S_FALSE;

        return S_OK;
    }
    bool File::IsEOF()
    {
        return mFile.eof();
    }
}