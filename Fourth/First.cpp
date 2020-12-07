#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
const int MaxV = 26;

char Ch(int c) { 
	return c + 'a'; 
}

class GR {
	int num, n, m;
	vector <list<int>> LIST;
	vector <int> NUM, L;
	stack<pair<int, int>> STACK;
	void DBL(int v, int p);
public:
	GR();
	void DBL_Exec();
	~GR() = default;
};

GR::GR() : num(0), n(0), m(0)
{
	int G[MaxV][MaxV]; string s;
	for (int i = 0; i < MaxV; ++i)
		for (int j = 0; j < MaxV; ++j) G[i][j] = 0;
	cout << "\n ������� ��-�� ��������� (������ ���� a �� z)\n";
	do {
		cout << "v[" << Ch(n) << "]="; cin >> s;
		for (auto i : s)  if (isalpha(i)) {
			int j = (tolower(i) - 'a');
			G[n][j] = G[j][n] = 1;
		}
		++n;
	} while (isalpha(s[0]) && n < MaxV);
	n = m = 0; LIST.resize(MaxV);
	for (int i = 0; i < MaxV; ++i)
	{
		int f = 0;
		cout << '\n' << Ch(i) << ": ";
		for (int j = 0; j < MaxV; ++j)
			if (G[i][j])
			{
				++f;
				LIST[i].push_back(j);
				cout << Ch(j) << ' ';
			}
			else cout << "- ";
		m += f;
		if (f) ++n;
		else break;
	}
	cout << "\n|V|=" << n << " |E|=" << m / 2;
}

void GR::DBL_Exec() //����� ����� � �����, ��������, ����������
{
	NUM.resize(n, 0); L.resize(n, 0);
	for (int i = 0; i < n; ++i)
		if (!NUM[i]) DBL(i, -1);
}

void GR::DBL(int v, int p) //����� ���������� ���������
{
	using edge = pair<int, int>;
	NUM[v] = L[v] = ++num;
	for (auto u : LIST[v])
	{
		if (!NUM[u])
		{
			edge e0(u, v), e1(0, 0);
			STACK.push(e0); // ����� -> � ����
			DBL(u, v);
			L[v] = L[u] < L[v] ? L[u] : L[v];
			if (L[u] >= NUM[v])
			{
				cout << "\n ����� <" << Ch(v) << '-' << Ch(u)
					<< "> �������� ���������� [";
				do { //������ ���������� ������������
					e1 = STACK.top(); STACK.pop();
					cout << Ch(e1.first) << '-' << Ch(e1.second) << ';';
				} while ((e1 != e0) && !STACK.empty());
				cout << "] ";
			}
		} // if (NUM�
		else if ((u != p) && (NUM[u] < NUM[v]))
		{
			STACK.push(make_pair(u, v));
			L[v] = NUM[u] < L[v] ? NUM[u] : L[v];
		}
	} //  for�
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "\nDBL test ============== (C)lgn, 10.10.03;24.02.20";
	GR Gr;
	Gr.DBL_Exec();  //������������ ������� DBL
	cout << "\n ===== ����� =====\n";
}