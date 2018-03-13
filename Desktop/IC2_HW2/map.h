#include <vector>

#ifndef MAP_H
#define MAP_H

using namespace std;

class map
{
public:
	map();//constructor, not used though
	bool init();//initialize the map, by _NumberOfRow, _NumberOfCol, _NumberOfMine and check if the _NumberOfMine is too large
	void print_map();//print the whole map
	void set_col(int col);//set _NumberOfCol
	void set_row(int row);//set _NumberOfRow
	void set_mine(int mine);//set _NumberOfMine
	void set_mine_pos(pair<int, int> FirstStep);//open up a game with the first step position, and prevent the player from stepping on a mine at the very first step
	void count_surrounding_mines(pair<int, int> Coord);//count the number of surrounding mines to present them on the map 
	void uncover(pair<int, int> Coord);//uncover the specific square on the map
	bool check_mine(pair<int, int> Coord);//check if there is a mine on the specific square of the map
	void make_flag(pair<int, int> Coord);//make flag on the specific square of the map
	void unmake_flag(pair<int, int>Coord);//unmark the specific square of the map
	int get_remain_number_of_mine();//get the "real" number of the mines
	int get_remain_number_of_mine_on_table();//get the "seeming" number of the mines
	int check_mask(pair<int, int>Coord);//check if the mask is marked as "flagged", "covered", or "revealed"
	void show_hand();//show all the position of the mines
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