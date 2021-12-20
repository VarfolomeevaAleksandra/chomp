#include <iostream>
#include<time.h>
#include "Chomp.h"

using namespace std;

void won_game(bool playerWon);

int main()
{
	int a = 0;
	int b = 0;
	int f = 0;

	cout << "Number of rows: ";
	cin >> a;

	cout << "Number of columns: ";
	cin >> b;

	cout << endl;

	Chomp game(a, b);
	game.print_field();
	system("pause");
	int inrow = 0;
	int incol = 0;

	bool isPlayerTurn = false; //Игрок - true, программа - false

	while (true)
	{
		time_t start, end;

		if (isPlayerTurn)
		{
			cout << "Enter cell coordinates" << endl;
			cout << "Row: ";
			cin >> inrow;

			while (inrow == 0 || inrow < -1)
			{
				cout << "Invalid Row: ";
				cin >> inrow;
			}

			cout << "Col: ";
			cin >> incol;

			while (incol == 0 || incol < -1)
			{
				cout << "Invalid Col: ";
				cin >> incol;
			}

			cout << endl;
		}
		else
		{
			time(&start);
			
			if (f == 0)
			{
				if (game.check_rectangle())
				{
					inrow = a - 1;
					incol = b - 1;
				}
			}
			else
			{
				pair<int, int> best_move = game.find_best_move(game.get_field());
				inrow = best_move.first;
				incol = best_move.second;
				time(&end);
				double seconds = difftime(end, start);
				cout << "Time: " << seconds << endl;
				system("pause");
			}
			++f;
		}

		if (inrow == a && incol == b)
		{
			won_game(!isPlayerTurn);
			return 1;
		}

		if (game.set_field(inrow, incol))
		{
			system("cls");
			game.print_field();

			if (game.check_win())
			{
				won_game(isPlayerTurn);
				return 0;
			}
			system("pause");
			isPlayerTurn = !isPlayerTurn;
		}
	}
}

void won_game(bool player_won)
{
	if (player_won)
	{
		cout << "You won!" << endl;
	}
	else
	{
		cout << "You lost" << endl;
	}
}