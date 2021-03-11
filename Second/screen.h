#pragma once
#include <Windows.h>
#include "Exceptions/CantPutPoint.h"
#include<iostream>

class Screen
{
public:
	int XMAX;
	int YMAX;
	Screen(int Width, int Height)
	{
		hConsle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		dwBytesWritten = 0;
		SetConsoleActiveScreenBuffer(hConsle);

		XMAX = Width;
		YMAX = Height;
		screen = new wchar_t[XMAX * YMAX];
		for (int y = 0; y < YMAX; ++y)
		{
			for (int x = 0; x < XMAX; ++x)
				screen[y * XMAX + x] = white;
		}
	}
	~Screen()
	{
		delete[] screen;
	}
	void screen_refresh() // Обновление экрана
	{
		screen[XMAX * YMAX - 1] = '\0';
		WriteConsoleOutputCharacter(hConsle, screen, XMAX * YMAX, { 0,0 }, &dwBytesWritten);
	}
	void screen_clear()
	{
		for (int y = 0; y < YMAX; ++y)
		{
			for (int x = 0; x < XMAX; ++x)
				screen[y * XMAX + x] = white;
		}
	}
	bool on_screen(int a, int b) // проверка попадания точки на экран
	{
		return (0 <= a && a < XMAX && 0 <= b && b < YMAX);// ? true : throw CantPutPoint("Can't put point at position", a, b);
	}
	void put_point(int a, int b)
	{
		if (on_screen(a, b)) screen[(YMAX - b) * XMAX + a] = black;
	}

private:
	HANDLE hConsle;
	DWORD dwBytesWritten;
	wchar_t* screen;
	enum color { black = '@', white = ' ' };
}gScreen(60, 60);