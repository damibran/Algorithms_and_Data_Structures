#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Set
{
private:
	static int N, cnt;
	int n = 0;
	char S, *A;
public:
	Set& operator |= (const Set &);
	Set operator | (const Set &) const;
	Set& operator &= (const Set &);
	Set operator & (const Set &) const;
	Set& operator -= (const Set &);
	Set operator - (const Set &) const;
	int power() { return n; }
	void Show();
	Set(char);
	Set();
	Set(string);
	Set(const Set &);
	Set& operator = (const Set &);
	~Set() { delete[] A; }
};

Set& Set::operator &= (const Set& B)
{
    Set C(*this);
    n=0;
    for(int i=0;i<C.n;++i)
    {
        for(int j=0;j<B.n;++j)
        {
            if(C.A[i]==B.A[j]) A[n++]=C.A[i];
        }
    }
    A[n]=0;
    return *this;
}

Set Set::operator & (const Set& B) const
{
    Set C(*this);
    return (C &= B);
}

Set& Set::operator |= (const Set& B)
{
    Set C(*this);
	int f;
	for (int i = 0; i < B.n; ++i)
	{
		f = 0;
		for (int j = 0; j < C.n; ++j)
		{
			if (B.A[i] == C.A[j])  f = 1;
		}
		if (f == 0) A[n++] = B.A[i];
	}
    A[n]='\0';
    return *this;
}

Set Set::operator | (const Set& B) const
{
    Set C(*this);
    return (C |= B);
}

Set& Set::operator -= (const Set& B)
{
    Set C(*this);
    int f;
	n=0;
	for (int i = 0; i < C.n; ++i)
	{
		f=0;
		for (int j = 0; j < B.n; ++j)
		{
			if (C.A[i] == B.A[j]) f=1;
		}
		if(f==0) A[n++]=C.A[i];
	}
    A[n]=0;
    return *this;
}

Set Set::operator - (const Set& B) const
{
    Set C(*this);
    return (C -= B);
}

void Set::Show()
{
    cout << endl << S << " = ((A & B) \\ C) | D = [" << A << "]" << endl;
}

Set::Set(): n(0), S('A'+cnt++), A(new char[N+1]) {A[0]=0;}

Set::Set(string set): S('A'+cnt++), n(0), A(new char[N+1])
{
	for(int i=0;i<set.length();++i) A[n++]=set[i];
	A[n]=0;
} 

Set::Set(char): S('A'+cnt++), n(0), A(new char[N+1])
{
    for(int i=0;i<N;i++)
    {
        if(rand()%2) A[n++]=i+'a';
    }
    A[n]=0;
    cout << '\n' << S << " = [" << A << "]";
}

Set::Set(const Set& B): S('A'+cnt++), n(B.n), A(new char[N+1])
{
    char *dst(A), *src(B.A);
    while(*dst++=*src++);
}

Set& Set::operator = (const Set& B)
{
    if(this != &B)
    {
        char *dst(A), *src(B.A);
        n = B.n;
        while(*dst++ = *src++);
        S = 'A'+cnt++;
    }
    return *this;
}