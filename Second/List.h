#pragma once
#include<string>



class Set {
private: 

    struct Node {
        char el;
        Node* next = nullptr;
        Node(char c, Node* n = nullptr) : el(c),next() { }
		~Node() { delete next; }
    };

	static int N, cnt; 
	int n=0; 
	Node *first=nullptr;
	Node *last=nullptr;

public: 
	Set operator |= (const Set&) const;
	Set operator | (const Set&) const; 
	Set& operator &= (Set& b);
	Set operator & (const Set&) const; 
	Set operator -= (const Set&) const;
	Set operator - (const Set&) const;
	char* to_String(); 
	int power() { return n; } 
	Set();
	Set(const Set&);
	Set(std::string in);
	~Set() { delete first; }
	void add(char c);
};

