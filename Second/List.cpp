#include "List.h"
#include<iostream>

char* Set::to_String()
{
	Set* a;
	Set* head = this;
	char* res = new char[26];
	int l = 0;
	char c;

	for (int i = 0; i < 26; i++)
	{
		a = head->next;

		c = 'a' + i;
		while (a != nullptr)
		{
			if (a->el == c)
				res[l++] = a->el;

			a = a->next;
		}
	}
	res[l] = '\0';
	return res;
}

Set& Set::operator&= (const Set& B) const
{
	Set A(*this);
	Set* E = new Set();

	while (&A != nullptr)
	{
		Set* b = B.next;
		while (b != nullptr)
		{
			if (A.el == b->el)
				E->add(A.el);

			b = b->next;
		}
		A = *(A.next);
	}

	return *E;
}

Set Set :: operator & (const Set& B) const
{
	Set C(*this);
	return (C &= B);
}


Set::Set(std::string in)
{
	for (int i = 0; i < in.length(); i++)
		add(in[i]);
}

void Set::add(char c)
{
	Set* wen;
	wen = new Set(c, this->next);
	this->next = wen;
}