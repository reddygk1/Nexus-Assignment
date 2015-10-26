#include "stdafx.h"
#include "State.h"

//Constructor
State::State()
{
	gameStage = -1;
}

//Writing the method which displays the board from previous state.
void State::MoveBack( int &score, int(&mBoard)[9][9])
{
	//Check if game stage is not 0, which means it is not the start of the game, then do stuff.
	if (gameStage != 0)
	{
		//Copying the board from vector from last state.

		gameStage = gameStage - 1;
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				//gamestage is the indicator to which state to copy from Vector.
				mBoard[i][j] = lastState[gameStage].CurrentBoard[i][j];
			}
		}
		//Copying the score from Vector using game stage as indicator.
		score = lastState[gameStage].CurrentScore;

		//And erasing both from Vector.
		lastState.pop_back();
	}
	//If game stage is 0, which means it is at the start of the game, then display the message.
	else
	{
		System::Windows::Forms::MessageBox::Show("You are at the start of the game already!!");
	}
	

}
//Writing the method which adds the board from current state to Vector.

void State::AddCurrent(const int &score, const int(&mBoard)[9][9])
{
	gameStage = gameStage + 1;
	BoardState boardState;
	//Copying the current state of the board to vector.
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			boardState.CurrentBoard[i][j] = mBoard[i][j];
		}
	}
	//copying the current score to vector.
	boardState.CurrentScore = score;

	//And adding both to Vector.
	lastState.push_back(boardState);
}
State::~State()
{
}
