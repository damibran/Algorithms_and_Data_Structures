#pragma once
#include "../shape.h"

class circle : public shape
{
	point center;
	int R;
public:
	circle(point c, int r) : center(c), R(r) {}

	point north() const { return point(center.x, center.y + R); }
	point south() const { return point(center.x, center.y - R); }
	point east() const { return point(center.x + R, center.y); }
	point west() const { return point(center.x - R, center.y); }
	point neast() const { return point(center.x + R, center.y + R); }
	point seast() const { return point(center.x + R, center.y - R); }
	point nwest() const { return point(center.x - R, center.y + R); }
	point swest() const { return point(center.x - R, center.y - R); }
	void draw();		//Рисование
	void move(int, int);	//Перемещение
	void resize(float);    	//Изменение размера

	int radius()
	{
		return R;
	}
};
void circle::draw() //Алгоритм Брезенхэма для окружностей
{   //(выдаются два сектора, указываемые значением reflected)
	int x0 = center.x, y0 = center.y;
	int radius = R;
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
void circle::resize(float d)
{
	R *= d;
}
void circle::move(int a, int b)
{
	center.x += a;
	center.y += b;
}