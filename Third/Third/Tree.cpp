// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(char nm, char mnm, int mxr) :
	num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr),
	SCREEN(new char* [maxrow])
{
	for (int i = 0; i < maxrow; i++) SCREEN[i] = new char[80];
}

Tree :: ~Tree() {
	for (int i = 0; i < maxrow; i++) delete[]SCREEN[i];
	delete[]SCREEN; delete root;
}

Node* Tree::MakeNode(int depth)
{
	Node* v = nullptr;
	int Y = (depth < rand() % 6 + 1) && (num <= 'z');
	//¬ариант: cout << "Node (" << num << ',' << depth << ")1/0: "; cin >> Y;
	if (Y) {
		v = new Node;
		v->d = num++;
		v->lft = MakeNode(depth + 1);
		v->rgt = MakeNode(depth + 1);
		v->mdl = MakeNode(depth + 1);
	}
	return v;
}

void Tree::OutTree()
{
	clrscr();
	OutNodes(root, 1, offset);
	for (int i = 0; i < maxrow; i++)
	{
		SCREEN[i][79] = '\0';
		cout << '\n' << SCREEN[i];
	}
	cout << '\n';
}

void Tree::clrscr()
{
	for (int i = 0; i < maxrow; i++)
		memset(SCREEN[i], '.', 80);
}

void Tree::OutNodes(Node* v, int r, int c)
{
	if (r && c && (c < 80)) SCREEN[r - 1][c - 1] = v->d; // вывод метки
	if (r < maxrow) {
		if (v->lft) OutNodes(v->lft, r + 1, c-(offset >> r)); //левый сын
		if (v->mdl) OutNodes(v->mdl, r + 1, c);	//Ц средний сын (если нужно)
		if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //правый сын
	}
}