// First.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

struct list {
	char el;
	list* next;
	list(char  e, list* n = nullptr) : el(e), next(n) { }
	~list() { delete next; }
};


list* delete_elem(list* lst, list* root);
void add(list** head, char c);
void print_list(list* head);
int len(list* head);
void str_to_list(list* head, string in);
void and_m(list* a, list* b, list* e);
void sub_m(list* e, list* c);
void unite_m(list* e, list* d);
long int str_to_univers(string in);

int main()
{
	// A&&B\\C||D
	string in;

	/*list* a = new list('#');
	list* b = new list('#');
	list* c = new list('#');
	list* d = new list('#');

	list* e = new list('#');

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(a, in);

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(b, in);

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(c, in);

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(d, in);*/

	char U[26];
	long int a;

	for(int i=0;i<26;i++)
	{
		U[i] = i + 'a';
	}

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	a=str_to_univers(in);

	cout << a;

	/*printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(b, in);

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(c, in);

	printf("Enter mnozestvo:\n");
	getline(cin, in);
	str_to_list(d, in);*/



	system("pause");
}

long int str_to_univers(string in)
{
	long int k = 0;;

	for (int i = 0; i < 26; i++)
	{
		k = k || (1 << i);
	}
	return k;
}

list* proc_by_list(list *a,list *b,list *c,list *d)
{
	list* e = new list('#');

	and_m(a, b, e);

	print_list(e);

	sub_m(e, c);

	unite_m(e, d);

	return e;
}

void unite_m(list* e,list *d)
{
	list* curE = e->next;
	list* curD = d->next;
	bool flag = false;

	while (curD != nullptr)
	{
		curE = e->next;
		flag = false;
		while (curE != nullptr)
		{
			if (curE->el == curD->el)
			{
				flag = true;
			}
			curE = curE->next;
		}
		if (!flag)
			add(&e, curD->el);
		curD = curD->next;
	}
}

void and_m(list* a, list* b, list* e)
{
	list* curA = a->next;
	list* curB = b->next;

	while (curA != nullptr)
	{
		list* curB = b->next;
		while (curB != nullptr)
		{
			if (curA->el == curB->el)
			{
				add(&e, curA->el);
			}
			curB = curB->next;
		}
		curA = curA->next;
	}
}

void sub_m(list* e, list* c)
{
	list* curE = e->next;
	list* curC = c->next;
	list* prev = nullptr;

	while (curE != nullptr)
	{
		list* curC = c->next;
		while (curC != nullptr)
		{
			if (curE->el == curC->el)
			{
				if (prev == nullptr)
				{
					if (curE == e->next)
					{
						delete_elem(curE, e);
						curE = e->next;
					}
					else
					{
						delete_elem(curE, e);
					}

				}
				else
				{
					delete_elem(curE, e);
					curE = prev;

				}
			}
			curC = curC->next;
		}
		if (curE == nullptr)
		{
			curE = e->next;
		}
		else
		{
			prev = curE;
			curE = curE->next;
		}
	}
}

int len(list* head)
{
	list* cur;
	int c = 0;
	cur = head;
	while (cur->next != nullptr)
	{
		cur = cur->next;
		c++;
	}

	return c;
}

void str_to_list(list* head, string in)
{
	for (int i = 0; i < in.length(); i++)
	{
		add(&head, in[i]);
	}
}

void print_list(list* head)
{
	list* a;

	a = head->next;
	while (a != nullptr)
	{
		cout << a->el;
		a = a->next;
	}

	cout << '\n';
}

void add(list** head, char c)
{
	list* a;
	list* wen;
	a = *head;

	try
	{
		wen = new list(c, a->next);
		a->next = wen;
	}
	catch (errc)
	{
		list* b = new list(c);
		b = new list('#', b);
		*head = b;
	}

}

list* delete_elem(list* lst, list* root)
{
	list* temp = nullptr;
	if (len(root) != 0) {
		temp = root;
		while (temp->next != lst) // просматриваем список начиная с корня
		{ // пока не найдем узел, предшествующий lst
			temp = temp->next;
		}
		temp->next = lst->next; // переставляем указатель
		free(lst); // освобождаем память удаляемого узла
	}
	return(temp);

}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
