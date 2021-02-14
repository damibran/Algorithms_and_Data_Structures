#include "screen.h"
#include "shape.h"
#define _WIN32_WINNT 0x0500

//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include <windows.h>
// ПРИМЕР ДОБАВКИ: дополнительный фрагмент - полуокружность
class h_circle : public rectangle {
public:
	h_circle(point c, int r) : rectangle(point(c.x - r, c.y - r), point(c.x + r, c.y + r)) {}

	void draw();
};
void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{   //(выдаются два сектора, указываемые значением reflected)
	int x0 = (sw.x + ne.x) / 2, y0 = (sw.y + ne.y) / 2;
	int radius = (ne.x - sw.x) / 2;
	int x = 0, y = radius, delta = 1 - 2 * radius, error = 0;
	float k=0.65;
	while (y >= 0) 
	{ // Цикл рисования

		put_point(x0 + x, y0 + y * k);
		put_point(x0 + x, y0 - y * k);
		put_point(x0 - x, y0 + y * k);
		put_point(x0 - x, y0 - y * k);

		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0)
		{
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) 
		{
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		delta += 2 * (++x - --y);
	}
}



void down(shape& p, const shape& q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}
// Cборная пользовательская фигура - физиономия
class myshape : public rectangle { // Моя фигура ЯВЛЯЕТСЯ
	int w, h;			             //        прямоугольником
	h_circle l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
	h_circle r_eye; // правый глаз
	line mouth; // рот
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(float d)
	{ 
		w *= d;
		h *= d;
		rectangle::resize(d);
		l_eye.resize(3 * d / 4);
		l_eye.move(swest().x - l_eye.swest().x + 2 * d, swest().y - l_eye.swest().y + h * 2 / 4);
		r_eye.resize(3*d/4);
		r_eye.move(swest().x - r_eye.swest().x + w - 5 * d, swest().y - r_eye.swest().y +  h * 2 / 4);
		mouth.resize(d);
		mouth.move(swest().x - mouth.swest().x +2*d, swest().y - mouth.swest().y +  h /4);

	}
};
myshape::myshape(point a, point b)
	: rectangle(a, b),	//Инициализация базового класса
	w(neast().x - swest().x + 1), // Инициализация данных
	h(neast().y - swest().y + 1), // - строго в порядке объявления!
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4),2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{ }
void myshape::draw()
{
	rectangle::draw(); //Контур лица (глаза и нос рисуются сами!) 
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b)); // Нос – существует только на рисунке!
}
void myshape::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b); 
	r_eye.move(a, b);
	mouth.move(a, b);
}
int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, XMAX*9, YMAX*20, TRUE);

	setlocale(LC_ALL, "Rus");
	screen_init();
	//== 1.Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 17);
	myshape face(point(15, 10), point(27, 18));
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

//== 2.Подготовка к сборке ==
	hat.rotate_right();
	hat.resize(3);
	brim.resize(3);
	face.resize(3);
	face.move(-10, -10);
	shape_refresh();
	std::cout << "=== Prepared... ===\n";
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
