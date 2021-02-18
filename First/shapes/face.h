#pragma once
#include "rectangle.h"
#include "circle.h"
#include "line.h"

class face : public rectangle { // ћо€ фигура я¬Ћя≈“—я
	int w, h;			             //        пр€моугольником
	circle l_eye; // левый глаз
	circle r_eye; // правый глаз
	line mouth; // рот
public:
	face(point, point);
	void draw();
	void move(int, int);
	void resize(float d)
	{
		w *= d;
		h *= d;
		rectangle::resize(d);
		l_eye.resize(2 * d / 3);
		l_eye.move(swest().x + 2 * d - l_eye.swest().x, neast().y - l_eye.radius() - 2 * d - l_eye.swest().y);
		r_eye.resize(2 * d / 3);
		r_eye.move(neast().x - r_eye.radius() * 2 - 2 * d - r_eye.swest().x, neast().y - r_eye.radius() - 2 * d - r_eye.swest().y);
		mouth.resize(d);
		mouth.move(swest().x - mouth.swest().x + 2 * d, swest().y - mouth.swest().y + h / 4);

	}
};
face::face(point a, point b)
	: rectangle(a, b),	//»нициализаци€ базового класса
	w(neast().x - swest().x + 1), // »нициализаци€ данных
	h(neast().y - swest().y + 1), // - строго в пор€дке объ€влени€!
	l_eye(point(swest().x + 3, neast().y - 1 - 1), 1),
	r_eye(point(neast().x - 1 * 2 - 1, neast().y - 1 - 1), 1),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{ }
void face::draw()
{
	rectangle::draw(); // онтур лица (глаза и нос рисуютс€ сами!) 
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b)); // Ќос Ц существует только на рисунке!
}
void face::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b);
	r_eye.move(a, b);
	mouth.move(a, b);
}
