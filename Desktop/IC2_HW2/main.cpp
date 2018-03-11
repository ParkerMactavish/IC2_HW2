#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "map.h"

using namespace std;

void CheckNormalCommand(string Command, pair<int, int> Coord, int Col, int Row, int &Flag)
{
	if (Command == "Q" || Command == "q")
	{
		Flag = 0;
		return;
	}
	else if (Command == "R" || Command == "r")
	{
		Flag = 10;
		return;
	}
	else if (Command != "S"&& Command != "s"&&Command != "F"&&Command != "f"&&Command != "U"&&Command != "u")
	{
		Flag = 81;
		return;
	}
	if (Coord.first > Row || Coord.first <= 0)
	{
		Flag = 82;
		return;
	}
	if (Coord.first > Row || Coord.first <= 0)
	{
		Flag = 83;
		return;
	}
}

int Stirng2UnsingedInt(string NumberInString)
{
	int Result = 0;
	if ((NumberInString[0] == 'Q' || NumberInString[0] == 'q') && NumberInString[1] == 0)
	{
		return -3;
	}
	else if ((NumberInString[0] == 'R' || NumberInString[0] == 'r') && NumberInString[1] == 0)
	{
		return -2;
	}
	else
	{
		for (int i = 0; i<NumberInString.size(); i++)
		{
			if (NumberInString[i] >= '0'&&NumberInString[i] <= '9')
			{
				Result *= 10;
				Result += NumberInString[i] - '0';
			}
			else
			{
				Result = -1;
				break;
			}
		}
		return Result;
	}
}

void ProcessInput(int Input, int & Flag)
{
	if (Input == -1 || Input == 0)
	{
		Flag *= 10; Flag += 1;
	}
	else if (Input == -2)
	{
		Flag = 10;
	}
	else if (Input == -3)
	{
		Flag = 0;
	}
	else Flag++;
}

int main()
{
	int Flag = 1, Col, Row, Mine;
	pair<int, int>CurrentStep;
	map MineMap;
	string RowInChar, ColInChar, MinesInChar, Command, TmpStr;
	pair<string, string> CurrentStepInChar;
	system("CLS");
	string welcome("Welcome to Minesweeper.\n Please enter the row number and column number down below.\nYou can type \'Q\' to quit or type \'R\' to restart anytime.\n"),
		RowInputErr("You are entering an illegal row number\nPlease enter an integer bigger than 0\n"),
		ColInputErr("You are entering an illegal column number\nPlease enter an integer bigger than 0\n"),
		MineInputErr("You are entering an illegal Mine number\nPlease enter an integer bigger than 0\n");
	cout << welcome;
	while (Flag != 0)
	{
		if (Flag == 1)
		{
			cout << "Number of rows:";
			cin >> RowInChar;
			Row = Stirng2UnsingedInt(RowInChar);
			ProcessInput(Row, Flag);
		}
		if (Flag == 2)
		{
			cout << "Number of columns:";
			cin >> ColInChar;
			Col = Stirng2UnsingedInt(ColInChar);
			ProcessInput(Col, Flag);
		}
		if (Flag == 3)
		{
			cout << "Number of Mines:";
			cin >> MinesInChar;
			Mine = Stirng2UnsingedInt(MinesInChar);
			ProcessInput(Mine, Flag);
		}
		if (Flag == 4)
		{
			MineMap.set_col(Col);
			MineMap.set_row(Row);
			MineMap.set_mine(Mine);
			bool FailFlag = MineMap.init();
			if (FailFlag)
			{
				Flag = 32;
			}
			else
			{
				cout << "Initialized! Watch your step~\n";
				MineMap.print_map();
				Flag++;
			}
		}
		if (Flag == 5)
		{
			cout << "Please enter the very first step you want to put your foot on:" << endl << "Row:";
			cin >> CurrentStepInChar.first;
			CurrentStep.first = Stirng2UnsingedInt(CurrentStepInChar.first);
			if (CurrentStep.first>Row) Flag = 51;
			else ProcessInput(CurrentStep.first, Flag);
			CurrentStep.first--;
		}
		if (Flag == 6)
		{
			cout << "Column:";
			cin >> CurrentStepInChar.second;
			CurrentStep.second = Stirng2UnsingedInt(CurrentStepInChar.second);
			if (CurrentStep.second>Col) Flag = 61;
			else ProcessInput(CurrentStep.second, Flag);
			CurrentStep.second--;
		}
		if (Flag == 7)
		{
			MineMap.set_mine_pos(CurrentStep);
			MineMap.print_map();
			Flag++;
		}
		if (Flag == 8)
		{
			cout << "Please enter your command:" << endl;
			cin >> Command >> CurrentStepInChar.first >> CurrentStepInChar.second;
			CurrentStep.first = Stirng2UnsingedInt(CurrentStepInChar.first);
			CurrentStep.second = Stirng2UnsingedInt(CurrentStepInChar.second);
			CheckNormalCommand(Command, CurrentStep, Col, Row, Flag);
			CurrentStep.first--; CurrentStep.second--;
			Flag++;
		}
		if (Flag == 9)
		{
			switch (Command[0])
			{
			case 'S': case 's':
				if (MineMap.check_mask(CurrentStep)==1)
				{
					cout << "You have stepped on this square, try another one.";
					Flag = 8;
				}
				else if(MineMap.check_mask(CurrentStep) == 2)
				{
					cout << "You have made a flag on the square, try another one.";
					Flag = 8;
				}
				else if (MineMap.check_mine(CurrentStep))
				{
					MineMap.show_hand();
					MineMap.print_map(); 
					cout << "Oops, you've stepped on a mine." << endl;
					Flag = 10;
				}
				else
				{
					MineMap.uncover(CurrentStep);
					MineMap.print_map();
					Flag = 8;
				}
				break;
			case 'F':case 'f':
				if (MineMap.check_mask(CurrentStep) == 1)
				{
					cout << "You have stepped on this square, try another one." << endl;
					Flag = 8;
				}
				else if (MineMap.check_mask(CurrentStep) == 2)
				{
					cout << "You have made a flag on the square, try another one."<<endl;
					Flag = 8;
				}
				else
				{
					MineMap.make_flag(CurrentStep);
					MineMap.print_map();
					if ((MineMap.get_remain_number_of_mine() == 0 && MineMap.get_remain_number_of_mine_on_table() != 0)||
						(MineMap.get_remain_number_of_mine() != 0 && MineMap.get_remain_number_of_mine_on_table() == 0))
					{
						cout << "Maybe you've mistaken some places as mines?\nDouble check them~" << endl;
					}
					else if (MineMap.get_remain_number_of_mine() == 0 && MineMap.get_remain_number_of_mine_on_table() == 0)
					{
						Flag = 100;
					}
					else Flag = 8;
				}
				break;
			case 'U':case'u':
				if (MineMap.check_mask(CurrentStep) != 2)
				{
					cout << "You didn't even make a flag on the square, try another one." << endl;
					Flag = 8;
				}
				else
				{
					MineMap.unmake_flag(CurrentStep);
					MineMap.print_map();
					Flag = 8;
				}
			}
		}


		if (Flag == 10)
		{
			cout << "Do you want to play another round?";
			cin >> TmpStr;
			while (TmpStr != "Y" && TmpStr != "y" && TmpStr != "N" && TmpStr != "n")
			{
				cout << "Wrong input!\nType \'Y\' to start another round, \'N\' to quit." << endl << "Do you want to play another round?";
				cin >> TmpStr;
			}
			if (TmpStr != "Y" || TmpStr != "y") Flag = 1;
			else Flag = 0;
		}


		if (Flag == 11)
		{
			cout << RowInputErr;
			Flag = 1;
		}
		if (Flag == 21)
		{
			cout << ColInputErr;
			Flag = 2;
		}
		if (Flag == 31)
		{
			cout << MineInputErr;
			Flag = 3;
		}
		if (Flag == 32)
		{
			cout << "Too many mines will kill yourself.\nPlease enter a number between " << 0 << " and " << Row*Col << "." << endl;
			Flag = 3;
		}
		if (Flag == 51)
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Row << endl;
			Flag = 5;
		}
		if (Flag == 61)
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Col << endl;
			Flag = 6;
		}
		if (Flag == 81)
		{
			cout << "Your command starts with a wrong letter" << endl
			<< "It should be something like \"S 3 8\" to STEP on the square in (3, 8)" << endl
			<<"or \"F 8 7\" to FLAG a mine on the square in (8, 7)."<<endl;
			Flag = 8;
		}
		if (Flag == 82)
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Row << endl;
			Flag = 8;
		}
		if (Flag == 83)
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Col << endl;
			Flag = 8;
		}
		if (Flag == 100)
		{
			cout << "You have won this game~";
			Flag = 10;
		}
	}
	cout << "Thanks for your playing~" << endl;
	system("PAUSE");
	return 0;
}