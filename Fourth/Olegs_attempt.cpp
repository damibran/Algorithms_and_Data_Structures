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
	std::vector<int> nodes(m_size); // вершины графа

	for (int i = 0; i < m_size; ++i) // исходно все вершины равны 0
		nodes[i] = 0;

	Stack.push(v); // помещаем в очередь первую вершину
	while (!Stack.empty())
	{ // пока стек не пуст
		int node = Stack.top(); // извлекаем вершину
		Stack.pop();

		path.push_back(node);

		//if (nodes[node] == 2) continue;
		nodes[node] = 2; // отмечаем ее как посещенную

		if (node == v)
			nodes[node] = 3;

		bool flag = false;

		for (int j = m_size - 1; j >= 0; --j)
		{ // проверяем для нее все смежные вершины
			if (arr[node][j] == 1 && arr[j][node] == 0 && nodes[j] == 3)
			{
				std::cout << std::endl;
				for (int i = 0; i < path.size(); ++i)
					std::cout << path[i] << "-";
				std::cout << j;
			}
			else if (arr[node][j] == 1 && nodes[j] != 2 && nodes[j] != 3)
			{ // если вершина смежная и не обнаружена
				Stack.push(j); // добавляем ее в cтек
				nodes[j] = 1; // отмечаем вершину как обнаруженную
				flag = true;
			}
		}

		if (!flag)//Если у текущей верш нет нужных детей её нужно удалить из пути, так как при следующей итерации большого цикла не её дети будут рассматриваться
		{
			path.pop_back();
			flag = true;
			while (flag && !path.empty()) {//после удаления текущей нужно проверить её предков и их предков(и тд) 
				int n = 0;				   //есть ли у них нужные дети и удалить их из пути если они уже не могут в нем учавствать
				flag = true;			   //возможно это лечится рекурсией, однако с ней придут и другие болячки, такчто мне лень :)
				for (int i = 0; i < m_size; ++i)
				{
					if (arr[path.back()][i] == 1 && nodes[i] != 2)//если есть хотябы одна не рассмотренна удалать не нужно
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