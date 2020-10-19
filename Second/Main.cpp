#include"List.h"
#include<iostream>
#include <time.h>


char* generate_union() {
	int m = rand() % 26;
	char* S = new char[26];
	char* St = new char[26];
	for (int i = 0; i < m; i++)
		S[i] = 49 + rand() % 0x1A + '0';
	int l = 0;
	for (int i = 0; i < m; i++) {
		bool flag = true;
		for (int j = 0; j < m; j++)
			if (i - j != 0 && S[i] == S[j]) flag = false;
		if (flag) {
			St[l++] = S[i];
		}
	}
	St[l] = '\0';
	delete[] S;
	return St;
}

int main()
{
	srand(time(0));
	
	for (int i = 0; i < 100; i++) {

		char* in = new char(26);
		in = generate_union();
		std::cout << "a: " << in<< std::endl;
		Set a(in);
		delete in;

		in = new char(26);
		in = generate_union();
		std::cout << "b: " << in << std::endl;
		Set b(in);
		delete in;

		a &= b;

		std::cout <<"res: "<< a.to_String() << std::endl << std::endl;
	}

	system("pause");
	return 0;
}