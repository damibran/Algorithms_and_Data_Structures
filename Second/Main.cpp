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
	char* in;
	for (int i = 0; i < 1000000; i++) {

		in = generate_union();
		//std::cout << "a: " << in<< std::endl;
		Set a(in);
		delete[] in;

		in = generate_union();
		//std::cout << "b: " << in << std::endl;
		Set b(in);
		delete[] in;

		a -= b;

		//char* res = a.to_String();

		//std::cout <<"res: "<< res << std::endl << std::endl;
		//delete res;
	}

	system("pause");
	return 0;
}