#pragma once

#include <vector>

using namespace std;

struct BoardState
{
	int CurrentScore;
	int CurrentBoard[9][9];
};
class State
{
	vector<BoardState> lastState;

public:
	State();
	int gameStage;
	void MoveBack( int &score, int (&mBoard)[9][9]);
	void AddCurrent(const int &score, const int(&mBoard)[9][9]);

	~State();
};

