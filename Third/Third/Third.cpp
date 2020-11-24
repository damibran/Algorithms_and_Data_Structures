// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// Троичное | Прямая | В ширину | Количество вершин, имеющих предков

#include <iostream>
#include "Tree.h"
#include<time.h>

using namespace std;
int main()
{
	srand(time(0));

	printf("(Lable, depth, side)\n");
	Tree t('a', 'e', 7); 

	t.MakeTree();
	t.OutTree();
	int res = t.BFS();

	std::cout << "\nResult is : " << res-1;

	return 0;
}
