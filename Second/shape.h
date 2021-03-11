#pragma once
#include "screen.h"
#include <vector>
#include "glm/glm.hpp"
#include "primitive.h"

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


//== 2. ���������� ����� ==
struct shape
{ // ����������� ������� ����� "������"
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

void shape_refresh() // ����������� ���� ����� �� ������
{
	//gScreen.screen_clear();
	//for (auto p : shape::shapes)
	//	p->draw(); //������������ ����������!!!
	//gScreen.screen_refresh();
}
