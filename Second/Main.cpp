#include"List.h"
#include<iostream>

int main()
{
	Set a("abc");
	char* hz = a.to_String();
	std::cout << hz;
	system("pause");
	return 0;
}