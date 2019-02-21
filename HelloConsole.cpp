﻿// ============================================================================
// HelloConsole.cpp: Консольное приложение с доп. окошками – шаблон.
//
// 2019. Вариант 1.
// If you can't see comments in Russian on Git, download and see its locally.
// (Solved.)
// ============================================================================

#include "HelloConsole.h"
// ----------------------------------------------------------------------------
#define LOGENABLED true
#include "WinWnd.h"

// ============================================================================
static const float Version = 0.01f;


// ============================================================================
exception Exc; // До этого места полагается уже определить GetUnexpected;
                          // Где-нибудь в какой-нибудь далекой _SystemInit...


// ============================================================================
static const char * const SetLocale(void);
static void Reset1(void);


// ============================================================================
template<typename T> class testclass
{

};


// ============================================================================
int main(int argc, char argv[]) // Можно что-нибудь перетянуть на ярлычок
{                               // на рабочем столе и посмотреть argv[1].
    Println("Локаль:", SetLocale()) << endl; // Маленькая шалость.
#ifdef _DEBUG
    Println("Отладочная сборка:", Version);
#else
    Println("Без отладки:", Version);
#endif
    Println("Разрядность системы (бит):", _INTEGRAL_MAX_BITS);
#ifdef WIN32
    Println("Разрядность сборки (бит):", 32) << endl;   // TODO: Поаккуратнее.
#else
    Println("Разрядность сборки (бит):", 64) << endl;
#endif

    // ------------------------------------------------------------------------
    CreateWinWnd();
    SetupWinBitmaps();
    ShowWinWnd();

    TestDraw();
    SwapBuffers();



    //-------------------------------------------------------------------------
    // Цилиндрическая часть котла — коническая. Хи-хи.
    // (Ну, так-то образована из телескопически сопряжённых цилиндрических
    // барабанов.) (Паровоз П38, википедиа.)
    // ------------------------------------------------------------------------
    MSG msg;
    // --------------------------------------------------------------------
    while (GetMessageA(&msg, nullptr, 0, 0))
    {
        //		cout << msg.message << " " << msg.time << "\n";

        //		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }




    return 0;
}


// ============================================================================
const char * const SetLocale(void)
{
    ios_base::sync_with_stdio(false);
    return setlocale(LC_ALL, "rus");
}


// ============================================================================
void Reset1(void)
{

}


// ============================================================================
inline void TechInfo(void)
{
//#ifdef _DEBUG  // __LINE__, __FILE__, __TIME__.
//    // -- Тех. инфо. ----------------------------------------------------------
//    cout << "Отладка." << endl << endl;
//
//    // docs.microsoft.com/ru-ru/cpp/preprocessor/predefined-macros?view=vs-2017
//    cout << "Имя функции:    " << __FUNCTION__ << endl;
//    cout << "Декорированное: " << __FUNCDNAME__ << endl;
//    cout << "Отпечаток:      " << __FUNCSIG__ << endl;
//#else
//    cout << "Без отладки." << __FUNCTION__ << endl << endl;
//#endif
//    cout << "Разрядность системы (бит): " << _INTEGRAL_MAX_BITS << endl;
//    cout << "Локаль сборки:             " << TmpString << endl;
//    // 	cout << "Разрядность сборки (бит): " << // TODO:
}


// ============================================================================



// ============================================================================



/* Плюшкинизм. (

    while (true)
    {
        Sleep(5000);
        break;
    }

*/
