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

Set& Set::operator &= (Set& B)  
{
	Set T(*this);

	Node* curT = T.first;
	Node* prevThis=nullptr;
	Node* curThis = this->first;

	if (curT != nullptr) {
		while (curT != nullptr)
		{
			Node* curB = B.first;
			while (curB != nullptr)
			{
				if (curB->el == curT->el)
				{
					curThis->el = curT->el;
					prevThis = curThis;
					curThis = curThis->next;
				}
				curB = curB->next;
			}
			curT = curT->next;
		}
		if (curThis != nullptr && curThis != this->first)
		{
			delete curT;
			this->last = prevThis;
			prevThis->next = nullptr;
		}
	}

	return *this;
}

Set::Set(const Set& a) {

	Node *curA = a.first;
	while (curA != nullptr)
	{
		add(curA->el);
		curA = curA->next;
	}
}

Set::Set(std::string in) {
	
	for(int i=0;i< in.length();i++)
		add(in[i]);
}

void Set::add(char c){
	if (this->first != nullptr) {
		Node *_new = new Node(c);
		if (last == nullptr)
			last = first;
		last->next = _new;
		last = _new;
	}
	else{
		Node* _first = new Node(c);
		first = _first;
		first->next = nullptr;
	}
}