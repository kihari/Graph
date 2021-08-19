#include<iostream>
#include<string.h>
using namespace std;

#define infinity 99999999

const int N = 12;// Количество вершин
// Матрица смежности
const int graph[N][N] = {
	{0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 8, 15, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 9, 0, 0, 6, 0, 3, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 10, 2, 3, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 11, 0},
	{0, 0, 0, 0, 0, 0, 7, 0, 0, 9, 4, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

struct Graff
{
	int data;
	Graff* prev;
};
Graff* top = NULL;


void push(int data)
{
	Graff* temp = new Graff;
	temp->data = data;
	temp->prev = top;
	top = temp;

}

void pop()
{
	Graff* temp = top;
	top = top->prev;
	temp->prev = NULL;
	delete temp;
}

void PrintStack()
{
	Graff* temp = top;

	while (temp != NULL)
	{
		cout << temp->data << "  ";
		temp = temp->prev;
	}
}

int* Topological_Sort(const int graph[N][N])
{
	int* LineOrder = new int[N];
	memset(LineOrder, 0, sizeof(int*) * N);
	int in_degree[N] = {};

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (graph[i][j] > 0)
			{
				in_degree[j]++;
			}
		}
	}

	cout << "\nСтепени вершин:\n";
	for (int i = 0; i < N; i++)
	{
		cout << i  << ".\t" << in_degree[i] << endl;
	}

	for (int i = 0; i < N; i++)
	{
		if (in_degree[i] == 0)
		{
			push(i + 1);
		}
	}
	cout << "Стек: ";
	PrintStack();

	int temp;
	int i = 0;

	while (top != NULL)
	{

		temp = top->data;
		pop();
		LineOrder[i] = temp;

		for (int j = 0; j < N; j++)
		{
			if (graph[LineOrder[i] - 1][j] > 0)
			{
				in_degree[j]--;

				if (in_degree[j] == 0)
				{
					push(j + 1);

					cout << endl;
					for (int n = 0; n < N; n++)
					{
						cout << n + 1 << ". " << in_degree[n] << endl;
					}
					cout << "Стек: ";
					PrintStack();
					cout << endl;

				}
			}

		}
		i++;
	}

	cout << "\n\nЛинейное упорядочение: ";
	for (i = 0; i < N; i++)
	{
		cout << LineOrder[i] << "   ";
	}

	return LineOrder;
}

void Relax(int u, int v, const int graph[N][N], int* shortest, int* pred)
{

	if (shortest[u - 1] + graph[u - 1][v - 1] < shortest[v - 1])
	{
		shortest[v - 1] = shortest[u - 1] + graph[u - 1][v - 1];
		pred[v - 1] = u;
	}

}

void Dag_Shortest_Paths(const int graph[N][N], int s, int* shortest, int* pred)
{

	int* LineOrder = new int[N];
	LineOrder = {};

	LineOrder = Topological_Sort(graph);
	
	for (int i = 0; i < N; i++)
	{
		shortest[i] = infinity;
	}
	
	for (int i = 0; i < N; i++)
	{
		pred[i] = NULL;
	}
	shortest[s - 1] = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (graph[LineOrder[i] - 1][j] > 0)
			{
				Relax(LineOrder[i], j + 1, graph, shortest, pred);
			}
		}
	}

	cout << "\n\n\nНачальная вершина: " << s << endl;
	cout << "Кратчайшие пути для " << s << " вершины: \n";
	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << " вершина: ";
		if (shortest[i] == infinity)
		{
			cout << "<infinity>\n";
		}
		else
		{
			cout << shortest[i] << endl;
		}
	}

	cout << "\nПредыдущие вершины:\n";
	for (int i = 0; i < N; i++)
	{
		cout << "Вершина: " << i << ". Предыдущая: ";
		if (pred[i] == NULL)
		{
			cout << "<NULL>\n";
		}
		else
		{
			cout << pred[i] << endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	int* LineOrder = new int[N];
	int* shortest = new int[N];
	int* pred = new int[N];

	cout << "Матрица смежности:\n\t";
	for (int i = 0; i < N; i++)
	{
		cout << i << "\t";
	}
	cout << endl << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < N; j++)
			cout << graph[i][j] << "\t";
		cout << endl;
	}

	int s;
	cout << "Введите исходную вершину: ";
	cin >> s;
	if (s > N || s < 0)
	{
		cout << "Недопустимый выбор вершины";
		return -1;
	}

	LineOrder = Topological_Sort(graph);
	Dag_Shortest_Paths(graph, s, shortest, pred);

	delete[] LineOrder;
	delete[] shortest;
	delete[] pred;

	cout << endl << endl;
	return 0;
}