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

	static int N, cnt,debug;

	Set& operator = (const Set& B);
	Set& operator |= (const Set&);
	Set operator | (const Set&);
	Set& operator &= (const Set&);
	Set operator & (const Set&);
	Set& operator -= (const Set&);
	Set operator - (const Set&);
	Set(char);
	Set(string in);
	Set(const Set& B);
	void Show();
	Set();
	~Set() {
		if (debug)
			printf("\ndeleting %c", S);
	}
};

Set& Set::operator = (const Set& B)
{
	if (debug)
		printf("\noperation = %c with %c", S, B.S);
	k = B.k;
	return *this;
}

Set& Set::operator -= (const Set& B)
{
	if (debug)
		printf("\noperation -= %c with %c", S, B.S);
	k = k & (~B.k);
	return *this;
}

Set Set::operator - (const Set& B)
{
	if (debug)
		printf("\noperation - %c with %c", S, B.S);
	Set C(*this);
	return (C -= B);
}

Set& Set::operator |= (const Set& B)
{
	if (debug)
		printf("\noperation |= %c with %c", S, B.S);
	k = k | B.k;
	return *this;
}

Set Set::operator | (const Set& B)
{
	if (debug)
		printf("\noperation | %c with %c", S, B.S);
	Set C(*this);
	return (C |= B);
}

Set& Set::operator &= (const Set& B)
{
	if (debug)
		printf("\noperation &= %c with %c", S, B.S);
	k = k & B.k;
	return *this;
}

Set Set::operator & (const Set& B)
{
	if (debug)
		printf("\noperation & %c with %c", S, B.S);
	Set C(*this);
	return (C &= B);
}

Set::Set():S('A' + cnt++) {
	if (debug)
		printf("\ncreating %c from default constructor", S);
	k = 0;
}

Set::Set(char S):S('A' + cnt++)
{
	if (debug)
		printf("\ncreating %c from char", S);
	k = 0;
	for (int i = 0; i < N; i++)
	{
		if (rand() % 2) k = k | 1<<i;
	}

	long int q = k;
	cout <<endl<< S << " = [";
	for (int i = 0; i < 26; i++) {
		if (q % 2 != 0)
			cout << char('a' + i);
		q = q / 2;
	}
	cout << "]" << endl;
}

Set::Set(const Set& B) : S('A' + cnt++)
{
	if (debug)
		printf("\ncreating copy %c of %c", S, B.S);

	k = B.k;
}

Set::Set(string in):S('A' + cnt++) {
	if (debug)
		printf("\ncreating %c from string", S);
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