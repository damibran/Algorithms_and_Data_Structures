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

Set& Set::operator &= (Set& b)  {

}



Set::Set(std::string in) {
	
	for(int i=0;i< in.length();i++)
		add(in[i]);
}

void Set::add(char c){
	if (this->last != nullptr) {
		Node *_new = new Node(c);
		last->next = _new;
		last = _new;
	}
	else{
		Node* _first = new Node(c);
		first = _first;
		first->next = _first;
		last = _first;
	}
}