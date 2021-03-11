#pragma once
#include "screen.h"
#include <list>

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

//== 2. Библиотека фигур ==
struct shape : public Uncopyable
{ // Виртуальный базовый класс "фигура"
	static std::list<shape*> shapes;// Список фигур (один на все фигуры!)
	shape() { shapes.push_back(this); } //Фигура присоединяется к списку
	~shape() { shapes.remove(this); 
	//std::cout << "Shape Destructed"; 
	}
	virtual point north() const = 0;	//Точки для привязки
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;		//Рисование
	virtual void move(int, int) = 0;	//Перемещение
	virtual void resize(int) = 0;    	//Изменение размера
};
std::list<shape*> shape::shapes;   // Размещение списка фигур
void shape_refresh(HANDLE hConsle, DWORD dwBytesWritten) // Перерисовка всех фигур на экране
{
	screen_clear();
	for (auto p : shape::shapes)
		p->draw(); //Динамическое связывание!!!
	screen_refresh(hConsle, dwBytesWritten);
}
