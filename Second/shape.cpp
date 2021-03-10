//it is important that the above line be typed
//  BEFORE <windows.h> is included
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
// C������ ���������������� ������ - ����������

void up(shape& p, const shape& q) // ��������� p ��� q
{	//��� ������� �������, �� ���� ������! ������������ ����������!!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}

int main()
{
	SetConsoleActiveScreenBuffer(hConsle);

	setlocale(LC_ALL, "Rus");
	screen_init();

	//== 1.���������� ������ ����� ==
	hat_circle hat(point(1, 1), point(15, 7));
	line brim(point(5, 15), 17);
	face face(point(20, 52), point(32, 60));
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //�������� �������� �����

//== 2.���������� � ������ ==
	hat.rotate_right();
	hat.resize(3);
	brim.resize(3);
	face.resize(3);
	face.move(-8, -9);
	shape_refresh();
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //�������� ��������� ���������/���������
//== 2.1 ����������� ������ 
	shape_refresh();
	std::cout << "=== Fixed ===\n";
	std::cin.get(); //�������� ��������� ���������/���������
//== 3.������ ����������� ==
	//face.move(0, -10); // ���� - � �������� ���������
	up(brim, face);
	up(hat, brim);
	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //�������� ���������
	screen_destroy();
	return 0;
}
