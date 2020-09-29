// First.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <time.h>
#include <cstring>
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
void and_list(list* a, list* b, list* e);
void sub_list(list* e, list* c);
void unite_list(list* e, list* d);
long int str_to_univers_word(string in);
char* univers_to_str_word(long int in);
char* univers_to_str_array(bool* in);
bool* str_to_univers_array(string in);
void and_bool_array(bool* a, bool* b, bool* e);
void initialize_bool(bool* a);
void sub_bool_array(bool* e, bool* c);
void unite_bool_array(bool* e, bool* d);
void del_elem_array(char* in, int n);
void unite_array(char* in_1, char* in_2);
void and_array(char* in1, char* in2, char* res);
void sub_array(char* in1, char* in2);
void proc_by_word(char in[4][26]);
void proc_by_list(char in[4][26]);
void proc_by_bool_array(char in[4][26]);
void proc_by_array(char in[4][26]);

int main()
{
	//clock_t start, stop;
	// A&&B\\C||D
	char in[4][26] = { "qwerty","yasedfq","jen","oky" };
	
	//start = clock();
	
	proc_by_word(in);
	cout << "\n";
	proc_by_bool_array(in);
	cout << "\n";
	proc_by_list(in);
	proc_by_array(in);
	cout << endl;
	
	//stop = clock();

	//cout << (float)(stop-start)/CLK_TCK;
	
	system("pause");
	return 0;
}


void proc_by_bool_array(char in[4][26])
{
	bool* a;
	bool* b;
	bool* c;
	bool* d;
	bool* e = new bool[26];

	a = str_to_univers_array(in[0]);

	b = str_to_univers_array(in[1]);

	c = str_to_univers_array(in[2]);

	d = str_to_univers_array(in[3]);

	e = str_to_univers_array("");

	and_bool_array(a, b, e);

	sub_bool_array(e, c);

	unite_bool_array(e, d);

	char* res = new char[26];
	res = univers_to_str_array(e);
	cout << res;
}

void proc_by_word(char in[4][26])
{
	long int a;
	long int b;
	long int c;
	long int d;
	long int e;

	a = str_to_univers_word(in[0]);

	b = str_to_univers_word(in[1]);

	c = str_to_univers_word(in[2]);

	d = str_to_univers_word(in[3]);

	e = a & b;
	e = (e | c) & (~c);
	e = e | d;

	char* res = new char(26);

	res = univers_to_str_word(e);

	cout << res;
}

void proc_by_list(char in[4][26])
{
	list* a = new list('#');
	list* b = new list('#');
	list* c = new list('#');
	list* d = new list('#');

	list* e = new list('#');

	str_to_list(a, in[0]);

	str_to_list(b, in[1]);

	str_to_list(c, in[2]);

	str_to_list(d, in[3]);

	and_list(a, b, e);

	//print_list(e);

	sub_list(e, c);

	unite_list(e, d);

	print_list(e);
}

void proc_by_array(char in[4][26])
{
	char* e = new char[26]();

	and_array(in[0], in[1], e);
	
	sub_array(e, in[2]);
	
	unite_array(e, in[3]);

	cout << e;
}

void unite_bool_array(bool* e, bool* d)
{
	for (int i = 0; i < 26; i++)
		e[i] = e[i] || d[i];
}

void sub_bool_array(bool* e, bool* c)
{
	for (int i = 0; i < 26; i++)
		e[i] = ((e[i] || c[i]) && !c[i]);

}

void initialize_bool(bool* a)
{
	for (int i = 0; i < 26; i++)
		a[i] = false;
}

void and_bool_array(bool* a, bool* b, bool* e)
{
	for (int i = 0; i < 26; i++)
		e[i] = bool(a[i] && b[i]);
}

char* univers_to_str_array(bool* in)
{
	char* k = new char[26];
	int m = 0;

	for (int i = 0; i < 26; i++)
		if (in[i])
			k[m++] = 'a' + i;

	k[m] = '\0';
	return k;
}

bool* str_to_univers_array(string in)
{
	bool* k = new bool[26];

	initialize_bool(k);

	for (char c : in)
		if (c != 0)
			k[int(c) - 97] = true;

	return k;
}

char* univers_to_str_word(long int in)
{
	char* k = new char[26];

	int m = 0;
	for (int i = 0; i < 26; i++) {
		if (in % 2 == 1)
			k[m++] = 'a' + i;
		in = in / 2;
	}

	k[m] = '\0';

	return k;
}

long int str_to_univers_word(string in)
{
	long int k = 0;;

	for (char c : in)
		if (c != 0)
			k = k | (1 << (int(c) - 97));

	return k;
}

void unite_list(list* e,list *d)
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
				flag = true;

			curE = curE->next;
		}
		if (!flag)
			add(&e, curD->el);
		curD = curD->next;
	}
}

void and_list(list* a, list* b, list* e)
{
	list* curA = a->next;
	list* curB = b->next;

	while (curA != nullptr)
	{
		list* curB = b->next;
		while (curB != nullptr)
		{
			if (curA->el == curB->el)
				add(&e, curA->el);

			curB = curB->next;
		}
		curA = curA->next;
	}
}

void sub_list(list* e, list* c)
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
						delete_elem(curE, e);
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
		add(&head, in[i]);
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

void del_elem_array(char* in, int n)
{
	int j=n;
	for(int i=n+1; i<strlen(in); ++i) in[j++]=in[i];
	in[strlen(in)-1] = '\0';
}

void unite_array(char* in1, char* in2)
{
	int f;
	for(int i=0; i<strlen(in2); ++i)
	{
		f = 0;
		for(int j=0; j<strlen(in1); ++j)
		{
			if(in2[i]==in1[j])  f = 1;
		}
		if(f==0) in1[strlen(in1)] = in2[i];
	}
}

void and_array(char* in1, char* in2, char *res)
{
	int k=0;
	for(int i=0; i<strlen(in1); ++i)
	{
		for(int j=0; j<strlen(in2); ++j)
		{
			if(in1[i]==in2[j]) res[k++] = in1[i];
		}
	}
}

void sub_array(char* in1, char* in2)
{
	for(int i=0; i<strlen(in1); ++i)
	{
		for(int j=0; j<strlen(in2); ++j)
		{
			if(in1[i]==in2[j]) del_elem_array(in1, i);
		}
	}
}
