#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Set
{
private:
	long int k;
	char S;
public:

	static int N, cnt;

	Set& operator = (const Set& B);
	Set& operator |= (const Set&);
	Set operator | (const Set&);
	Set& operator &= (const Set&);
	Set operator & (const Set&);
	Set& operator -= (const Set&);
	Set operator - (const Set&);
	Set(char);
	Set(string in);
	void Show();
	Set();
	~Set() {}
};

Set& Set::operator = (const Set& B)
{
	k = B.k;
	S = B.S + 1;
	return *this;
}

Set& Set::operator -= (const Set& B)
{
	k = k & (~B.k);
	S = B.S + 1;
	return *this;
}

Set Set::operator - (const Set& B)
{
	return (*this -= B);
}

Set& Set::operator |= (const Set& B)
{
	k = k | B.k;
	S = B.S + 1;
	return *this;
}

Set Set::operator | (const Set& B)
{
	return (*this |= B);
}

Set& Set::operator &= (const Set& B)
{
	k = k & B.k;
	S = B.S + 1;
	return *this;
}

Set Set::operator & (const Set& B)
{
	return (*this &= B);
}

Set::Set() {
	k = 0;
}

Set::Set(char S):S(S)
{
	k = 0;
	for (int i = 0; i < N; i++)
	{
		if (rand() % 2) k = k | 1<<i;
	}

	long int q = k;
	cout << S << " = [";
	for (int i = 0; i < 26; i++) {
		if (q % 2 != 0)
			cout << char('a' + i);
		q = q / 2;
	}
	cout << "]" << endl;
}

Set::Set(string in) {
	k = 0;
	for (char c : in)
		if (c != 0)
			k = k | (1 << (int(c) - 'a'));
}

void Set::Show()
{
	long int q = k;
	cout <<endl<< S << " = [";
	for (int i = 0; i < 26; i++) {
		if (q % 2 != 0)
			cout << char('a' + i);
		q = q / 2;
	}
	cout<<"]"<< endl;
}