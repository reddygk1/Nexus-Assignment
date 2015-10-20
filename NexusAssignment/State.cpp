#include "stdafx.h"
#include "State.h"


State::State()
{
	gameStage = -1;
}

void State::MoveBack( int &score, int(&mBoard)[9][9])
{
	if (gameStage != 0)
	{
		gameStage = gameStage - 1;
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				mBoard[i][j] = lastState[gameStage].CurrentBoard[i][j];
			}
		}
		score = lastState[gameStage].CurrentScore;
		lastState.pop_back();
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("You are at teh start of the game already!!");
	}
	

}

void State::AddCurrent(const int &score, const int(&mBoard)[9][9])
{
	gameStage = gameStage + 1;
	BoardState boardState;

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			boardState.CurrentBoard[i][j] = mBoard[i][j];
		}
	}
	boardState.CurrentScore = score;

	lastState.push_back(boardState);
}
State::~State()
{
}
