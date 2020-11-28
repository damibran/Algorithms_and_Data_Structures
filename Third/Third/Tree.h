#pragma once

class Node {
	char d;
	Node* lft;
	Node* mdl;
	Node* rgt;
public:
	Node() : d(0) ,lft(nullptr), mdl(nullptr), rgt(nullptr) { }
	~Node() {
		if (lft) delete lft;
		if (mdl) delete mdl;
		if (rgt) delete rgt;
	}
	friend class Tree;
};

class Tree
{
	Node* root;
	char num, maxnum;
	int maxrow, offset;
	char** SCREEN;
	void clrscr();
	Node* MakeNode(char,char ,int depth);
	void OutNodes(Node* v, int r, int c);
	Tree(const Tree&) = delete;
	Tree(Tree&&) = delete;
	Tree operator = (const Tree&) const = delete;
	Tree operator = (Tree&&) const = delete;

public:

	Tree(char num, char maxnum, int maxrow);
	~Tree();
	void MakeTree()
	{
		root = MakeNode('0','M',0);
	}
	bool exist() { return root != nullptr; }
	int BFS();
	void OutTree();
};