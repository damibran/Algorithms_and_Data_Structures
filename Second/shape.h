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

//== 2. ���������� ����� ==
struct shape : public Uncopyable
{ // ����������� ������� ����� "������"
	static std::list<shape*> shapes;// ������ ����� (���� �� ��� ������!)
	shape() { shapes.push_back(this); } //������ �������������� � ������
	~shape() { shapes.remove(this); 
	//std::cout << "Shape Destructed"; 
	}
	virtual point north() const = 0;	//����� ��� ��������
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;		//���������
	virtual void move(int, int) = 0;	//�����������
	virtual void resize(int) = 0;    	//��������� �������
};
std::list<shape*> shape::shapes;   // ���������� ������ �����
void shape_refresh(HANDLE hConsle, DWORD dwBytesWritten) // ����������� ���� ����� �� ������
{
	screen_clear();
	for (auto p : shape::shapes)
		p->draw(); //������������ ����������!!!
	screen_refresh(hConsle, dwBytesWritten);
}
