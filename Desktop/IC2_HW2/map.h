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
	
	private:
		vector<vector<int>> _map;
		vector<vector<int>> _mask;
		int _NumberOfRow;
		int _NumberOfCol;
		int _NumberOfMine;
};
#endif