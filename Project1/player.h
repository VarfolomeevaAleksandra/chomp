#pragma once
#include<iostream>


class Player
{
	int a; //lines
	int b; //columns
	int** field; //playing field
	int** winning_position;
	int* position;
	int* first_move;
	Player(int a1 = 0, int b1 = 0)
	{
		a = a1;
		b = b1;
		int** winning_position = new int* [2 * min(a, b) + max(a, b)]{ 0 };
		for (int row = 0; row < 2 * min(a, b) + max(a, b); row++)
		{
			winning_position[row] = new int[a] { 0 };
		};
		int** field = new int* [a]{ 0 };
		for (int row = 0; row < a; row++)
		{
			field[row] = new int[b] { 0 };
		};
		int* position = new int[a] { 0};
		int* first_move = new int[1]{ 0 };
	}
	Player(const Player& player);
	~Player();
	bool win_check(int** field);
	int** set_field(int**& field, int x, int y);
	int* set_first_move(int* first_move, int a, int b);
	int set_position(int i, int j);
	void filling_in_winning_positions(int**& winning_position, int a, int b);
	int* position(int a, int b, int** field);
	bool comparison_of_position(int a, int b, int* position, int** winning_position);
	int** copy_field(int** field, int, int b);
	bool check_move(int** field, int**winning_position, int a, int b, int x, int y);
};
