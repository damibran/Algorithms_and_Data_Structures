#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
const int MaxV = 26;
char Ch(int c) { return c + 'a'; }
class GR {
	int n, m;
	vector <list<int>> LIST;
	vector <int> NEW, X;
	void GAM(int);
public:
	GR(int); //��� ������� ������������ ���������� ������� 4.1.
	void GAM_test();
	~GR() = default;
};
void GR::GAM(int k)
{
	if (k == n) //������� �������, �������
	{
		cout << "<";
		for (auto x : X) cout << Ch(x) << ' ';
		cout << ">\n"; cin.get();
	}
	else
	{
		for (auto u : LIST[X[k - 1]]) //���������� ��������� Ak
		{
			if (NEW[u]) //��������� ������� ��������?
			{
				NEW[u] = true; //��������� ������� �������
				X.push_back(u); // � ��������� � � �������
				GAM(k + 1); //���������� ��������� ������
				X.pop_back(); //������� ����������� �������
				NEW[u] = false; // � ��������� � ����� ���������
			}
		}
	}
}
void GR::GAM_test() {
	NEW.resize(n, 1);
	cout << "\n����������� ����:\n";
	X.push_back(0); NEW[0] = false;
	GAM(1);
	cin.get();
}
int main()
{
	GR G(MaxV);
	setlocale(LC_ALL, "Russian");
	cout <<
		"\nGAM test ====================== (C)lgn, 16.10.03;24.02.20";
	//������������ ������� GAM
	G.GAM_test();
}