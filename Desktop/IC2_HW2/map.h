#include <vector>

#ifndef MAP_H
#define MAP_H

using namespace std;

class map
{
public:
	map();
	bool init();
	void print_map();
	void set_col(int col);
	void set_row(int row);
	void set_mine(int mine);
	void set_mine_pos(pair<int, int> FirstStep);
	void count_surrounding_mines(pair<int, int> Coord);
	void uncover(pair<int, int> Coord);
	bool check_mine(pair<int, int> Coord);
	void make_flag(pair<int, int> Coord);
	void unmake_flag(pair<int, int>Coord);
	int get_remain_number_of_mine();
	int get_remain_number_of_mine_on_table();
	int check_mask(pair<int, int>Coord);
	void show_hand();
	//int get_unmasked();

private:
	vector<vector<int>> _map;
	vector<vector<int>> _mask;
	int _NumberOfRow;
	int _NumberOfCol;
	int _NumberOfMine;
	int _RemainOfMine;
	int _SurfaceRemainOfMine;
};
#endif