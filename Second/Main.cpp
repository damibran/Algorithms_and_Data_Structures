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

using namespace std;

int main()
{
	clock_t start, stop;
	// A&&B\\C||D
	srand(time(0));

	const int N = 1000000;
	bool debug = false;

	char*** in = new char** [N];

	for (int j = 0; j < N; j++) {
		in[j] = new char* [4];
		for (int i = 0; i < 4; i++)
		{
			in[j][i] = generate_union();
		}

	}

	cout << "FUCK";

	start = clock();
	for (int i = 0; i < N; i++)
	{
		Set a(in[i][0]);
		if (debug)
			cout << endl << "a : " << in[i][0] << endl;
		Set b(in[i][1]);
		if (debug)
			cout << "b : " << in[i][1] << endl;
		Set c(in[i][2]);
		if (debug)
			cout << "c : " << in[i][2] << endl;
		Set d(in[i][3]);
		if (debug)
			cout << "d : " << in[i][3] << endl;
		Set e;

		e = ((a & b) - c) | d;

		if (debug) {
			char* res;
			res = e.to_String();
			cout << "res : " << in[i][3] << endl;
			delete res;
		}

	}
	stop = clock();
	cout << "\nTime : " << ((float)(stop - start) / CLK_TCK) / N << endl;

	system("pause");
	return 0;
}