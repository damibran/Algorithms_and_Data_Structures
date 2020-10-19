#include"List.h"
#include<iostream>

int main()
{
	Set a("cba");
	char* hz = a.to_String();
	std::cout << hz << std::endl;
	system("pause");
	return 0;
}