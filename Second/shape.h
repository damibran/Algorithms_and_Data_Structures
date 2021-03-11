#pragma once
#include "screen.h"
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "primitive.h"

class Uncopyable
{
protected:
	Uncopyable() = default;
	~Uncopyable() = default;

	Uncopyable(const Uncopyable&) = delete;
	Uncopyable(const Uncopyable&&) = delete;
	Uncopyable& operator=(const Uncopyable&) = delete;
	Uncopyable& operator=(const Uncopyable&&) = delete;
};


//== 2. Библиотека фигур ==
struct shape
{ // Виртуальный базовый класс "фигура"
	std::vector<shape*> childs;
	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scaleM = glm::mat4(1.0f);
	std::vector<primitive*> visual;
	shape(shape&) = delete;
	shape() = default;
	void addChild(shape& s)
	{
		childs.push_back(&s);
	}
	void drawChild(glm::mat4 trans)
	{
		glm::mat4 transformM = position * rotation * scaleM;
		for (int i = 0; i < visual.size(); ++i)
		{
			visual[i]->drawPrimitive(trans * transformM);
		}
		for (int i = 0; i < childs.size(); ++i)
		{
			childs[i]->drawChild(trans * transformM);
		}
	}
	void translate(glm::mat4 trans)
	{
		position = trans * position;
	}
	void rotate(glm::mat4 trans)
	{
		rotation = trans * rotation;
	}
	void scale(glm::mat4 trans)
	{
		scaleM = trans * scaleM;
	}
};

