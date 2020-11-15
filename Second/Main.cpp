#include "List.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int Set::N = 26, Set::cnt = 0;
const long q0 = 100000;


int main()
{
    srand(time(nullptr));
    Set A('A'), B('B'), C('C'), D('D'), E;

    clock_t begin = clock();
    for (long q = 0; q < q0; q++) E = ((A & B) - C) | D;
    clock_t end = clock();

    cout << endl << "((A & B) \\ C) | D";
    E.Show();
    cout << "Time of one = " << (float)(end - begin) / CLK_TCK / q0 << endl;

    system("pause");
    return 0;
}