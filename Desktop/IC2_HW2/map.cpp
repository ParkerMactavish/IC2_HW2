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
	for(int i=0; i<_map.size(); i++)
	{
		for(int j=0; j<_map[i].size(); j++)
		{
			if(_mask[i][j]==1)cout<<setw(2)<<_map[i][j];
			else cout<<"  ";
		}
		cout<<endl;
	}
	
	//test
	for(int i=0; i<_map.size(); i++)
	{
		for(int j=0; j<_map[i].size(); j++)
		{
			cout<<setw(2)<<_map[i][j];
		}
		cout<<endl;
	}
}

void map::set_col(int col)
{
	_NumberOfCol=col;
}

void map::set_row(int row)
{
	_NumberOfRow=row;
}

void map::set_mine(int mine)
{
	_NumberOfMine=mine;
}

bool map::init()
{
	int FailFlag=false;
	if(_NumberOfMine>=_NumberOfCol*_NumberOfRow) FailFlag=true;
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
	for(int i=0; i<_NumberOfMine; i++)
	{
		pair<int, int> TmpIntPair;
		TmpIntPair=make_pair(rand()%_NumberOfRow, rand()%_NumberOfCol);
		while((TmpIntPair.first==FirstStep.first && TmpIntPair.second==FirstStep.second)||_map[TmpIntPair.first][TmpIntPair.second]==-1)
		{		
			TmpIntPair=make_pair(rand()%_NumberOfRow, rand()%_NumberOfCol);
		}
		_map[TmpIntPair.first][TmpIntPair.second]=-1;
		map::count_surrounding_mines(TmpIntPair);
	}
	map::uncover(FirstStep);
}

void map::uncover(pair<int, int> Coord)
{
	
	_mask[Coord.first][Coord.second]=1;
	cout<<1;
	if(Coord.first>0 && _map[Coord.first-1][Coord.second]!=-1)
	{
		_mask[Coord.first-1][Coord.second]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first-1, Coord.second);
		map::uncover(TmpIntPair);
		cout<<2;
	}//up
	cout<<"up"<<endl;
	if(Coord.second>0 && _map[Coord.first][Coord.second-1]!=-1)
	{
		_mask[Coord.first][Coord.second-1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first, Coord.second-1);
		map::uncover(TmpIntPair);
	}//left
	if(Coord.first<_NumberOfRow-1 && _map[Coord.first+1][Coord.second]!=-1)
	{
		_mask[Coord.first+1][Coord.second]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first+1, Coord.second);
		map::uncover(TmpIntPair);
	}//down
	if(Coord.second<_NumberOfCol-1 && _map[Coord.first][Coord.second+1]!=-1)
	{
		_mask[Coord.first][Coord.second+1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first, Coord.second+1);
		map::uncover(TmpIntPair);
	}//right	
	if(Coord.first>1 && Coord.second>1 && _map[Coord.first-1][Coord.second-1]!=-1)
	{
		_mask[Coord.first-1][Coord.second-1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first-1, Coord.second-1);
		map::uncover(TmpIntPair);
	}//up left
	if(Coord.first>1 && Coord.second<_NumberOfCol-1 && _map[Coord.first-1][Coord.second+1]!=-1)
	{
		_mask[Coord.first-1][Coord.second+1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first-1, Coord.second+1);
		map::uncover(TmpIntPair);
	}//up right	
	if(Coord.first<_NumberOfRow-1 && Coord.second>1 && _map[Coord.first+1][Coord.second-1]!=-1)
	{
		_mask[Coord.first+1][Coord.second-1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first+1, Coord.second-1);
		map::uncover(TmpIntPair);
	}//down left
	if(Coord.first<_NumberOfRow-1 && Coord.second<_NumberOfCol-1 && _map[Coord.first+1][Coord.second+1]!=-1)
	{
		_mask[Coord.first+1][Coord.second+1]=1;
		pair<int, int> TmpIntPair=make_pair(Coord.first+1, Coord.second+1);
		map::uncover(TmpIntPair);
	}//down right
}

void map::count_surrounding_mines(pair<int, int> Coord)
{
	if(Coord.first>0 && _map[Coord.first-1][Coord.second]!=-1) _map[Coord.first-1][Coord.second]++;//up
	if(Coord.second>0 && _map[Coord.first][Coord.second-1]!=-1) _map[Coord.first][Coord.second-1]++;//left
	if(Coord.first<_NumberOfRow-1 && _map[Coord.first+1][Coord.second]!=-1) _map[Coord.first+1][Coord.second]++;//down
	if(Coord.second<_NumberOfCol-1 && _map[Coord.first][Coord.second+1]!=-1) _map[Coord.first][Coord.second+1]++;//right	
	if(Coord.first>1 && Coord.second>1 && _map[Coord.first-1][Coord.second-1]!=-1) _map[Coord.first-1][Coord.second-1]++;//up left
	if(Coord.first>1 && Coord.second<_NumberOfCol-1 && _map[Coord.first-1][Coord.second+1]!=-1) _map[Coord.first-1][Coord.second+1]++;//up right	
	if(Coord.first<_NumberOfRow-1 && Coord.second>1 && _map[Coord.first+1][Coord.second-1]!=-1) _map[Coord.first+1][Coord.second-1]++;//down left
	if(Coord.first<_NumberOfRow-1 && Coord.second<_NumberOfCol-1 && _map[Coord.first+1][Coord.second+1]!=-1) _map[Coord.first+1][Coord.second+1]++;//down right
}
