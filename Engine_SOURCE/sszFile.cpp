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

        if (!mLoadFile.is_open())					// 파일 열람 검사
        {
            std::wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"파일 불러오기 실패", MB_OK);
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
        // 만약 SaveFile이 열려있다면 이전 SaveFile을 닫고 새로 연다

        // 작업중

        std::wofstream ofs; // 저장용 파일 스트림

        ofs.open(path, std::ios::binary); // 바이너리형식으로 저장요 파일을 열람

        // 파일 열람에 실패할 경우 return S_FALSE;

        // 저장할 데이터를 불러온다.
        // 여러개일 경우 iterator를 사용해 while로 반복문을 돌려준다.

        std::wstring szbuff = {}; // 저장용 내용을 담을 버퍼

        // Data와 구분자를 넣어 이어붙인다.
        // szbuff += std::to_wstring(data) + L',';
        // szbuff += std::to_wstring(data) + L'\n'; // 마지막 값

        ofs.write(szbuff.c_str(), szbuff.size()); // 담아놓은 szbuff line을 파일에 입력

        // ofs.close(); // 저장용 파일을 닫는다.

        return S_OK;
    }

    HRESULT File::OpenLoadFile(const std::wstring& path)
    {
        // 만약 LoadFile이 열려있다면 이전 LoadFile을 닫고 새로 연다
         
        // 작업중

        std::wifstream ifs;

        if (!ifs.is_open())	// 파일 열람 검사
        {
            std::wstring errMsg = L"해당 파일이 없거나 파일 경로가 올바르지 않습니다. \n 찾는 파일 경로 : \n";
            errMsg += path;
            MessageBox(nullptr, errMsg.c_str(), L"Load 파일 불러오기 실패", MB_OK);
            return S_FALSE;
        }

        std::wstring LoadData;
        std::getline(ifs, LoadData, L','); // ,를 구분자로 Data를 얻어온다.
        std::getline(ifs, LoadData, L'\n'); // ,를 구분자로 Data를 얻어온다.

        // 언더온 LoadData를 입력할 Data에 입력.
        while (!ifs.eof())
        {
            // Load Data(ifs); // 데이터를 읽어오는 함수
            // 함수 포인터로받아 외부에서 구현한 내용을 얻어오도록 함
        }

        ifs.close(); // Load용 파일 닫기

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