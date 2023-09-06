#include "framework.h"
#include "Editor_Window.h"

#include "..\Engine_SOURCE\sszApplication.h"
// #include <vld.h> // vld 설치 되어있는 경우 추가

#include "guiEditor.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\660Engine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\660Engine.lib")
#endif

ssz::Application application;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 한글 입력
wchar_t    g_strText[_MAX_FNAME];        // 텍스트를 저장하기 위한 변수
wchar_t    g_strCombine[10];             // 조합 중인 문자
wchar_t    g_strSpecial[_MAX_FNAME];     // 특수 문자를 위한 변수
int     mSpecialPos;                // 특수 문자의 위치
int     nSpecialMax;                // 특수 문자의 최대 개수

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 메모리릭(누수) 찾기
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(217);
    // _CrtDumpMemoryLeaks();

    SetProcessDPIAware();

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 게임 로직이 돌아가야한다.
            application.Run();
            gui::Editor::Run();
            application.Present();
        }
    }

    application.Release();
    gui::Editor::Release();

    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL; // MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
      CW_USEDEFAULT, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   application.SetWindow(hWnd, 1920, 1080);

   // Cursor 감추기
   ShowCursor(false);

   application.Initialize();
   gui::Editor::Initialize();

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

int GetText(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // IME 한글 입력
    if (GetText(hWnd, message, wParam, lParam) == 0)
    {
        
        return 0;
    }

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



int GetText(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int nLen;

    HIMC    m_hIMC = NULL;      // IME 핸들

    switch (msg)
    {
    case WM_IME_COMPOSITION:    // 글씨 조합중
    {
        // 메세지 처리루틴

        m_hIMC = ImmGetContext(hWnd); // IME 핸들을 얻어온다.

        // HCS_RESULTSTR : 완성된 문자
        if (lParam & GCS_RESULTSTR)
        {
            // ImmGetCompositionString
            // : 현재 IME에 입력되어 있는 한글코드의 크기 및 내용을 취득
            if ((nLen = ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, NULL, 0)) > 0)
            {
                // 현재 IME의 스트링 길이를 얻는다.

                // strCombine에 조합 중인 문자열을 받아낸다.
                ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, g_strCombine, nLen);

                g_strCombine[nLen] = NULL; // 문자열의 마지막 문자 NULL 처리
                wcscpy_s(g_strText + wcslen(g_strText), nLen, g_strCombine);  // 전체 내용 뒤에 보여주 후

                // 초기화
                memset(g_strCombine, 0, 10);

                // 한 문자가 조합 중에 다음 문자가 들어오면 ..
            }
        }
        // GCS_COMPSTR : 조합중인 문자
        else if (lParam & GCS_COMPSTR)
        {
            // 조합 중인 문자열의 길이를 얻는다.
            nLen = ImmGetCompositionString(m_hIMC, GCS_COMPSTR, NULL, 0);

            // strCombine에 조합 중인 문자열을 받아낸다.
            ImmGetCompositionString(m_hIMC, GCS_COMPSTR, g_strCombine, nLen);

            g_strCombine[nLen] = NULL; // 문자열의 마지막 문자 NULL 처리

            // 글씨 찍을 때는 strText + strCombine 해서 보여주면 도니다.
        }

        // 핸들 반환
        ImmReleaseContext(hWnd, m_hIMC);
    }
    return 0;
    case WM_CHAR:               // 문자 넘어오기 : 영문의 경우 바로 반환, 한글같은 조합문자는 한 글자가 완성되면 반환
    {
        /*
        일반적인 IME의 동작
        일반적으로 핸들을 상속받아 만든 윈도우는 영어입력을 받으면
        WM_KEYDOWN 다음에 WM_CHAR_메세지가 발생하지만,
        한글의 경우 WM_KEYDOWN 다음에 WM_IME_COMPOSITION이 발생하고,
        한글이 완성되면 WM_CHAR가 2번 발생하게 된다.
        2번인 이유는, 한글은 2byte 이기 때문에 한번에 전달할 수 없기때문이다.
        이 때문에 한글 처리는 글자 단위로 해야한다.
         */

         // 만약 Backspace 라면,

        // ENTER 입력
        if (wParam == 0x0D)
        {
            return 0;// 아무 동작하지 않는다.
        }

        if (wParam == 8)
        {
            // 길이가 0보다 크고, 지울 것이 0보다 작으면 이라는 의미
            // 본 의도는 완성형에서 앞글자인지 뒷글자인지 알려주는 함수가 있다.
            if (wcslen(g_strText) > 0)
            {
                if (wcslen(g_strText) < 0)
                {
                    // 글자 하나를 지운다.
                    g_strText[wcslen(g_strText) - 1] = 0;
                }
                // 글자 하나를 지운다.
                g_strText[wcslen(g_strText) - 1] = 0;
            }
        }
        else
        {
            nLen = (int)wcslen(g_strText);

            g_strText[nLen] = wParam & 0xff;  // 넘어온 문자를 문자열에 넣기
            g_strText[nLen + 1] = NULL;
        }
    }
    return 0;
    }

    return 1;
};
