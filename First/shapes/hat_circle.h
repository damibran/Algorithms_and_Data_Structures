#pragma once
#include "rectangle.h"
#include "circle.h"

class hat_circle : public rectangle
{
	int w, h;
	circle circle;
public:
	hat_circle(point a, point b) : rectangle(a, b),
		w(neast().x - swest().x),
		h(neast().y - swest().y),
		circle(point(south().x, east().y), w >= h ? h / 2 : w / 2) {
		std::cout << east().y;
	}
	void resize(float d);
	void move(int, int);
};

void hat_circle::move(int a, int b)
{
	rectangle::move(a, b);
	circle.move(a, b);
}

void hat_circle::resize(float d)
{
	rectangle::resize(d);
	circle.resize(d);
	circle.move(south().x - circle.south().x, east().y - circle.east().y);
}