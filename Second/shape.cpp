#define _WIN32_WINNT 0x0500
//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include <windows.h>

#include "screen.h"
#include "shape.h"
#include "shapes/hat_circle.h"
#include "shapes/line.h"
#include "shapes/face.h"
#include "shapes/rectangle.h"


void down(shape& p, const shape& q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}
// Cборная пользовательская фигура - физиономия

void up(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, не член класса! Динамическое связывание!!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, XMAX * 9, YMAX * 9, TRUE);
	

	setlocale(LC_ALL, "Rus");
	screen_init();

	//== 1.Объявление набора фигур ==
	hat_circle hat(point(1, 1), point(15, 7));
	line brim(point(5, 15), 17);
	face face(point(20, 52), point(32, 60));
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

//== 2.Подготовка к сборке ==
	hat.rotate_right();
	hat.resize(3);
	brim.resize(3);
	face.resize(3);
	face.move(-8, -9);
	shape_refresh();
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений
//== 2.1 Исправление ошибок 
	shape_refresh();
	std::cout << "=== Fixed ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений
//== 3.Сборка изображения ==
	//face.move(0, -10); // Лицо - в исходное положение
	up(brim, face);
	up(hat, brim);
	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}
