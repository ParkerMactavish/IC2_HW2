#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "map.h"

using namespace std;

void CheckCommand(string Command, int &Flag)//this function is to check the first character of the input command in the form of "Char Int Int"
{
	if (Command == "Q" || Command == "q")//the command to quit the game
	{
		Flag = 0;
		return;
	}
	else if (Command == "R" || Command == "r")//the command to restart the game
	{
		Flag = 10;
		return;
	}
	else if (Command != "S"&& Command != "s"&&Command != "F"&&Command != "f"&&Command != "U"&&Command != "u")//3 types of Char for typical command: Step/Flag/Unflag
	{
		Flag = 81;
		return;
	}
	else
	{
		Flag = 80;
		return;
	}
}

void CheckStep(pair<int, int>Coord, int Col, int Row, int &Flag)//check if the input coordinate is valid
{
	if (Coord.first > Row || Coord.first <= 0)
	{
		Flag = 82;
		return;
	}
	else if (Coord.first > Row || Coord.first <= 0)
	{
		Flag = 83;
		return;
	}
	else Flag = 9;
}

int Stirng2UnsingedInt(string NumberInString)//this function is to convert the input string to integer, and altogether check the special command such as quit/restart
{
	int Result = 0;
	if ((NumberInString[0] == 'Q' || NumberInString[0] == 'q') && NumberInString[1] == 0)//command of quit
	{
		return -3;
	}
	else if ((NumberInString[0] == 'R' || NumberInString[0] == 'r') && NumberInString[1] == 0)//command of restart
	{
		return -2;
	}
	else
	{
		for (int i = 0; i<NumberInString.size(); i++)//string to int
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

void ProcessInput(int Input, int & Flag)//Check the input before the "Char Int Int" command stage
{
	if (Input == -1 || Input == 0)//if the result of Stirng2UnsingedInt is 0 or N/A then put it to warning stage
	{
		Flag *= 10; Flag += 1;//warning stage is usually set as original flag*10+1. Like stage 5, we have warning stage at stage 51
	}
	else if (Input == -2)//restarting stage is at stage 10
	{
		Flag = 10;
	}
	else if (Input == -3)//quitting requires the flag to become 0
	{
		Flag = 0;
	}
	else Flag++;
}

int main()
{
	int Flag = 1, Col, Row, Mine;//set the flag; decalre Column, Row, and Mine for later usage
	pair<int, int>CurrentStep;//declare the pair of int for later usage as coordinate
	map MineMap;//declare a self-defined object "map"
	string RowInChar, ColInChar, MinesInChar, Command, TmpStr;//declare strings for raw input
	pair<string, string> CurrentStepInChar;//declare pair of strings for raw input
	system("CLS");
	string welcome("Welcome to Minesweeper.\n Please enter the row number and column number down below.\nYou can type \'Q\' to quit or type \'R\' to restart anytime.\n"),
		RowInputErr("You are entering an illegal row number\nPlease enter an integer bigger than 0\n"),
		ColInputErr("You are entering an illegal column number\nPlease enter an integer bigger than 0\n"),
		MineInputErr("You are entering an illegal Mine number\nPlease enter an integer bigger than 0\n");//declare the string for later usage in error message
	cout << welcome;
	while (Flag != 0)
	{
		if (Flag == 1)//Stage 1 get the raw data of the number of rows and convert it into numeric
		{
			cout << "Number of rows:";
			cin >> RowInChar;
			Row = Stirng2UnsingedInt(RowInChar);
			ProcessInput(Row, Flag);
		}
		if (Flag == 2)//Stage 2 get the raw data of the number of columns and convert it into numeric
		{
			cout << "Number of columns:";
			cin >> ColInChar;
			Col = Stirng2UnsingedInt(ColInChar);
			ProcessInput(Col, Flag);
		}
		if (Flag == 3)//Stage 3 get the raw data of the number of mines and convert it into numeric
		{
			cout << "Number of Mines:";
			cin >> MinesInChar;
			Mine = Stirng2UnsingedInt(MinesInChar);
			ProcessInput(Mine, Flag);
		}
		if (Flag == 4)//set up the mine map and initialize the map
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
				system("PAUSE");
				MineMap.print_map();
				Flag++;
			}
		}
		if (Flag == 5)//open up the game, first to input the row number
		{
			cout << "Please enter the very first step you want to put your foot on:" << endl << "Row:";
			cin >> CurrentStepInChar.first;
			CurrentStep.first = Stirng2UnsingedInt(CurrentStepInChar.first);
			if (CurrentStep.first>Row) Flag = 51;
			else ProcessInput(CurrentStep.first, Flag);
			CurrentStep.first--;
		}
		if (Flag == 6)//second to input the column numbers
		{
			cout << "Column:";
			cin >> CurrentStepInChar.second;
			CurrentStep.second = Stirng2UnsingedInt(CurrentStepInChar.second);
			if (CurrentStep.second>Col) Flag = 61;
			else ProcessInput(CurrentStep.second, Flag);
			CurrentStep.second--;
		}
		if (Flag == 7)//generate the position of mines
		{
			MineMap.set_mine_pos(CurrentStep);
			MineMap.print_map();
			Flag++;
		}
		if (Flag == 8)//go into the Char Int Int command stage, first the Char
		{
			cout << "Please enter your command:" << endl;
			cin >> Command;
			CheckCommand(Command, Flag);
		}
		if (Flag == 80)//then the Int, Int
		{
			cin >> CurrentStepInChar.first >> CurrentStepInChar.second;
			CurrentStep.first = Stirng2UnsingedInt(CurrentStepInChar.first);
			CurrentStep.second = Stirng2UnsingedInt(CurrentStepInChar.second);
			CheckStep(CurrentStep, Col, Row, Flag);
			CurrentStep.first--; CurrentStep.second--;
		}
		if (Flag == 9)//see if the player has stepped on a mine, or has finished the game
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


		if (Flag == 10)//restarting stage, see if the player wants another round
		{
			cout << "Do you want to play another round?";
			cin >> TmpStr;
			while (TmpStr != "Y" && TmpStr != "y" && TmpStr != "N" && TmpStr != "n")
			{
				cout << "Wrong input!\nType \'Y\' to start another round, \'N\' to quit." << endl << "Do you want to play another round?";
				cin >> TmpStr;
			}
			if (TmpStr == "Y" || TmpStr == "y")
			{
				system("CLS");
				Flag = 1;
			}
			else Flag = 0;
		}


		if (Flag == 11)//incorrect row number error
		{
			cout << RowInputErr;
			Flag = 1;
		}
		if (Flag == 21)//incorrect column number error
		{
			cout << ColInputErr;
			Flag = 2;
		}
		if (Flag == 31)//incorrect mine number error1
		{
			cout << MineInputErr;
			Flag = 3;
		}
		if (Flag == 32)//incorrect mine number error2
		{
			cout << "Too many mines will kill yourself.\nPlease enter a number between " << 0 << " and " << Row*Col << "." << endl;
			Flag = 3;
		}
		if (Flag == 51)//incorrect row number error when starting
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Row << endl;
			Flag = 5;
		}
		if (Flag == 61)//incorrect column number error when starting
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Col << endl;
			Flag = 6;
		}
		if (Flag == 81)//incorrect command error
		{
			cout << "Your command starts with a wrong letter" << endl
			<< "It should be something like \"S 3 8\" to STEP on the square in (3, 8)" << endl
			<<"or \"F 8 7\" to FLAG a mine on the square in (8, 7)."<<endl;
			Flag = 8;
		}
		if (Flag == 82)//row number out of range/Not a number error
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Row << endl;
			Flag = 8;
		}
		if (Flag == 83)//column number out of range/Not a number error
		{
			cout << "You are entering an illegal row number\nPlease enter an integer in the range of 1 ~" << Col << endl;
			Flag = 8;
		}
		if (Flag == 100)//finish stage
		{
			cout << "You have won this game~";
			Flag = 10;
		}
	}
	system("CLS");
	cout << "Thanks for your playing~" << endl;//Danke stage
	system("PAUSE");
	return 0;
}