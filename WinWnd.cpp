// ============================================================================
// WinWnd.cpp, 2019
// Âàðèàíò 0.01.00
//
// Äåâèç äíÿ: Ïîèñê ïî ôàéëàì ñòðîêè "TODO" ïîëåçåí. 
// ============================================================================


// ----------------------------------------------------------------------------
#define LOGENABLED true
#include "WinWnd.h"


// ----------------------------------------------------------------------------
ostream & logout = cout;

// ----------------------------------------------------------------------------
int Width = 640, Height = 480;

// ----------------------------------------------------------------------------
static HINSTANCE hModule = nullptr;

static const char * const szWindowClass = "ArtWndClass";
static const char * const szTitle = "Òåñòîâîå îêíî";

static ATOM WndClass = 0;   // Ðåäàêòîð ñâÿçåé àêà ëèíêåð âèäèò ñòàòè÷åñêèå
static HWND hWnd = nullptr; // ãëîáàëüíûå ïåðåìåííûå òîëüêî â ýòîì ôàéëå
static HDC hWndDC, hBitmapDC, hMemDC; // îíè òàê è íàçûâàþòñÿ – ôàéëîâûå
static HBITMAP hBitmap;               // ïåðåìåííûå è ðàáîòàþò êàê
                                      // ïðèâàòíûå ïîëÿ â êëàññå.

// ----------------------------------------------------------------------------
static ATOM RegisterWndClass(void);
//static HWND CreateWnd(const char * const , void * );
static HWND CreateWnd(int x, int y, int width, int height, const char * const title, void* lptr);
static LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM );


// ============================================================================
void TestDraw(void)
{
    // Word6bit c; Ýòî ìû â äðóãîì ïðîåêòå ðàññìîòðèì. )

    // SetPixelV(hBitmapDC, 100, 100, 0x00FFFFFF); // Ðàáîòàåò.

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            COLORREF colordword;
            colordword = RGB((WORD)(y / float(Height) * 0xFF), (WORD)(x / float(Width) * 0xFF), 0);
            SetPixelV(hBitmapDC, x, y, colordword);
        }
    }

}


// ============================================================================
void CreateWinWnd(void)
{
    DWORD dwres = 1;

    hModule = GetModuleHandleA(nullptr);
    dwres = GetLastError();
    Logln("hModule", hModule);

    WndClass = RegisterWndClass();
    dwres = GetLastError();
    Logln("hModule", WndClass);

	hWnd = CreateWnd(300, 300, Width, Height, szTitle, nullptr);
    dwres = GetLastError();
    Logln("hWnd", WndClass);
}


// ============================================================================
void ShowWinWnd(void)
{
    BOOL res = false;
    res = ShowWindow(hWnd, SW_SHOWNA); // SW_SHOW
    res = UpdateWindow(hWnd);

    DWORD dwres = GetLastError();
}


// ============================================================================
void ClearWinWnd(void)
{
    BOOL res = UnregisterClassA(szWindowClass, hModule);

    DWORD dwres = GetLastError();
}


// ============================================================================
void SetupWinBitmaps(void)
{
    hWndDC = GetDC(hWnd);
    Logln("hWndDC", hWndDC);

    hBitmapDC = CreateCompatibleDC(hWndDC);
    Logln("hWndDC", hWndDC);

    hBitmap = CreateCompatibleBitmap(hWndDC, 640, 480);
    Logln("hBitmap", hBitmap);

    GetBitmapBits(hBitmap, 0, nullptr);

    SelectObject(hBitmapDC, hBitmap);
    int intres = GetDeviceCaps(hBitmapDC, COLORRES);
    Logln("COLORRES", intres);
}


// ============================================================================
void SwapBuffers(void)
{
    BOOL res = BitBlt(hWndDC, 0, 0, Width, Height, hBitmapDC, 0, 0, SRCCOPY);
}


// --------------------------------------------------------------------------------------------
ATOM RegisterWndClass(void)
{
    //	hModule = GetModuleHandleA(NULL);

    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 16;
    wcex.hInstance = hModule; // hInstance;
    wcex.hIcon = NULL; // LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOW));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_WINDOW);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    WndClass = RegisterClassExA(&wcex);

    DWORD res = GetLastError();

    return WndClass;
}


// --------------------------------------------------------------------------------------------
HWND CreateWnd(int x, int y, int width, int height, const char * const title, void* lptr)
{
    hWnd =
        CreateWindowExA(0L, szWindowClass, title, WS_OVERLAPPEDWINDOW,
                        x, y, width, height,
                        nullptr, nullptr, hModule, lptr);

    DWORD res = GetLastError();

    return hWnd;
}


// --------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT messageid, WPARAM wparam, LPARAM lparam)
{
//	cout << messageid << endl;
    switch (messageid)
    {
        case WM_CREATE:
        {						    // Äîëæíà âîçâðàùàòü 0, åñëè óñïåøíî è íå 0, åñëè íåò. 
            //hWndDC = GetDC(hWnd);	// È äàæå ìîæíî ïðîâåðèòü ÷åðåç GetLastError(), ïî ìîåìó.
        }
        break;

        case WM_CLOSE:
        {
            DeleteDC(hBitmapDC);		// Ýòîò ìû ñîçäàëè,
            ReleaseDC(hwnd, hWndDC);	// À ýòîò âçÿëè ïîïîëüçîâàòüñÿ.
            DestroyWindow(hwnd);
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_GETICON: // Âîçâðàùàåò hIcon.
            break;

        default:
            return DefWindowProcA(hwnd, messageid, wparam, lparam);
    }

    return 0; // Ñòàðûå äîáðûå âðåìåíà, 0, îí æå NULL.
}

