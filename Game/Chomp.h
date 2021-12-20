#pragma once

#include <vector>
#include <map>
#include <utility>

using namespace std;

using field_i = vector<vector<int>>;
using pair_i = pair<int, int>;

class Chomp
{
private:
	field_i field;

	field_i end;

	map<field_i, pair_i> winning_moves;


	bool set_field(field_i& test_field, int row, int col);

	pair_i check_move(field_i test_field);

	bool simulate_move(field_i test_field, int row, int col);

	void print_field(field_i test_field);

public:
	Chomp(int row, int col);

	field_i get_field();

	void print_field();

	bool set_field(int row, int col);

	pair_i find_best_move(field_i test_field);

	bool check_win();
};

