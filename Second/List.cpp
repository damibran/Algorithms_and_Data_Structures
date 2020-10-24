#include "List.h"
#include<iostream>

char* Set::to_String()
{
	Node* cur;

	char* res = new char[26];
	int l = 0;
	char c;

	for (int i = 0; i < 26; i++)
	{
		cur = this->first;

		c = 'a' + i;
		while (cur != nullptr)
		{
			if (cur->el == c)
				res[l++] = cur->el;

			cur = cur->next;
		}
	}
	res[l] = '\0';
	return res;
}

Set& Set::operator &= (const Set& B)
{
	bool flag = false;
	Set::Node* curB;
	Set::Node* curT=this->first;

	while (curT != nullptr) 
	{
		curB = B.first;
		flag = false;
		while (curB != nullptr)
		{
			if (curB->el == curT->el)
				flag = true;
			curB = curB->next;
		}
		if (!flag)
			curT = this->delete_elem(curT);
		if(curT!=nullptr)
			curT = curT->next;
	}

	return (*this);
}

Set Set::operator & (const Set& B) const 
{
	Set C(*this);
	return (C &= B);
}

Set& Set::operator-= (const Set& B)
{
	Node* curT = this->first;
	Node* curB;

	while (curT != nullptr)
	{
		curB = B.first;
		while (curB != nullptr)
		{
			if (curT != nullptr && (curT->el == curB->el))
			{
				curT = this->delete_elem(curT);
			}
			curB = curB->next;
		}
		if(curT!=nullptr)
			curT = curT->next;
	}

	return (*this);
}

Set Set::operator - (const Set& B) const
{
	Set C(*this);
	return (C -= B);
}

Set& Set::operator |= (const Set& B)
{
	bool flag = false;
	Set::Node* curB = B.first;
	Set::Node* curT;

	while (curB != nullptr)
	{
		curT = this->first;
		flag = false;
		while (curT != nullptr)
		{
			if (curT->el == curB->el)
				flag = true;

			curT = curT->next;
		}
		if (!flag)
			this->add(curB->el);
		curB = curB->next;
	}
	return (*this);
}

Set Set::operator | (const Set& B) const
{
	Set C(*this);
	return (C |= B);
}

Set& Set::operator= (const Set& B) 
{
	Node* curB=B.first;

	if (this != &B)
	{
		while(curB!=nullptr)
		{
			this->add(curB->el);
			curB = curB->next;
		}
	}
	return *this;
}

Set::Node* Set::delete_elem(Node* lst)
{
	Node* temp = nullptr;
	if (this->get_len() != 0) {
		if (lst == this->first) {
			this->first = lst->next;
			temp = this->first;
		}
		else
		{
			temp = this->first;
			while (temp->next != lst) // просматриваем список начиная с корня
			{ // пока не найдем узел, предшествующий lst
				temp = temp->next;
			}
			temp->next = lst->next; // переставляем указатель	
		}
		free(lst); // освобождаем память удаляемого узла
	}
	return(temp);
}

int Set::get_len()
{
	Node* cur;
	int c = 0;
	cur = this->first;
	while (cur->next != nullptr)
	{
		cur = cur->next;
		c++;
	}

	return c;
}

Set::Set(const Set& a) {

	Node* curA = a.first;
	while (curA != nullptr)
	{
		add(curA->el);
		curA = curA->next;
	}
}

Set::Set(std::string in) {

	for (int i = 0; i < in.length(); i++)
		add(in[i]);
}

void Set::add(char c) {
	if (this->first != nullptr) {
		Node* _new = new Node(c);
		if (last == nullptr)
			last = first;
		last->next = _new;
		last = _new;
	}
	else {
		Node* _first = new Node(c);
		first = _first;
		first->next = nullptr;
	}
}