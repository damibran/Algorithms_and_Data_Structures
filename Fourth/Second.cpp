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
	GR(int); //Эта функция определяется аналогично примеру 4.1.
	void GAM_test();
	~GR() = default;
};
void GR::GAM(int k)
{
	if (k == n) //Найдено решение, выводим
	{
		cout << "<";
		for (auto x : X) cout << Ch(x) << ' ';
		cout << ">\n"; cin.get();
	}
	else
	{
		for (auto u : LIST[X[k - 1]]) //Перебираем множество Ak
		{
			if (NEW[u]) //Очередная вершина свободна?
			{
				NEW[u] = true; //Объявляем вершину занятой
				X.push_back(u); // и добавляем её в решение
				GAM(k + 1); //Продолжаем расширять вектор
				X.pop_back(); //Убираем проверенную вершину…
				NEW[u] = false; // и объявляем её снова свободной
			}
		}
	}
}
void GR::GAM_test() {
	NEW.resize(n, 1);
	cout << "\nГамильтонов путь:\n";
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
	//Тестирование функции GAM
	G.GAM_test();
}