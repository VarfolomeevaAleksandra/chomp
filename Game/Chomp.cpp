#include "Chomp.h"

#include <iostream>

using namespace std;

Chomp::Chomp(int rows, int columns)
{
	field_i tempField(rows, vector<int>(columns, 0));
	tempField.back()[columns - 1] = 2;

	field = tempField;

	field_i tempEnd(rows, vector<int>(columns, 1));

	end = tempEnd;
}

field_i Chomp::get_field()
{
	return field;
}

void Chomp::print_field()
{
	for (auto i = 0; i <= field.size(); ++i)
	{
		if (i == 0)
		{
			cout << "   ";
		}
		else
		{
			cout << i << ": ";
		}

		for (auto j = 0; j < field[0].size(); ++j)
		{
			if (i == 0)
			{
				cout << j + 1 << " ";
			}
			else
			{
				cout << field[i - 1][j] << " ";
			}
		}
		cout << endl;
	}

	cout << endl;
}

void Chomp::print_field(field_i test_field)
{
	for (auto i = 0; i <= test_field.size(); i++)
	{
		if (i == 0)
		{
			cout << "   ";
		}
		else
		{
			cout << i << ": ";
		}

		for (auto j = 0; j < test_field[0].size(); j++)
		{
			if (i == 0)
			{
				cout << j + 1 << " ";
			}
			else
			{
				cout << test_field[i - 1][j] << " ";
			}
		}
		cout << endl;
	}

	cout << endl;
}

bool Chomp::set_field(int row, int col)
{
	row--;
	col--;

	if (row >= field.size() || col >= field[0].size())
	{
		cout << "Invalid number of rows or columns" << endl;;
		return false;
	}

	if (field[row][col] == 1)
	{
		cout << "Invalid move" << endl;;
		return false;
	}

	for (auto i = 0; i < field.size(); ++i)
	{
		for (auto j = 0; j < field[0].size(); ++j)
		{
			if (i <= row && j <= col)
			{
				field[i][j] = 1;
			}
		}
	}

	return true;
}

bool Chomp::set_field(field_i& test_field, int row, int col)
{
	if (row >= test_field.size() || col >= test_field[0].size())
	{
		return false;
	}

	if (test_field[row][col] == 1)
	{
		return false;
	}

	for (auto i = 0; i < test_field.size(); ++i)
	{
		for (auto j = 0; j < test_field[0].size(); ++j)
		{
			if (i <= row && j <= col)
			{
				test_field[i][j] = 1;
			}
		}
	}

	return true;
}

pair_i Chomp::check_move(field_i test_field)
{
	auto i = winning_moves.find(test_field);

	if (i != winning_moves.end())
	{
		return i->second;
	}

	pair_i bestMove = { -1, -1 };

	for (auto i = 0; i < test_field.size(); ++i)
	{
		for (auto j = 0; j < test_field[0].size(); ++j)
		{
			if (test_field[i][j] == 0)
			{
				if (simulate_move(test_field, i, j))
				{
					bestMove = { i, j };
					break;
				}
				
			}
		}
	}

	winning_moves.emplace(test_field, bestMove);

	return bestMove;
}

bool Chomp::simulate_move(field_i test_field, int row, int col)
{
	set_field(test_field, row, col);

	pair_i check_coords = check_move(test_field);

	if (check_coords.first == -1)
	{
		return true;
	}

	return false;
}

pair_i Chomp::find_best_move(field_i test_field)
{
	pair_i bestMove = check_move(test_field);

	if (bestMove.first != -1)
	{
		bestMove.first++;
		bestMove.second++;
	}

	return bestMove;
}

bool Chomp::check_win()
{
	if (field == end)
	{
		return true;
	}

	return false;
}

bool Chomp::check_rectangle()
{
	if (field.size() == field[0].size()) return true;
	return false;
}