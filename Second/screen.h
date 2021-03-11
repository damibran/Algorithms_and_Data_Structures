#pragma once
#include <Windows.h>
#include "Exceptions/CantPutPoint.h"
#include<iostream>

class point {	//Точка на экране
public:
	int x, y;
	point(int a = 0, int b = 0) : x(a), y(b) {  }
};

class Screen
{
public:
	int XMAX;
	int YMAX;
	Screen(int Width,int Height)
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
		for (int y = 0; y < YMAX; ++y)
		{
			for (int x = 0; x < XMAX; ++x)
				screen[y * XMAX + x] = black;
		}
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
		return (0 <= a && a < XMAX && 0 <= b && b < YMAX) ? true : throw CantPutPoint("Can't put point at position", a, b);
	}
	void put_point(int a, int b)
	{
		if (on_screen(a, b)) screen[(YMAX-b) * XMAX + a] = black;
	}
	void put_point(point p)
	{
		put_point(p.x, p.y);
	}
	void put_line(int x0, int y0, int x1, int y1)
		/* Алгоритм Брезенхэма для прямой:
		рисование отрезка прямой от (x0,y0) до (x1,y1).
		Уравнение прямой: b(x-x0) + a(y-y0) = 0.
		Минимизируется величина abs(eps), где eps = 2*(b(x-x0)) + a(y-y0).  */
	{
		int dx = 1;
		int a = x1 - x0;   if (a < 0) dx = -1, a = -a;
		int dy = 1;
		int b = y1 - y0;   if (b < 0) dy = -1, b = -b;
		int two_a = 2 * a;
		int two_b = 2 * b;
		int xcrit = -b + two_a;
		int eps = 0;
		for (;;) { //Формирование прямой линии по точкам
			put_point(x0, y0);
			if (x0 == x1 && y0 == y1) break;
			if (eps <= xcrit) x0 += dx, eps += two_b;
			if (eps >= a || a < b) y0 += dy, eps -= two_a;
		}
	}
	void put_line(point a, point b)
	{
		put_line(a.x, a.y, b.x, b.y);
	}
private:
	HANDLE hConsle;
	DWORD dwBytesWritten;
	wchar_t* screen;
	enum color { black = '@', white = ' ' };
}gScreen(60,60);