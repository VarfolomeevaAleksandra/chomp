#include "player.h"
#include<stdio.h>

using namespace std;

//Player::Player(const Player& player)
//{
//	a = player.a;
//	b = player.b;
//	field = new int[a - 1, b - 1]{ 0 };
//	winning_position = new int[b - 1]{ 0 };
//	for (int i = 0; i < b; i++)
//	{
//		winning_position[i] = player.winning_position[i];
//		for (int j = 0; j < a; j++)
//		{
//			field[i, j] = player.field[i, j];
//		}
//	}
//
//}

Player::~Player()
{
	delete[] field;
	delete[] winning_position;
}

bool Player::win_check(int** field)
{
	if (field[a - 1][b - 1] == 1) return true;
	return false;
}
int** Player::set_field(int**& field, int x, int y)
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

int* Player::set_first_move(int* first_move, int a, int b)
{
	FILE* sm;
	char* fmove;
	sm = fopen("first_moves.txt", "rt");
	fseek(sm, (41 * a) + 1 + b, SEEK_SET);
	fread(fmove, 1, 1, sm);
	first_move[0] = *(fmove)-'0';
	fseek(sm, 1, SEEK_CUR);
	fread(fmove, 1, 1, sm);
	first_move[1] = *(fmove)-'0';
	return first_move;
}

int Player::set_position(int i, int j)
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

void Player::filling_in_winning_positions(int**& winning_position, int a, int b)
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

int* Player::position(int a, int b, int** field)
{
	int* position = new int[a];
	for (int i = 0; i < a; i++) 
	{
		for (int j = 0; j < b; j++)
		{
			if (field[i][j] != 0)
			{
				position[i] = b - j;
				break;
			}
		}
	}
	return position;
}

bool Player::comparison_of_position(int a, int b, int* position, int** winning_position)
{
	int k = 0;
	for (int i = 0; i < 2 * min(a, b) + max(a, b); i++)
	{
		for (int j = 0; j < a; j++)
		{
			if (winning_position[i][j] == position[j])
			{
				++k;
			}
		}
		if (k = a) return true;
	}
}

int** Player::copy_field(int** field, int a, int b)
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
			field[i][j] = field[i][j];
		}
	}
	return field1;
}

bool Player::check_move(int** field, int ** winning_position, int a, int b, int x, int y)
{
	int** field1 = new int* [a];
	field1 = copy_field(field, a, b);
	field1 = set_field(field1, x, y);
	int* position1 = new int[a];
	position1 = position(a, b, field1);
	if (comparison_of_position(a, b, position1, winning_position)) return true;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			int** field2 = new int* [a];
			field2 = copy_field(field1, a, b);
			field2 = set_field(field2, i, j);
			if (field2[i][j] != 0) break;
			int* position2 = new int[a];
			position2 = position(a, b, field2);
			if (comparison_of_position(a, b, position2, winning_position)) return false;
		}
	}
	return true;
}

