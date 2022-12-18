#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
using namespace std;

char board[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
bool draw = false;
char first_mark = 'X';
char second_mark = 'O';
string first_player = "Player 1";
string second_player = "Player 2";
char current_mark = first_mark;
string current_player = first_player;

int numeric_input()
{
	int n = 0;
	int temp = 0;
	do
	{
		temp = scanf("%d", &n);
		if (temp != 1)
			cout << "In according to instruction, please type in a number!\n";
		while (getchar() != '\n');
	} while (temp != 1);

	return n;
}

void display_board() //A function to draw current gameboard.
{
	string interspace = "_____|_____|_____\n";
	string free_space = "     |     |     \n";

	system("cls");
	cout << "\tTic Tac Toe\n\n";
	cout << first_player << " (" << first_mark << ") - " << second_player << " (" << second_mark << ")\n\n";
	cout << free_space;
	cout << "  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << endl;
	cout << interspace + free_space;
	cout << "  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << endl;
	cout << interspace + free_space;
	cout << "  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << endl;
	cout << free_space << endl;
}

void change_player()
{
	if (current_mark == first_mark)
	{
		current_mark = second_mark;
		current_player = second_player;
	}
	else
	{
		current_mark = first_mark;
		current_player = first_player;
	}

}

bool update_gamestatus()
{	// horizontal cases.
	if ((board[1] == board[2] && board[1] == board[3]) || (board[1] == board[4] && board[1] == board[7]) || (board[2] == board[5] && board[2] == board[8]))
	{
		return false;
	}
	// vertical cases.
	else if ((board[3] == board[6] && board[1] == board[9]) || (board[4] == board[5] && board[4] == board[6]) || (board[7] == board[8] && board[7] == board[9]))
	{
		return false;
	}
	// diagonal cases.
	else if ((board[1] == board[5] && board[1] == board[9]) || (board[3] == board[5] && board[3] == board[7]))
	{
		return false;
	}
	for (int i = 1; i <= 9; i++)
		if (board[i] != 'X' && board[i] != 'O')
		{
			return true;

		}
	draw = true;
	return false;
}



int main() 
{ //A function which allows user make next step to glory and win the game.
	int choice = 0;
	int move = 0;
	int left_combos = 362880; //9! possible combinations at begin of game
	int factorial = 10;
	int undo_combos = 362880;
	char undo_board[10] = {0};
	bool undo_limiter = false;

	do {
	system("cls");
	cout << "\tTic Tac Toe\n\n";
	cout << "\t=== Menu ===\n\n";
	cout << "1. Player vs. AI" << endl;
	cout << "2. Local co-op" << endl;
	cout << "3. Session summary" << endl;
	cout << "4. Set names of players (default: Player 1 & Player 2)" << endl;
	cout << "5. Set symbols (default: cross&circle)" << endl;
	cout << "6. Exit" << endl;
	choice = numeric_input();

	switch (choice) {
		case 1:
			cout << "Tutaj powinno byc YOU VS AI\n\n";
			system("pause");
			break;
		case 2:
			while (update_gamestatus())
			{
				display_board();
				cout << "Left " << left_combos << " possible combinations.\n";
				cout << current_player + " please enter your field.\n";
				do
				{
					move = numeric_input();
					if (move > 9 || move < 0)
					{
						cout << "Please enter valid field number.\n";
					}
					else if (move == 0 && undo_limiter == false)
					{
						for (int i = 0; i < 10; i++)
						{
							board[i] = undo_board[i];
						}
						break;
					}
					else if ((board[move] == first_mark || board[move] == second_mark) && move != 0)
					{
						cout << "This field has been already taken!\n";
					}
					else if (undo_limiter == true)
					{
						cout << "Please don't abuse the undo function.\n";
					}
				} while ((move > 9 || move < 1) || (board[move] == first_mark || board[move] == second_mark));
				for (int i = 1; i < 10; i++)
				{
					undo_board[i] = board[i];
				}
				undo_combos = left_combos;
				if (move == 0 && undo_limiter == false)
				{
					left_combos *= factorial;
					factorial += 1;
					undo_limiter = true;
				}
				else if (move != 0)
				{
					factorial -= 1;
					left_combos /= factorial;
					undo_limiter = false;
				}
				board[move] = current_mark;
				change_player();
				update_gamestatus();
			}

			display_board();
			if (current_mark == first_mark && draw == false)
			{
				cout << second_player << " (" << second_mark << ") has won.\n\n";
			}
			if (current_mark == second_mark && draw == false)
			{
				cout << first_player << " (" << first_mark << ") has won.\n\n";
			}
			if (draw == true)
			{
				cout << "Unfortunately, it is a draw and there is no winner.\n\n";
			}
			//for (int i = 48; i < 58; i++)
			//{
			//	board[i] = i;
			//}
			system("pause");
			break;
		case 3:
			cout << "Session summary\n\n";
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "Please enter name for the first player...\n";
			cin >> first_player;
			system("cls");
			cout << "Please enter name for the second player...\n";
			cin >> second_player;
			break;
		case 5:
			system("cls");
			cout << "Please enter symbol that will be used by the first player...\n";
			cin >> first_mark;
			system("cls");
			cout << "Please enter symbol that will be used by the second player...\n";
			cin >> second_mark;
			current_mark = first_mark;
			break;
		case 6:
			cout << "Goodbye!\n\n";
			system("pause");
			break;
		default:
			cout << "Please enter correct action number (1-6).\n\n";
			system("pause");
		}
	} while (choice != 6);
}

//c4 daily history c5 AI, erase pamiêæ po gierce, refactor