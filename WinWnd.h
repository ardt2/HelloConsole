// ============================================================================
// WinWnd.h,  2019
// ������� 0.01.00
// ============================================================================
// #pragma once � ������������.

#ifndef WINWND_H_00100
#define WINWND_H_00100

// ============================================================================
#include <iostream>

using std::ostream;
using std::ios_base;

using std::cout;
using std::endl;

extern ostream & logout; // ����������� � WinWnd.cpp

// ----------------------------------------------------------------------------
#include <string>

using std::string;


// ����� ���������� Windows:
// ============================================================================
#define WIN32_LEAN_AND_MEAN // ��������� ����� ������������ ���������� �� ���������� Windows
#include <windows.h>	    // (�� stdafx.h)


// ======================================================================
template<typename T>
ostream & Print(const string & msg, const T & obj, ostream & stream = logout)
{
    stream << msg << " " << obj;
	return stream;
}
// ----------------------------------------------------------------------
template<typename T>
ostream & Println(const string & msg, const T & obj, ostream & stream = logout)
{
    Print<T>(msg, obj);
    stream << endl;
	return stream;
}
// ----------------------------------------------------------------------
template<typename T>
ostream & Log(const string & msg, const T & obj, ostream & stream = logout)
{
    // ����� ���� �� ������� ������������ ����������� ��������.
    if (LOGENABLED) stream << msg << " " << obj;
	return stream;
	// if (LOGENABLED) Return(msg, obj); // TODO: ����� ���������.
}
// ----------------------------------------------------------------------
template<typename T>
ostream & Logln(const string & msg, const T & obj, ostream & stream = logout)
{
    Log<T>(msg, obj);
    if (LOGENABLED) stream << endl;
	return stream;
}


// ============================================================================
extern void SetPixel(int x, int y, COLORREF c);

extern void CreateWinWnd(void);
extern void ShowWinWnd(void);
extern void ClearWinWnd(void);

extern void SetupWinBitmaps(void);
extern void SwapBuffers(void);

extern void TestDraw(void);


// ============================================================================
#endif // ������ ���������� ���������.