//Board header file.
#pragma once
#ifndef _BOARD
#define _BOARD
#include "State.h"
//Using Vectors to store the cells.
#include <vcclr.h>
#include <vector>

#define BLOCK_SIZE 40
#define BOARD_WIDTH 9
#define BOARD_HEIGHT 9

using namespace std;
using namespace System;

//Using a struct cell to store the values of each cell.

struct Cell
{
	int x;
	int y;
};


class Board
{
	Cell cells[BOARD_WIDTH][BOARD_HEIGHT];
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	vector<Cell> emptyCells; // Vector to store empty cells.
	gcroot<Random^> random; // Using gcroot to create Random.
	Cell active; //Declaring a struct.
	int activeCellcolour; //Color indicator for the selected cell.
	int score; //Score
	int highScore; // Int to store High Score.
	State* state; //Declaring a State class.
public:
	Board();
	int cellContent(int, int); //This takes the input of two integers and gives back the value of those in the board.
	void selectCell(int x, int y); // This takes ints as input and checks the whole board for those two inputs, and if any rectangle contains those ints, it will make the shape flicker.
	void initBoard();// Initialising board.
	void draw(); // method to draw board and shapes.
	bool clear(int, int); // Method to claer cells when there are 5 of more in a row.
	void ScoreWriter(int x); // Method to store the score in a text file
	int ScoreReader();// Method to read the score from a text file.
	void activeCellFlicker(); // Method to make the cell flicker.
	void createRandomColours(); // to create 3 random colours after every move.
	void Move(int x, int y); // To move the shapes from one place to another.
	void CheckFreeCells(); //Method to check free cells.
	int getScore() { return score; }; // Score Property.
	int getHighScore() { return highScore; } // High Score property.
	void MovebackAState(); // Undo Method.
	~Board();
};

#endif