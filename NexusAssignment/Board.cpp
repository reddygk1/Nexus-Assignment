//Board.cpp file.
#include "stdafx.h"
#include "Board.h"
#include "Drawer.h"
#include "Astar.h"

//Constuctor.
Board::Board()
{
	initBoard();
	random = gcnew Random();
	state = new State;
}

//Initialising the boared.
void Board::initBoard()
{
	highScore = (ScoreReader()); // Getting the high score form textfile.
	active.x = -1;             // Setting the variables out of boundaries, so nothing happens when we use them in methods. 
	active.y = -1;             //Setting the variables out of boundaries, so nothing happens when we use them in methods.
	activeCellcolour = -1;    //Setting the variables out of boundaries, so nothing happens when we use them in methods.
	score = 0;

	//Drawing the cells.
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			mBoard[i][j] = 0;

			cells[i][j].x = i * BLOCK_SIZE;
			cells[i][j].y = j * BLOCK_SIZE;
		}
	}
	//Checking for freecells.
	CheckFreeCells();
}

//Method to check free cells and store them to Vector.
void Board::CheckFreeCells()
{
	emptyCells.clear();

	for (size_t i = 0; i < BOARD_HEIGHT; i++)
	{
		for (size_t j = 0; j < BOARD_WIDTH; j++)
		{
			if (mBoard[i][j] ==0)
			{
				//Declaring a temorary cell struct to use it as indicator to store in the vector.
				Cell tempCell;
				tempCell.x = i;
				tempCell.y = j;
				emptyCells.push_back(tempCell);
			}

		}
	}
}

// method to move back a state.
void Board::MovebackAState()
{
	//This is to make sure even the selected cell is added to the moveback method.
	if (active.x != -1 && active.y != -1)
	{
		//This is to change theselected cell colour to default.
		mBoard[active.x][active.y] = activeCellcolour;
		active.x = -1;
		active.y = -1;
		activeCellcolour = -1;

	}
	//Stoting them in vector, passing in the board and the score.
	state->MoveBack(score, mBoard);
}

//This is the method to select a cell.
void Board::selectCell(int x, int y)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			Rectangle^ rect = gcnew Rectangle(cells[i][j].x, cells[i][j].y, BLOCK_SIZE, BLOCK_SIZE);

			//check if the selected cell has a shape, if yes make it flicker.
			if (rect->Contains(x, y))
			{
				//Make it Flicker
				if (i == active.x && j == active.y)
				{
					active.x = -1;
					active.y = -1;
					mBoard[i][j] = activeCellcolour;
					activeCellcolour = -1;
				}
				else
				{
					//Checking if they have changes their selection of shape.
					if (mBoard[i][j] != 0)
					{
						if (active.x != -1 && active.y != -1)
						{
							//if yes changing the focus onto the currently selected cell and changing the original cell to stop flickering.
							mBoard[active.x][active.y] = activeCellcolour;
							active.x = -1;
							active.y = -1;
							activeCellcolour = -1;
						}
						active.x = i;
						active.y = j;
						activeCellcolour = mBoard[i][j];
					}
					else
					{
						//Once in boundaries and the cell is empty, Move the cell.
						Move(i, j);						
					}						
				}				
				return;
			}
			delete rect;
		}
	}
}
//Taking the inputs of int and returning the particular cell.
int Board::cellContent(int x, int y)
{
	return mBoard[x][y];
}

//Drawing the shapes.
void Board::draw()
{
		Drawer::draw(*this);
		activeCellFlicker();
}

//Method to write the high score to a text file.
void Board::ScoreWriter(int x)
{
	gcroot<IO::StreamWriter^> sw;
	sw = gcnew IO::StreamWriter("HighScore.txt");
	//Checking the score is greater than the stored high score, if yes write it to text file.
	if (score > highScore)
	{
		sw->WriteLine(x);
	}
	//Close the stream writer.
	sw->Close();
}

//Method to Read the text file.
int Board::ScoreReader()
{
	//Read the text file and return it as INT.
	int srScore;
	gcroot<IO::StreamReader^> sr;
	sr = gcnew IO::StreamReader("HighScore.txt");
	srScore = Convert::ToInt32(sr->ReadLine());
	sr->Close();
	return srScore;
}
//Method to check for the Shapes of same colour are in a row and clearing them and increasing the score.
bool Board::clear(int x,int y)
{
	bool deleted = false;
	std::vector<Cell> eraseShapes;
	int tempX = x;
	int tempY = y;
	int color = mBoard[x][y];
	int tempColor = -1;
	int count = 1;
	
	//Declaring a temporary cell struct to use it as indicator.
	Cell tempCell;
	tempCell.x = tempX;
	tempCell.y = tempY;
	eraseShapes.push_back(tempCell);

	// Checking left for same colour shapes and storing them into the vector.

	do
	{
		//setting the starting point
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9)) // Check if it is inside the boundaries.
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
			else

			{
				// if the colour is not the same then default the temp.
				tempColor = -1;
			}		
	} while (tempColor == color);
	
	//Checking Right for same colour shapes and storing them into the vector.
	tempX = x;
	do
	{
		//setting the starting point
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same colour ina row and deleting them.
	if (count < 5)
	{
		for (int i = 0; i < count -1; i++)
		{
			eraseShapes.pop_back();
		}
		 
	}
	//Setting the variabls back so we can check the other direction
	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Checking Up
	do
	{
		//setting the starting point
		tempY -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down
	tempY = y;
	do
	{
		//setting the starting point
		tempY += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same colour ina row and deleting them.
	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			eraseShapes.pop_back();
		}
	}

	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Checking Up Right Diagonally
	do
	{
		//setting the starting point
		tempY -= 1;
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down Left Diagonally
	tempY = y;
	tempX = x;
	do
	{
		//setting the starting point
		tempY += 1;
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same colour ina row and deleting them.
	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			eraseShapes.pop_back();
		}
	}
	//Setting the variabls back so we can check the other direction
	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Checking Up Left Diagonally
	do
	{
		//setting the starting point
		tempY -= 1;
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down Left Diagonally
	tempY = y;
	tempX = x;
	do
	{
		//setting the starting point
		tempY += 1;
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];// store as temp to compare it with the other shape's colour.
			if (mBoard[tempX][tempY] == color)
			{
				//if the colour is the same then increasin the count.
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			// if the colour is not the same then default the temp.
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same colour ina row and deleting them.
	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			eraseShapes.pop_back();
		}
	}
	//Erasing the shapes after completing the checking.
	if (eraseShapes.size()>=5)
	{
		deleted = true;
		for (size_t i = 0; i < eraseShapes.size(); i++)
		{
			mBoard[eraseShapes[i].x][eraseShapes[i].y] = 0;
		}
		//Updating the score.
		score = score + eraseShapes.size()*10;
	}
	//Update farecells after deleting.
	CheckFreeCells();
	return deleted;
}

//Method to flicker the active cell.
void Board::activeCellFlicker()
{
	if (active.x != -1 && active.y != -1)
	{
		if (mBoard[active.x][active.y] != activeCellcolour)
		{
			mBoard[active.x][active.y] = activeCellcolour;
		}
		else
		{
			mBoard[active.x][active.y] = 7;
		}
		
	}
}
//This is the method to create 3 random clears.
void Board::createRandomColours()
{
	for (int i = 0; i < 3; i++)
	{
		if (!emptyCells.empty())
		{
			int space = random->Next(emptyCells.size());
			int color = random->Next(1, 7);
			mBoard[emptyCells[space].x][emptyCells[space].y] = color;
			int tempX = emptyCells[space].x;
			int tempY = emptyCells[space].y;
			CheckFreeCells();
			clear(tempX, tempY);
			//If there are no more empty cells, display Game over.
			if (emptyCells.empty())
			{
				ScoreWriter(score);				
				System::Windows::Forms::MessageBox::Show("Game Over!!");
			}
		}
		else
		{
			ScoreWriter(score);
			System::Windows::Forms::MessageBox::Show("Game Over!!");
				return;
		}

	}
	//Add to state vector.
	state->AddCurrent(score, mBoard);
	
}
//Method to move the shapes.
void Board::Move(int x, int y)
{
	string Path = aStar::pathFind(active.x, active.y, x, y, mBoard);
	if (Path.length() >0)
	{
		int k; char c;
		int tempX = active.x;
		int tempY = active.y;
		mBoard[tempX][tempY] = 0;
		active.x = -1;
		active.y = -1;
		for (size_t h = 0; h < Path.length(); h++)
		{
			c = Path.at(h);
			k = c - '0';
			tempX = tempX + dx[k];
			tempY = tempY + dy[k];
			mBoard[tempX][tempY] = activeCellcolour;
			draw();
			System::Threading::Thread::Sleep(50);
			mBoard[tempX][tempY] = 0;
		}
		mBoard[tempX][tempY] = activeCellcolour;
		activeCellcolour = -1;
		CheckFreeCells();
		if (!clear(tempX, tempY))
		{
			createRandomColours();
		}
	}
}


Board::~Board()
{
}
