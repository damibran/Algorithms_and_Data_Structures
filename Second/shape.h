#pragma once
#include "screen.h"
#include <vector>
#include "glm/glm.hpp"

class Uncopyable
{
protected:
	Uncopyable() = default;
	~Uncopyable() = default;

	Uncopyable(const Uncopyable&)=delete;
	Uncopyable(const Uncopyable&&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&&) = delete;
};

class primitive
{
public:
	virtual void drawPrimitive(glm::mat3)=0;
};

class dot: public primitive
{
public:
	dot(point _p):p(glm::vec3(_p.x,_p.y,1)) {}
	virtual void drawPrimitive(glm::mat3 trans)override
	{
		int x = (trans * p)[0];
		int y = (trans * p)[1];
		gScreen.put_point(x, y);
	}
private:
	glm::vec3 p;
};

class edge : public  primitive
{
public:
	edge(point _p1, point _p2) : p1(glm::vec3(_p1.x, _p1.y, 1)), p2(glm::vec3(_p2.x, _p2.y, 1)) {}
	virtual void drawPrimitive(glm::mat3 trans)
	{
		int x0 = (trans * p1)[0];
		int y0 = (trans * p1)[1];

		glm::vec3 t = trans * p2;
		int x1 = (trans * p2)[0];
		int y1 = (trans * p2)[1];

		gScreen.put_line(x0, y0, x1, y1);
	}
private:
	glm::vec3 p1, p2;
};

//== 2. Библиотека фигур ==
struct shape
{ // Виртуальный базовый класс "фигура"
	std::vector<shape> childs;
	glm::mat3 transform=glm::mat3(1.0f);
	std::vector<std::shared_ptr<primitive>> visual;
	void addChild(shape& s)
	{		childs.push_back(s);	}
	void drawChild(glm::mat3 trans)
	{
		for (int i = 0; i < visual.size(); ++i)
		{
			visual[i]->drawPrimitive(trans * transform);
		}
		for (int i = 0; i < childs.size(); ++i)
		{
			childs[i].drawChild(trans*transform);
		}
	}
};

void shape_refresh() // Перерисовка всех фигур на экране
{
	//gScreen.screen_clear();
	//for (auto p : shape::shapes)
	//	p->draw(); //Динамическое связывание!!!
	//gScreen.screen_refresh();
}
