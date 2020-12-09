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
	int arr[maxSize][maxSize];
	std::vector<int> cycles[maxSize*10];
	int cycle_number = 0;

	bool cyclic_cmpr_of_vectors(std::vector<int> a, std::vector<int> b)
	{
		bool res = true;
		size_t n = a.size();
		int i;
		for (i = 0; i < n; ++i)
		{
			if (a[0] == b[i])
			{
				for (int j = 0; j < n; ++j)
				{
					if (a[j] != b[(i + j) % int(n)])
						res = false;
				}
				break;
			}
		}
		if (i == n)
			res = false;
		return res;
	}

	bool cycle_already_added(std::vector<int> that)
	{
		bool flag = false;
		for (int i = 0; i < cycle_number; ++i)
			if (cycles[i].size() == that.size() && cyclic_cmpr_of_vectors(cycles[i], that))
				flag = true;
		return flag;
	}

public:
	Graph(int);
	Graph(int, int);
	Graph(int[5][5]);
	void print_matrix();
	void DFS_cycle(int v, int par, int color[], int parent[],int);
	int getSize();
	void print_cycles();
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
				if (rand() % 2 == 0 && edges > 0)
				{
					arr[i][j] = 1;
					edges -= 1;
				}
			}
		}
}

void Graph::print_matrix()
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

void Graph::DFS_cycle(int v, int prnt, int color[], int parent[],int start)
{
	if (color[v] == 1)
	{
		if (v == start) 
		{
			std::vector<int> temp;
			int cur = prnt;
			temp.push_back(v);
			while (cur != v)
			{
				temp.push_back(cur);
				cur = parent[cur];
			}
			if (!cycle_already_added(temp))
			{
				cycles[cycle_number] = temp;
				cycle_number++;
			}
		}
		return;
	}

	parent[v] = prnt;

	color[v] = 1;

	for (int i = 0; i < m_size; ++i)
	{ // проверяем для нее все смежные вершины
		if (arr[v][i] == 1)
			DFS_cycle(i, v, color, parent,start);
	}
	color[v] = 0;
}

int Graph::getSize()
{
	return m_size;
}

void Graph::print_cycles()
{
	for (int i = 0; i < cycle_number; ++i)
		if (cycles[i][0] != -1)
		{
			std::cout << cycles[i][0] << "-";
			for (int j = (int)cycles[i].size() - 1; j > 0; --j)
			{
				std::cout << cycles[i][j] << "-";
			}
			std::cout << cycles[i][0] << "\n";
		}
}

int main()
{
	srand(time(0));

	/*int g[5][5] = {
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{0, 1, 0, 1, 1},
		{0, 1, 1, 0, 0},
		{1, 1, 0, 1, 0}
	};*/
	
	Graph G(5,13);

	G.print_matrix();

	for (int i = 0; i < G.getSize(); ++i)
	{
		int* color = new int[G.getSize() * sizeof(int)];
		int* parent = new int[G.getSize() * sizeof(int)];

		for (size_t j = 0; j < G.getSize(); ++j)
		{
			color[j] = -1;
			parent[j] = -1;
		}

		G.DFS_cycle(i, -1, color, parent,i);

		delete[] color;
		delete[] parent;
	}

	std::cout << "\nCycles:\n";

	G.print_cycles();

	return 0;
}