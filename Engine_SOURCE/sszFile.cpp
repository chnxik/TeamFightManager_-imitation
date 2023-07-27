#include "sszFile.h"

namespace ssz
{
    File::File()
        : Resource(enums::eResourceType::File)
    {
    }
    File::~File()
    {
        CloseLoadFile();
        CloseSaveFile();
    }
    HRESULT File::Load(const std::wstring& path)
    {
        mLoadFile.open(path, std::ios::binary);

        if (!mLoadFile.is_open())					// ���� ���� �˻�
        {
            std::wstring errMsg = L"�ش� ������ ���ų� ���� ��ΰ� �ùٸ��� �ʽ��ϴ�. \n ã�� ���� ��� : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"���� �ҷ����� ����", MB_OK);
            return S_FALSE;
        }

        return S_OK;
    }

    void File::CloseLoadFile()
    {
        if (mLoadFile.is_open())
            mLoadFile.close();
    }

    void File::CloseSaveFile()
    {
        if (mSaveFile.is_open())
            mSaveFile.close();
    }

    HRESULT File::OpenSaveFile(const std::wstring& path)
    {
        // ���� SaveFile�� �����ִٸ� ���� SaveFile�� �ݰ� ���� ����

        // �۾���

        std::wofstream ofs; // ����� ���� ��Ʈ��

        ofs.open(path, std::ios::binary); // ���̳ʸ��������� ����� ������ ����

        // ���� ������ ������ ��� return S_FALSE;

        // ������ �����͸� �ҷ��´�.
        // �������� ��� iterator�� ����� while�� �ݺ����� �����ش�.

        std::wstring szbuff = {}; // ����� ������ ���� ����

        // Data�� �����ڸ� �־� �̾���δ�.
        // szbuff += std::to_wstring(data) + L',';
        // szbuff += std::to_wstring(data) + L'\n'; // ������ ��

        ofs.write(szbuff.c_str(), szbuff.size()); // ��Ƴ��� szbuff line�� ���Ͽ� �Է�

        // ofs.close(); // ����� ������ �ݴ´�.

        return S_OK;
    }

    HRESULT File::OpenLoadFile(const std::wstring& path)
    {
        // ���� LoadFile�� �����ִٸ� ���� LoadFile�� �ݰ� ���� ����
         
        // �۾���

        std::wifstream ifs;

        if (!ifs.is_open())	// ���� ���� �˻�
        {
            std::wstring errMsg = L"�ش� ������ ���ų� ���� ��ΰ� �ùٸ��� �ʽ��ϴ�. \n ã�� ���� ��� : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"Load ���� �ҷ����� ����", MB_OK);
            return S_FALSE;
        }

        std::wstring LoadData;
        std::getline(ifs, LoadData, L','); // ,�� �����ڷ� Data�� ���´�.
        std::getline(ifs, LoadData, L'\n'); // ,�� �����ڷ� Data�� ���´�.

        // ����� LoadData�� �Է��� Data�� �Է�.
        while (!ifs.eof())
        {
            // Load Data(ifs); // �����͸� �о���� �Լ�
            // �Լ� �����ͷι޾� �ܺο��� ������ ������ �������� ��
        }

        ifs.close(); // Load�� ���� �ݱ�

        return S_OK;
    }

    HRESULT File::DeleteLine()
    {
        std::wstring GarbageLine;
        std::getline(mLoadFile, GarbageLine);

        return S_OK;
    }
    HRESULT File::SetData(std::wstring& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mLoadFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mLoadFile.eof())
            return S_FALSE;

        return S_OK;
    }
    HRESULT File::SetData(int& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mLoadFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mLoadFile.eof())
            return S_FALSE;

        return S_OK;
    }
    HRESULT File::SetData(float& dest, wchar_t Delim)
    {
        wchar_t szbuff[50] = {};
        mLoadFile.getline(szbuff, 50, Delim);
        std::wstringstream(szbuff) >> dest;

        if (mLoadFile.eof())
            return S_FALSE;

        return S_OK;
    }
}