#define _CRT_SECURE_NO_WARNINGS
#include "screen.h"
#include "shape.h"
#include <wchar.h>
#include <cwchar>
#define _WIN32_WINNT 0x0500
//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include <windows.h>

// ПРИМЕР ДОБАВКИ: дополнительный фрагмент - полуокружность
class h_circle : public rectangle
{
public:
	h_circle(point c, int r) : rectangle(point(c.x - r, c.y - r), point(c.x + r, c.y + r)) {}

	void draw();

	int radius()
	{
		return (ne.x - sw.x) / 2;
	}
};
void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{   //(выдаются два сектора, указываемые значением reflected)
	int x0 = (sw.x + ne.x) / 2, y0 = (sw.y + ne.y) / 2;
	int radius = (ne.x - sw.x) / 2;
	int x = 0, y = radius, delta = 1 - 2 * radius, error = 0;
	float k = 1;
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

class hat_circle: public rectangle
{
	int w, h;
	h_circle circle;
public:
	hat_circle(point a, point b) : rectangle(a, b),
		w(neast().x - swest().x ),
		h(neast().y - swest().y ),
		circle(point(south().x, east().y), w >= h ? h/2 : w/2) {
		std::cout << east().y;
	}
	void resize(float d);
	void move(int, int);
};

void hat_circle::move(int a,int b)
{
	rectangle::move(a,b);
	circle.move(a,b);
}

void hat_circle::resize(float d)
{
	rectangle::resize(d);
	circle.resize(d);
	circle.move(south().x - circle.south().x, east().y - circle.east().y);
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
		l_eye.resize(2 * d / 3);
		l_eye.move(swest().x + 2 * d - l_eye.swest().x, neast().y - l_eye.radius() - 2*d - l_eye.swest().y);
		r_eye.resize(2 * d / 3);
		r_eye.move(neast().x - r_eye.radius() * 2 - 2 * d - r_eye.swest().x, neast().y - r_eye.radius() - 2 * d - r_eye.swest().y);
		mouth.resize(d);
		mouth.move(swest().x - mouth.swest().x + 2 * d, swest().y - mouth.swest().y + h / 4);

	}
};
myshape::myshape(point a, point b)
	: rectangle(a, b),	//Инициализация базового класса
	w(neast().x - swest().x + 1), // Инициализация данных
	h(neast().y - swest().y + 1), // - строго в порядке объявления!
	l_eye(point(swest().x + 3, neast().y - 1 - 1), 1),
	r_eye(point(neast().x - 1 * 2 - 1, neast().y - 1 - 1), 1),
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
	MoveWindow(console, r.left, r.top, XMAX * 10, YMAX * 10, TRUE);

	setlocale(LC_ALL, "Rus");
	screen_init();
	//== 1.Объявление набора фигур ==
	hat_circle hat(point(1, 1), point(15, 7));
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
	face.move(-8, -9);
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
