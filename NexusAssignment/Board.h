#pragma once
#ifndef _BOARD
#define _BOARD

#include <vcclr.h>
#include <vector>

#define BLOCK_SIZE 40
#define BOARD_WIDTH 9
#define BOARD_HEIGHT 9

using namespace std;
using namespace System;

struct Cell
{
	int x;
	int y;

};

class Board
{
	Cell cells[BOARD_WIDTH][BOARD_HEIGHT];
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	vector<Cell> emptyCells;
	gcroot<Random^> random;
	Cell active;
	int activeCellcolour;
	int score;
	int highScore;
public:
	Board();
	int cellContent(int, int);
	void selectCell(int x, int y);
	void initBoard();
	void draw();
	bool clear(int, int);
	void ScoreWriter(int x);
	int ScoreReader();
	void activeCellFlicker();
	void createRandomColours();
	void Move(int x, int y);
	void CheckFreeCells();
	int getScore() { return score; };
	int getHighScore() { return highScore; }
	~Board();
};

#endif