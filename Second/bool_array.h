#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Set
{
private:
	bool S[26];
	char A;
public:
	static int N, cnt;

	Set& operator = (const Set& B);
	Set& operator |= (const Set&);
	Set operator | (const Set&);
	Set& operator &= (const Set&);
	Set operator & (const Set&);
	Set& operator -= (const Set&);
	Set operator - (const Set&);
	Set(string in);
	Set(char S);
	void Show();
	Set();
	~Set() {}
};

Set& Set::operator = (const Set& B)
{

	if (this != &B)
	{
		A = B.A+1;
		for (int i = 0; i < 26; i++)
			if (B.S[i])
				S[i] = 1;
	}
	return *this;
}

Set& Set::operator -= (const Set& B)
{
	A = B.A + 1;
	for (int i = 0; i < 26; i++)
		S[i] = (S[i] && !B.S[i]);
	return *this;
}

Set Set::operator - (const Set& B)
{
	return (*this -= B);
}

Set& Set::operator |= (const Set& B)
{
	A = B.A + 1;
	for (int i = 0; i < 26; i++)
		S[i] = S[i] || B.S[i];
	return *this;
}

Set Set::operator | (const Set& B)
{
	return (*this |= B);
}

Set& Set::operator &= (const Set& B)
{
	A = B.A + 1;
	for (int i = 0; i < 26; i++)
		S[i] = bool(S[i] && B.S[i]);
	return *this;
}

Set Set::operator & (const Set& B)
{
	return (*this &= B);
}

Set::Set() {
	for (int i = 0; i < 26; i++) {
		S[i] = false;
	}
}

Set::Set(char A):A(A)
{
	for (int i = 0; i < 26; i++) {
		S[i] = false;
	}

	for (int i = 0; i < N; i++)
	{
		if (rand() % 2) S[i] = true;
	}

	cout << A << " = [";
	for (int i = 0; i < 26; i++)
		if (S[i])
			cout << char(i + 'a');
	cout << "]" << endl;
}

Set::Set(string in) {
	for (int i = 0; i < 26; i++) {
		S[i] = false;
	}
	for (char c : in)
		if (c != 0)
			S[int(c) - 'a'] = true;
}

void Set::Show()
{
	cout << endl << A << " = [";
	for (int i = 0; i < 26; i++)
		if (S[i])
			cout << char(i+ 'a');
	cout << "]" << endl;
}