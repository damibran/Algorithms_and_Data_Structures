#pragma once
#include<string>
#include<iostream>


class Set {
private:

	struct Node {
		char el;
		Node* next = nullptr;
		Node(char c, Node* n = nullptr) : el(c), next() { }
		~Node() { delete next; }


		/*void* operator new(size_t size) {
			return malloc(size);
		}

		void operator delete(void* p) {
			free(p);
		}*/
	};

	char S;

	Node* first = nullptr;
	Node* last = nullptr;

public:
	static int N, cnt, debug;

	Set& operator |= (const Set&);
	Set operator | (const Set&)const;
	Set& operator &= (const Set& b);
	Set operator & (const Set&)const;
	Set& operator -= (const Set&);
	Set operator - (const Set&)const;
	Set& operator= (const Set&);
	char* to_String();
	Set() :S('A' + cnt++) 
	{
		if (debug)
			printf("\ncreating %c with default constructor", S);
	};
	Set(const Set&);
	Set(std::string in);
	~Set() { 
		if (debug)
			printf("\ndeleting %c", S);
		delete first; 
	}
	Set(char S);
	void add(char c);
	int get_len();
	Node* delete_elem(Node* lst);
	void Show();

};

char* Set::to_String()
{
	Node* cur;

	char* res = new char[27];
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

void Set::Show()
{
	char* res;
	res = to_String();
	std::cout << std::endl << S << " = [" << res << "]" << std::endl;
	delete res;
}

Set& Set::operator &= (const Set& B)
{
	if (debug)
		printf("\noperation &= %c with %c", S, B.S);

	bool flag = false;
	Set::Node* curB;
	Set::Node* curT = this->first;

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
		if (curT != nullptr)
			curT = curT->next;
	}

	return (*this);
}

Set Set::operator & (const Set& B) const
{
	if (debug)
		printf("\noperation & %c with %c", S, B.S);
	Set C(*this);
	return (C &= B);
}

Set& Set::operator-= (const Set& B)
{
	Node* curT = this->first;
	Node* curB;
	if (debug)
		printf("\noperation -= %c with %c", S, B.S);

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
		if (curT != nullptr)
			curT = curT->next;
	}

	return (*this);
}

Set Set::operator - (const Set& B) const
{
	if (debug)
		printf("\noperation - %c with %c", S, B.S);
	Set C(*this);
	return (C -= B);
}

Set& Set::operator |= (const Set& B)
{
	bool flag = false;
	Set::Node* curB = B.first;
	Set::Node* curT;

	if (debug)
		printf("\noperation |= %c with %c", S, B.S);

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
	if (debug)
		printf("\noperation | %c with %c", S, B.S);
	Set C(*this);
	return (C |= B);
}

Set& Set::operator= (const Set& B)
{
	Node* curB = B.first;
	if (debug)
		printf("\noperation = %c with %c", S, B.S);

	if (this != &B)
	{
		if (first != nullptr)
		{
			delete (this->first);
			first = nullptr;
			last = nullptr;
		}
		while (curB != nullptr)
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
			while (temp->next != lst)
			{
				temp = temp->next;
			}
			temp->next = lst->next;
		}
		free(lst);
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

Set::Set(const Set& a): S('A' + cnt++) {

	Node* curA = a.first;
	if (debug)
		printf("\ncreating copy %c of %c", S, a.S);
	while (curA != nullptr)
	{
		add(curA->el);
		curA = curA->next;
	}
}

Set::Set(char S) : S('A' + cnt++)
{
	if (debug)
		printf("\ncreating %c from char", S);
	for (int i = 0; i < N; i++)
	{
		if (rand() % 2) add('a' + i);
	}

	char* res = to_String();

	std::cout << '\n' << S << " = [" << res << "]";

	delete[] res;
}

Set::Set(std::string in) : S('A'+cnt++) {
	if (debug)
		printf("\ncreating %c from string", S);

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