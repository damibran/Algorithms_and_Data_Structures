#include<iostream>
#include<time.h>
#include<stack>
#include<vector>

//https://graphonline.ru/create_graph_by_matrix

const int maxSize = 10;

class Graph
{
private:
	int m_size;
	//int used[maxSize];
	int arr[maxSize][maxSize];

public:
	Graph(int);
	Graph(int, int);
	Graph(int[5][5]);
	void print();
	void DFS_cycle(int);
};

Graph::Graph(int size)
{
	for (int i = 0; i < maxSize; ++i)
	{
		for (int j = 0; j < maxSize; ++j)
		{
			arr[i][j] = 0;
		}
	}

	m_size = size + (rand() % (maxSize - size));
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			if (rand() % 2 == 0)
			{
				arr[i][j] = 1;
			}
		}
	}
}

Graph::Graph(int size, int edges)
{
	for (int i = 0; i < maxSize; ++i)
	{
		for (int j = 0; j < maxSize; ++j)
		{
			arr[i][j] = 0;
		}
	}

	m_size = size;

	while (edges > 0)
		for (int i = 0; i < m_size; ++i)
		{
			for (int j = 0; j < m_size; ++j)
			{
				if (j == i) continue;
				if (rand() % 2 == 0&&edges>0)
				{
					arr[i][j] = 1;
					edges -= 1;
				}
			}
		}
}

void Graph::print()
{
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Graph::DFS_cycle(int v)
{
	std::stack<int> Stack;
	std::vector<int> path;
	std::vector<int> nodes(m_size); // ������� �����

	for (int i = 0; i < m_size; ++i) // ������� ��� ������� ����� 0
		nodes[i] = 0;

	Stack.push(v); // �������� � ������� ������ �������
	while (!Stack.empty())
	{ // ���� ���� �� ����
		int node = Stack.top(); // ��������� �������
		Stack.pop();

		path.push_back(node);

		//if (nodes[node] == 2) continue;
		nodes[node] = 2; // �������� �� ��� ����������

		if (node == v)
			nodes[node] = 3;

		bool flag = false;

		for (int j = m_size - 1; j >= 0; --j)
		{ // ��������� ��� ��� ��� ������� �������
			if (arr[node][j] == 1 && arr[j][node] == 0 && nodes[j] == 3)
			{
				std::cout << std::endl;
				for (int i = 0; i < path.size(); ++i)
					std::cout << path[i] << "-";
				std::cout << j;
			}
			else if (arr[node][j] == 1 && nodes[j] != 2 && nodes[j] != 3)
			{ // ���� ������� ������� � �� ����������
				Stack.push(j); // ��������� �� � c���
				nodes[j] = 1; // �������� ������� ��� ������������
				flag = true;
			}
		}

		if (!flag)//���� � ������� ���� ��� ������ ����� � ����� ������� �� ����, ��� ��� ��� ��������� �������� �������� ����� �� � ���� ����� ���������������
		{
			path.pop_back();
			flag = true;
			while (flag && !path.empty()) {//����� �������� ������� ����� ��������� � ������� � �� �������(� ��) 
				int n = 0;				   //���� �� � ��� ������ ���� � ������� �� �� ���� ���� ��� ��� �� ����� � ��� ����������
				flag = true;			   //�������� ��� ������� ���������, ������ � ��� ������ � ������ �������, ������ ��� ���� :)
				for (int i = 0; i < m_size; ++i)
				{
					if (arr[path.back()][i] == 1 && nodes[i] != 2)//���� ���� ������ ���� �� ������������ ������� �� �����
						flag = false;
				}
				if (flag)
				{
					path.pop_back();
					flag = true;
				}
			}
		}
	}
}

Graph::Graph(int g[5][5])
{
	m_size = 5;

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			arr[i][j] = g[i][j];
		}
	}
}

int main()
{
	srand(time(0));

	/*int g[5][5] = {
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 0},
		{0, 1, 0, 0, 1},
		{1, 1, 0, 1, 0},
	};

	Graph G(g);

	G.print();

	for (int i = 0; i < 5; ++i)
		G.DFS_cycle(i);*/

	return 0;
}