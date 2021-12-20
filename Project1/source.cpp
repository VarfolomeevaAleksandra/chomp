#include <iostream>
#include<stdio.h>
#include<fstream>


using namespace std;

bool win_check(int** field, int a, int b) // проверка победы
{
	if (field[a - 1][b - 1] == 1) return true;
	return false;
}
int** set_field(int**& field, int x, int y) //заполнение поля после хода
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			field[i][j] = 1;
		}
	}
	return field;
}

int* set_first_move(int a, int b) //определение первого хода
{
	ifstream fin;
	fin.open("first moves.txt");
	int** first_move = new int* [20]{ 0 };
	for (int row = 0; row < 20; row++)
	{
		first_move[row] = new int[20]{ 0 };
	}
	while (!fin.eof())
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				fin >> first_move[i][j];
			}
		}
	}
	fin.close();
	int* result = new int[2];
	result[0] = first_move[a - 1][2 * b - 2];
	result[1] = first_move[a - 1][2 * b - 1];
	return result;
}
int set_position(int i, int j) //вспомогательная функция для заполнения массива выигрышных позиций
{
	if (j < i)
	{
		return 0;
	}
	if (i == j)
	{
		return 1;
	}
	if (j > i)
	{
		return 2;
	}
}

void filling_in_winning_positions(int**& winning_position, int a, int b) //заполнение массива выигрышных позиций
{
	for (int i = 0; i < min(a, b); i++)
	{
		if (a != min(a, b))
		{
			for (int j = 0; j < b - min(a, b); j++)
			{
				winning_position[i][j] = 0;
			}
		}
		for (int j = a - min(a, b); j < i + a - min(a, b); j++)
		{
			winning_position[i][j] = 0;
		}
		for (int j = i + a - min(a, b); j < a - 1; j++)
		{
			winning_position[i][j] = 1;
		}
		winning_position[i][a - 1] = min(a, b) - i;
	}
	for (int i = min(a, b); i < min(a, b) + a; i++)
	{
		for (int j = 0; j < a; j++)
		{
			winning_position[i][j] = set_position(i - min(a, b), j);
		}
	}


	for (int i = min(a, b) + a; i < min(a, b) + a + b; i++)
	{
		for (int j = 0; j < a - 2; j++)
		{
			winning_position[i][j] = 0;
		}
		winning_position[i][a - 2] = b - 1 - (i - (min(a, b) + a));
		winning_position[i][a - 1] = b - (i - (min(a, b) + a));
	}
}

int* get_position(int a, int b, int** field) //заполнение массива, описывающего состояние поля
{
	int* position = new int[a] { b };
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (field[i][j] == 0)
			{
				position[i] = b - j;
				break;
			}
			if (j == b - 1)
			{
				position[i] = 0;
			}
		}
	}
	return position;
}

bool comparison_of_positions(int a, int b, int* position, int** winning_position) //сравнение разных позиций поля
{

	for (int i = 0; i < 2 * min(a, b) + max(a, b); i++)
	{
		int k = 0;
		for (int j = 0; j < a; j++)
		{

			if (winning_position[i][j] == position[j])
			{
				++k;
			}
		}
		if (k == a) return true;

	}
	return false;
}

int** copy_field(int** field, int a, int b) //копирование поля
{
	int** field1 = new int* [a] { 0 };
	for (int row = 0; row < a; row++)
	{
		field1[row] = new int[b] { 0 };
	}
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			field1[i][j] = field[i][j];
		}
	}
	return field1;
}

int count(int** field, int a, int b)
{
	int count = 0;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (field[i][j] == 0) ++count;
		}
	}
	return count;
}

bool check_move(int** field, int** winning_position, int a, int b, int x, int y, int f) //определение, является ли ход подходящим
{
	int p = f;
	int c = 0;
	cout << f << endl;

	int** field1 = new int* [a];
	for (int i = 0; i < a; i++)
	{
		field1[i] = new int[b];
	}
	field1 = copy_field(field, a, b);
	field1 = set_field(field1, x + 1, y + 1);
	cout << "Первое поле" << endl;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			cout << field1[i][j] << " ";
		}
		cout << endl;
	}
	int* position1 = new int[a];
	position1 = get_position(a, b, field1);
	if (comparison_of_positions(a, b, position1, winning_position)) return true;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (field1[i][j] == 0)
			{
				cout << i << " " << j << endl;
				int** field2 = new int* [a];
				for (int i = 0; i < a; i++)
				{
					field2[i] = new int[b];
				}
				field2 = copy_field(field1, a, b);
				field2 = set_field(field2, i + 1, j + 1);
				int* position2 = new int[a];
				position2 = get_position(a, b, field2);
				cout << "Второе поле" << endl;
				for (int i = 0; i < a; i++)
				{
					for (int j = 0; j < b; j++)
					{
						cout << field2[i][j] << " ";
					}
					cout << endl;
				}
				if (comparison_of_positions(a, b, position2, winning_position) && (p % 2 == 0)) return false;
				if (comparison_of_positions(a, b, position2, winning_position) && (p % 2 == 1)) return true;
			}
		}
	}
	//if (c == count(field1, a, b)) return true;
	//else if (c != count(field1, a, b)) return false;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			++p;
			cout << p << endl;
			
			if (check_move(field1, winning_position, a, b, i, j, p)) ++c;
			cout << c << endl;
			system("pause");
		}
	}
	if (c == count(field1, a, b)) return true;
}

void draw(int** field, int a, int b) //вывод поля
{
	int* position = new int[a];
	position = get_position(a, b, field);
	int a1 = 0;
	int b1 = 0;
	for (int i = 0; i < a; i++)
	{
		//cout << endl;
		for (int j = 0; j < b; j++)
		{
			if (b - j > position[i])
			{
				cout << "      ";
			}
			else
			{
				cout << " ____ ";
			}

		}
		cout << endl;
		for (int j = 0; j < b; j++)
		{
			if (b - j > position[i])
			{
				cout << "      ";
			}
			else
			{
				cout << "|    |";
			}
			
		}
		cout << endl;
		for (int j = 0; j < b; j++)
		{
			if (b - j > position[i])
			{
				cout << "      ";
			}
			else
			{
				cout << "|____|";
			}
			
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	int b;
	//размер поля
	cin >> a;
	cin >> b;
	int** winning_position = new int* [2 * min(a, b) + max(a, b)]{ 0 };
	for (int row = 0; row < 2 * min(a, b) + max(a, b); row++)
	{
		winning_position[row] = new int[a] {0};
	}

	int** field = new int* [a] { 0 };
	for (int row = 0; row < a; row++)
	{
		field[row] = new int[b] {0};
	}

	filling_in_winning_positions(winning_position, a, b);
	cout << "Начало игры" << endl;
	system("cls");
	draw(field, a, b);
	system("pause");
	int* position = new int[a] { 0 };
	int* first_move = new int[2]{ 0 };
	int x;
	int y;
	first_move = set_first_move(a, b);
	field = set_field(field, first_move[0], first_move[1]);
	system("cls");
	draw(field, a, b);
	system("pause");
	position = get_position(a, b, field);
	while (true)
	{
		cout << endl;
		cout << "Введите координаты клетки (отсчет начинается с 1, а не с 0)" << endl;
		cin >> x;
		cin >> y;
		while ((x > a) || (y > b))
		{
			cout << "Вы ввели неверные координаты, введите заново" << endl;
			cin >> x;
			cin >> y;
		}
		field = set_field(field, x, y);
		system("cls");
		draw(field, a, b);
		system("pause");
		if (win_check(field, a, b))
		{
			{
				cout << endl;
				cout << "Вы проиграли" << endl;
				break;
			}
		}
		int k = 0;
		int p = 0;
		int f = 0;
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				if (field[i][j] == 0)
				{
					cout << i << " " << j << endl;
					if (check_move(field, winning_position, a, b, i, j, f))
					{
						k = i;
						p = j;
						break;
					}
					if ((k != 0) || (p != 0)) break;
				}

			}
		}
		field = set_field(field, k + 1, p + 1);
		system("cls");
		draw(field, a, b);
		system("pause");
		if (win_check(field, a, b))
		{
			{
				cout << endl;
				cout << "Вы выиграли" << endl;
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
	
