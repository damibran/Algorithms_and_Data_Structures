// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include "Tree.h"
#include<time.h>

using namespace std;
int main()
{
	srand(time(0));

	Tree t('a', 'c', 10); 

	t.MakeTree();
	t.OutTree();

	return 0;
}
