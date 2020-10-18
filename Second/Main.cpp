#include"List.h"
#include<iostream>

int main()
{
	Set a("abcde");
	Set b("cd");
	Set e;
	char* hz = a.to_String();
	std::cout << hz << std::endl;
	e = a & b;
	char* zz = e.to_String();
	std::cout << zz << std::endl;
	system("pause");
	return 0;
}