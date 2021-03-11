#pragma once
#include "screen.h"
#include "glm/glm.hpp"

class primitive
{
public:
	virtual void drawPrimitive(glm::mat4) = 0;
};

class dot : public primitive
{
public:
	dot(glm::vec2 _p) :p(glm::vec4(_p.x, _p.y, 1, 1)) {}
	virtual void drawPrimitive(glm::mat4 trans)override
	{
		int x = (trans * p)[0];
		int y = (trans * p)[1];
		gScreen.put_point(x, y);
	}
private:
	glm::vec4 p;
};

class edge : public  primitive
{
public:
	edge(glm::vec2 _p1, glm::vec2 _p2) : p1(glm::vec4(_p1.x, _p1.y, 1, 1)), p2(glm::vec4(_p2.x, _p2.y, 1, 1)) {}
	virtual void drawPrimitive(glm::mat4 trans)
	{
		int x0 = (trans * p1)[0];
		int y0 = (trans * p1)[1];

		glm::vec3 t = trans * p2;
		int x1 = (trans * p2)[0];
		int y1 = (trans * p2)[1];

		put_line(x0, y0, x1, y1);
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
			gScreen.put_point(x0, y0);
			if (x0 == x1 && y0 == y1) break;
			if (eps <= xcrit) x0 += dx, eps += two_b;
			if (eps >= a || a < b) y0 += dy, eps -= two_a;
		}
	}
private:
	glm::vec4 p1, p2;
};