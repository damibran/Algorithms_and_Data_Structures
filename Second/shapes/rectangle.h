#pragma once
#include "../shape.h"

class rotatable : virtual public shape { //Фигуры, пригодные к повороту 
public:
	virtual void rotate_left() = 0;	//Повернуть влево
	virtual void rotate_right() = 0;	//Повернуть вправо
};
// Прямоугольник
class rectangle : public rotatable {
	/* nw ------ n ------ ne
	   |		       |
	   |		       |
	   w	   c            e
	   |		       |
	   |		       |
	   sw ------- s ------ se */
protected:
	point sw, ne;
public:
	rectangle(point a, point b) :sw(a), ne(b) { }
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point west() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(ne.x, sw.y); }
	point nwest() const { return point(sw.x, ne.y); }
	point swest() const { return sw; }
	void rotate_right() // Поворот вправо относительно se
	{
		int w = ne.x - sw.x, h = ne.y - sw.y; //(учитывается масштаб по осям)
		sw.x = ne.x - h * 2; ne.y = sw.y + w / 2;
	}
	void rotate_left() // Поворот влево относительно sw
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2; ne.y = sw.y + w / 2;
	}
	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
	}
	void resize(int d)
	{
		ne.x += (ne.x - sw.x) * (d - 1);
		ne.y += (ne.y - sw.y) * (d - 1);
	}
	void draw()
	{
		try
		{
			gScreen.put_line(nwest(), ne);   gScreen.put_line(ne, seast());
			gScreen.put_line(seast(), sw);   gScreen.put_line(sw, nwest());
		}
		catch (CantPutPoint err) {
			if (east().x >= gScreen.XMAX)
				move(gScreen.XMAX - east().x + 1, 0);
			else if (west().x < 0)
				move(-west().x, 0);
			if (north().y >= gScreen.YMAX)
				move(0, gScreen.YMAX - north().y - 1);
			else if (south().y < 0)
				move(0, -south().y);
		}
	}
};