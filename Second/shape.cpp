//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include "screen.h"
#include "shape.h"
#include <vector>
#include "shapes/rectangle.h"
#include <chrono>

int main()
{
	setlocale(LC_ALL, "Rus");
	//== 1.Объявление набора фигур ==
	shape worldObj;

	std::vector<edge> recBuff = {
		{{ -5,5 }, { 5,5 }},
		{{ 5,5 }, { 5,-5 }},
		{{ 5,-5 }, { -5,-5 }},
		{{ -5,-5 }, { -5,5 } }
	};


	rectangle rec;
	rec.setBuffer(recBuff);

	glm::mat3 viewM(1.0f);

	worldObj.addChild(rec);

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	rec.translate(glm::translate(glm::mat4(1.0f), glm::vec3(15, 15, 0)));
	rec.scale(glm::mat4(3));

	while (1)
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elpasedTime = tp2 - tp1;
		tp1 = tp2;
		float deltaTime = elpasedTime.count();

		gScreen.screen_clear();
		time_t ltime;
		time(&ltime);
		rec.rotate(glm::rotate(glm::mat4(1.0f), 3 * deltaTime, glm::vec3(0, 0, 1)));

		worldObj.drawChild(viewM);

		gScreen.screen_refresh();

		//Sleep(100);
	}

	return 0;
}
