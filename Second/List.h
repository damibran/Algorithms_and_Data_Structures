#pragma once
#include<string>



class Set {
private: 

	struct Node {
		char el;
		Node* next = nullptr;
		Node(char c, Node* n = nullptr) : el(c), next() { }
		~Node() { delete next; }
	};

	Node *first=nullptr;
	Node *last=nullptr;

public: 
	Set& operator |= (const Set&);
	Set operator | (const Set&); 
	Set& operator &= (Set& b);
	Set operator & (const Set&); 
	Set& operator -= (const Set&);
	Set operator - (const Set&);
	char* to_String(); 
	Set();
	Set(const Set&);
	Set(std::string in);
	~Set() { delete first; }
	void add(char c);
	int get_len();
	Node* delete_elem(Node* lst);
};

