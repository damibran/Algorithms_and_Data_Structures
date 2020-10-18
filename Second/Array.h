#pragma once
#include<string>

class Set {
private:
	static int N, cnt;
	int n = 0;
	char el = '#';
	Set* next = nullptr;
public:
	Set operator |= (const Set&) const;
	Set operator | (const Set&) const;
	Set& operator &= (const Set&) const;
	Set operator & (const Set&) const;
	Set operator -= (const Set&) const;
	Set operator - (const Set&) const;
	char* to_String();
	int power() { return n; }
	Set(char  e, Set* n = nullptr) : el(e), next(n) { }
	Set();
	Set(const Set&);
	Set(std::string in);
	~Set() { delete next; }
	void add(char c);
};