#include <iostream>
#include "Tree.h"
#include<time.h>

using namespace std;
int main()
{
	srand(time(0));

	printf("(Lable, depth, parent, side)\n");
	Tree t('a', 'f', 7); 
	t.MakeTree();

	if (t.exist())
	{
		t.OutTree();
		int res = t.BFS();
		std::cout << "\nResult is : " << res;
	}
	else
		std::cout << "Tree is empty";
	

	return 0;
}
