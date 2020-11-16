#include "word.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int Set::N = 26, Set::cnt = 0, Set::debug = 0;
const long q0 = 1;

char* generate_union()
{
    int m = rand() % 26;
    int n = 0;
    char* set = new char[26];
    for (int i = 0; i < m; i++)
    {
        if (rand() % 2) set[n++] = i + 'a';
    }
    set[n] = 0;
    return set;
}

int main()
{
    srand(time(nullptr));
    Set A('A'), B('B'), C('C'), D('D'), E;
    char*** in = new char** [q0];

    clock_t begin = clock();
    for (long q = 0; q < q0; q++) E = ((A & B) - C) | D;
    clock_t end = clock();

    cout << endl << "((A & B) \\ C) | D";
    E.Show();
    cout << "Time of one = " << (float)(end - begin) / CLK_TCK / q0 << endl;

    for (long j = 0; j < q0; j++)
    {
        in[j] = new char* [4];
        for (int i = 0; i < 4; i++)
        {
            in[j][i] = generate_union();
        }
    }
    begin = clock();
    for (long i = 0; i < q0; i++)
    {
        Set A('A',in[i][0]);
        Set B('B',in[i][1]);
        Set C('C',in[i][2]);
        Set D('D',in[i][3]);
        Set E;
        E = ((A & B) - C) | D;
    }
    end = clock();
    cout << "\nTime of random = " << (float)(end - begin) / CLK_TCK / q0 << endl;

    system("pause");
    return 0;
}