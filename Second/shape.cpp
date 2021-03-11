//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include "screen.h"
#include "shape.h"
#include <vector>
#include "shapes/rectangle.h"
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	setlocale(LC_ALL, "Rus");
	//== 1.���������� ������ ����� ==
	shape worldObj;

	std::vector<std::unique_ptr<primitive>> t;
	t.emplace_back(new edge({ 0,0 }, { 0,10 }));
	t.emplace_back(new edge({ 0,10 }, { 10,10 }));
	t.emplace_back(new edge({ 10,10 }, { 10,0 }));
	t.emplace_back(new edge({ 0,0 }, { 10,0 }));

	rectangle rec(std::move(t));

	glm::mat3 viewM(1.0f);
	
	worldObj.addChild(rec);
	
	while (1) 
	{
		glm::mat3 t(1.0f);
		rec.transform
		worldObj.drawChild(viewM);

		gScreen.screen_refresh();

		Sleep(100);
	}

	return 0;
}
