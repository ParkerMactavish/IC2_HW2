#include "map.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

map::map()
{
}

void map::print_map()
{
	system("CLS");
	cout << _SurfaceRemainOfMine << " mines to go" << endl;
	cout << "   ";
	for (int i = 0; i < _map[0].size(); i++) cout << setw(2) << i + 1;
	cout << endl;
	cout << "───";
	for (int i = 0; i < _map[0].size(); i++) cout << "──";
	cout << endl;
	for (int i = 0; i<_map.size(); i++)
	{
		cout <<setw(2) << i + 1<<'|';
		for (int j = 0; j<_map[i].size(); j++)
		{
			if (_mask[i][j] == 1)
			{
				if (_map[i][j] == 0) cout << "□";
				else if (_map[i][j] == -1)cout << "△";
				else cout << setw(2) << _map[i][j];
			}
			else if (_mask[i][j] == 0) cout << "█";
			else if (_mask[i][j] == 2) cout << "★";
		}
		cout << endl;
	}

	//test
	/*cout << endl << endl;
	for (int i = 0; i<_map.size(); i++)
	{
		for (int j = 0; j<_map[i].size(); j++)
		{
			cout << setw(2) << _map[i][j];
		}
		cout << endl;
	}*/
}

void map::set_col(int col)
{
	_NumberOfCol = col;
}

void map::set_row(int row)
{
	_NumberOfRow = row;
}

void map::set_mine(int mine)
{
	_NumberOfMine = mine;
	_RemainOfMine = mine;
	_SurfaceRemainOfMine = mine;
}

bool map::init()
{
	int FailFlag = false;
	if (_NumberOfMine >= _NumberOfCol*_NumberOfRow) FailFlag = true;
	else
	{
		vector<int> TmpVec(_NumberOfCol, 0);
		_map.resize(0);
		_map.resize(_NumberOfRow, TmpVec);
		_mask.resize(0);
		_mask.resize(_NumberOfRow, TmpVec);
	}
	return FailFlag;
}

void map::set_mine_pos(pair<int, int> FirstStep)
{
	srand(time(NULL));
	for (int i = 0; i<_NumberOfMine; i++)
	{
		pair<int, int> TmpIntPair;
		TmpIntPair = make_pair(rand() % _NumberOfRow, rand() % _NumberOfCol);
		while ((TmpIntPair.first == FirstStep.first && TmpIntPair.second == FirstStep.second) || _map[TmpIntPair.first][TmpIntPair.second] == -1)
		{
			TmpIntPair = make_pair(rand() % _NumberOfRow, rand() % _NumberOfCol);
		}
		_map[TmpIntPair.first][TmpIntPair.second] = -1;
		map::count_surrounding_mines(TmpIntPair);
	}
	map::uncover(FirstStep);
}

void map::uncover(pair<int, int> Coord)
{

	_mask[Coord.first][Coord.second] = 1;
	if (Coord.first>0 && _map[Coord.first - 1][Coord.second] != -1 && _mask[Coord.first - 1][Coord.second] != 1)
	{
		_mask[Coord.first - 1][Coord.second] = 1;
		if (_map[Coord.first - 1][Coord.second] == 0)
		{
			pair<int, int> TmpIntPair = make_pair(Coord.first - 1, Coord.second);
			map::uncover(TmpIntPair);
		}
	}//up
	if (Coord.second>0 && _map[Coord.first][Coord.second - 1] != -1 && _mask[Coord.first][Coord.second - 1] != 1)
	{
		_mask[Coord.first][Coord.second - 1] = 1;
		if (_map[Coord.first][Coord.second - 1] == 0)
		{
			pair<int, int> TmpIntPair = make_pair(Coord.first, Coord.second - 1);
			map::uncover(TmpIntPair);
		}
	}//left
	if (Coord.first<_NumberOfRow - 1 && _map[Coord.first + 1][Coord.second] != -1 && _mask[Coord.first + 1][Coord.second] != 1)
	{
		_mask[Coord.first + 1][Coord.second] = 1;
		if (_map[Coord.first + 1][Coord.second] == 0)
		{
			pair<int, int> TmpIntPair = make_pair(Coord.first + 1, Coord.second);
			map::uncover(TmpIntPair);
		}
	}//down
	if (Coord.second<_NumberOfCol - 1 && _map[Coord.first][Coord.second + 1] != -1 && _mask[Coord.first][Coord.second + 1] != 1)
	{
		_mask[Coord.first][Coord.second + 1] = 1;
		if (_map[Coord.first][Coord.second + 1] == 0)
		{
			pair<int, int> TmpIntPair = make_pair(Coord.first, Coord.second + 1);
			map::uncover(TmpIntPair);
		}
	}//right	
}

void map::count_surrounding_mines(pair<int, int> Coord)
{
	if (Coord.first>0 && _map[Coord.first - 1][Coord.second] != -1) _map[Coord.first - 1][Coord.second]++;//up
	if (Coord.second>0 && _map[Coord.first][Coord.second - 1] != -1) _map[Coord.first][Coord.second - 1]++;//left
	if (Coord.first<_NumberOfRow - 1 && _map[Coord.first + 1][Coord.second] != -1) _map[Coord.first + 1][Coord.second]++;//down
	if (Coord.second<_NumberOfCol - 1 && _map[Coord.first][Coord.second + 1] != -1) _map[Coord.first][Coord.second + 1]++;//right	
	if (Coord.first>0 && Coord.second>0 && _map[Coord.first - 1][Coord.second - 1] != -1) _map[Coord.first - 1][Coord.second - 1]++;//up left
	if (Coord.first>0 && Coord.second<_NumberOfCol - 1 && _map[Coord.first - 1][Coord.second + 1] != -1) _map[Coord.first - 1][Coord.second + 1]++;//up right	
	if (Coord.first<_NumberOfRow - 1 && Coord.second>0 && _map[Coord.first + 1][Coord.second - 1] != -1) _map[Coord.first + 1][Coord.second - 1]++;//down left
	if (Coord.first<_NumberOfRow - 1 && Coord.second<_NumberOfCol - 1 && _map[Coord.first + 1][Coord.second + 1] != -1) _map[Coord.first + 1][Coord.second + 1]++;//down right
}

bool map::check_mine(pair<int, int> Coord)
{
	if (_map[Coord.first][Coord.second] == -1) return true;
	else return false;
}

void map::make_flag(pair<int, int>Coord)
{
	_mask[Coord.first][Coord.second] = 2;
	if (_map[Coord.first][Coord.second] == -1) _RemainOfMine--;
	_SurfaceRemainOfMine--;
}
int map::get_remain_number_of_mine()
{
	return _RemainOfMine;
}

int map::get_remain_number_of_mine_on_table()
{
	return _SurfaceRemainOfMine;
}

void map::unmake_flag(pair<int, int> Coord)
{
	_mask[Coord.first][Coord.second] = 0;
	if (_map[Coord.first][Coord.second] == -1) _RemainOfMine++;
	_SurfaceRemainOfMine++;
}

int map::check_mask(pair<int, int> Coord)
{
	return _mask[Coord.first][Coord.second];
}

void map::show_hand()
{
	for (int i = 0; i < _NumberOfRow; i++)
	{
		for (int j = 0; j < _NumberOfCol; j++)
		{
			if (_mask[i][j] == 0 && _map[i][j]== -1 )
			{
				_mask[i][j] = 1;
			}
		}
	}
}

/*int map::get_unmasked()
{
	int result=0;
	for (int i = 0; i < _mask.size(); i++)
	{
		for (int j = 0; j < _mask[i].size(); j++)
		{
			
		}
	}
}*/