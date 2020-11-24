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

Node* Tree::MakeNode(char side, int depth)
{
	Node* v = nullptr;
	int Y = (depth < rand() % 6 + 1) && (num <= maxnum);
	//cout << "Node (" << num << ", " << depth << ", " << side << ")1/0: "; cin >> Y; // fill via keyboard
	if (Y) {
		v = new Node;
		v->d = num++;
		v->lft = MakeNode('L', depth + 1);
		v->mdl = MakeNode('M', depth + 1);
		v->rgt = MakeNode('R', depth + 1);
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
	if (r && c && (c < 80)) SCREEN[r - 1][c - 1] = v->d; // print metku
	if (r < maxrow) {
		if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r)); //left child
		if (v->mdl) OutNodes(v->mdl, r + 1, c);	//– mid child
		if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //right child
	}
}

template <class Item> class QUEUE
{
	Item* Q; int h, t, N;
public:
	QUEUE(int maxQ) : h(0), t(0), N(maxQ), Q(new Item[maxQ + 1]) { }
	int empty() const {
		return (h % N) == t;
	}
	void push(Item item)
	{
		Q[t++] = item;
		t %= N;
	}
	Item pop()
	{
		h %= N;
		return Q[h++];
	}
	~QUEUE()
	{
		delete[] Q;
	}
};

int Tree::BFS()
{
	const int MaxQ = 20; //максимальный размер очереди
	int count = 0;
	QUEUE < Node* > Q(MaxQ);  //создание очереди указателей на узлы
	Q.push(root); // QUEUE <- root поместить в очередь корень дерева 
	while (!Q.empty()) //пока очередь не пуста
	{
		Node* v = Q.pop();// взять из очереди,
		cout << v->d << '_'; count++; // выдать тег, счёт узлов 
		if (v->lft) Q.push(v->lft); // QUEUE <- (левый сын)
		if (v->mdl) Q.push(v->mdl);
		if (v->rgt) Q.push(v->rgt); // QUEUE <- (правый сын)
	}
	return count;
}