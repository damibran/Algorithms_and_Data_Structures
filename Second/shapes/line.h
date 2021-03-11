#pragma once
#include "../shape.h"

class line : public shape {
	/* отрезок прямой ["w", "e"].
	   north( ) определяет точку "выше центра отрезка и так далеко
	   на север, как самая его северная точка", и т. п. */
protected:
	point w, e;
public:
	line(point a, point b) : w(a), e(b) { };
	line(point a, int L) : w(point(a.x + L - 1, a.y)), e(a) {  };
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point(e.x < w.x ? w.x : e.x, (w.y + e.y) / 2); }
	point west() const { return point(e.x < w.x ? e.x : w.x, (w.y + e.y) / 2); }
	point neast() const { return point(w.x < e.x ? e.x : w.x, e.y < w.y ? w.y : e.y); }
	point seast() const { return point(w.x < e.x ? e.x : w.x, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point(w.x < e.x ? w.x : e.x, e.y < w.y ? w.y : e.y); }
	point swest() const { return point(w.x < e.x ? w.x : e.x, e.y < w.y ? e.y : w.y); }
	void move(int a, int b) { w.x += a; w.y += b; e.x += a; e.y += b; }
	void draw()
	{
		try
		{
			gScreen.put_line(w, e);
		}
		catch (CantPutPoint err)
		{
			if (east().x >= gScreen.XMAX)
				move(gScreen.XMAX - east().x + 1, 0);
			else if (west().x < 0)
				move(-west().x, 0);
			if (north().y >= gScreen.XMAX)
				move(0, gScreen.XMAX - north().y - 1);
			else if (south().y < 0)
				move(0, -south().y);
		}
	}
	void resize(int d) // Увеличение длины линии в (d) раз
	{
		e.x += (e.x - w.x) * (d - 1);
		e.y += (e.y - w.y) * (d - 1);
	}
};