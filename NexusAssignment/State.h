//Star class header file.
#pragma once

//Using Vectors to store the game states.
#include <vector>

using namespace std;
//Declaring a struct that stores the board and score at each stage.
struct BoardState
{
	int CurrentScore;
	int CurrentBoard[9][9];
};

class State
{
	//Declaring a Vector.
	vector<BoardState> lastState;

public:
	State();
	//Game stage is the indicator for the number of moves/states.
	int gameStage;
	//Move back is the method that displays the previos state of the game from the vector.
	void MoveBack( int &score, int (&mBoard)[9][9]);

	//This is to add the current state each time.
	void AddCurrent(const int &score, const int(&mBoard)[9][9]);

	~State();
};

