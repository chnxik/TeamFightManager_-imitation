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
        wchar_t szExtension[50] = {}; // Ȯ���� �Ǵ�
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

        std::wstring extension = szExtension;

        mFile.open(path);

        if (!mFile.is_open())					// ���� ���� �˻�
        {
            std::wstring errMsg = L"�ش� ������ ���ų� ���� ��ΰ� �ùٸ��� �ʽ��ϴ�. \n ã�� ���� ��� : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"���� �ҷ����� ����", MB_OK);
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