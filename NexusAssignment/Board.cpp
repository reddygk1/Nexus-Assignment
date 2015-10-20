#include "stdafx.h"
#include "Board.h"
#include "Drawer.h"
#include "Astar.h"


Board::Board()
{
	initBoard();
	random = gcnew Random();
	state = new State;
}

void Board::initBoard()
{
	highScore = (ScoreReader());
	active.x = -1;
	active.y = -1;
	activeCellcolour = -1;
	score = 0;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			mBoard[i][j] = 0;

			cells[i][j].x = i * BLOCK_SIZE;
			cells[i][j].y = j * BLOCK_SIZE;
		}
	}
	CheckFreeCells();
}

void Board::CheckFreeCells()
{
	emptyCells.clear();

	for (size_t i = 0; i < BOARD_HEIGHT; i++)
	{
		for (size_t j = 0; j < BOARD_WIDTH; j++)
		{
			if (mBoard[i][j] ==0)
			{
				Cell tempCell;
				tempCell.x = i;
				tempCell.y = j;
				emptyCells.push_back(tempCell);
			}

		}
	}
}

void Board::MovebackAState()
{
	if (active.x != -1 && active.y != -1)
	{
		mBoard[active.x][active.y] = activeCellcolour;
		active.x = -1;
		active.y = -1;
		activeCellcolour = -1;

	}
	state->MoveBack(score, mBoard);
}

void Board::selectCell(int x, int y)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			Rectangle^ rect = gcnew Rectangle(cells[i][j].x, cells[i][j].y, BLOCK_SIZE, BLOCK_SIZE);

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
					if (mBoard[i][j] != 0)
					{
						if (active.x != -1 && active.y != -1)
						{
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
						Move(i, j);
						
					}
						
				}
				
				return;
			}
			delete rect;
		}
	}
}

int Board::cellContent(int x, int y)
{
	return mBoard[x][y];
}

void Board::draw()
{
		Drawer::draw(*this);
		activeCellFlicker();
}

void Board::ScoreWriter(int x)
{
	gcroot<IO::StreamWriter^> sw;
	sw = gcnew IO::StreamWriter("HighScore.txt");
	if (score > highScore)
	{
		sw->WriteLine(x);
	}
	
	sw->Close();
}

int Board::ScoreReader()
{
	int srScore;
	gcroot<IO::StreamReader^> sr;
	sr = gcnew IO::StreamReader("HighScore.txt");
	srScore = Convert::ToInt32(sr->ReadLine());
	sr->Close();
	return srScore;
}

bool Board::clear(int x,int y)
{
	bool deleted = false;
	std::vector<Cell> eraseShapes;
	int tempX = x;
	int tempY = y;
	int color = mBoard[x][y];
	int tempColor = -1;
	int count = 1;
	

	Cell tempCell;
	tempCell.x = tempX;
	tempCell.y = tempY;
	eraseShapes.push_back(tempCell);

	// Checking left

	do
	{
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
			else

			{
				tempColor = -1;
			}		
	} while (tempColor == color);
	
	//Checking Right
	tempX = x;
	do
	{
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same in a row
	if (count < 5)
	{
		for (int i = 0; i < count -1; i++)
		{
			eraseShapes.pop_back();
		}
		 
	}

	count = 1;
	tempColor = 0;
	tempX = x;
	tempY = y;

	//Checking Up
	do
	{
		tempY -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down
	tempY = y;
	do
	{
		tempY += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same in a row
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
		tempY -= 1;
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down Left Diagonally
	tempY = y;
	tempX = x;
	do
	{
		tempY += 1;
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same in a row
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

	//Checking Up Left Diagonally
	do
	{
		tempY -= 1;
		tempX -= 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking Down Left Diagonally
	tempY = y;
	tempX = x;
	do
	{
		tempY += 1;
		tempX += 1;
		if ((tempX >= 0 && tempX < 9) && (tempY >= 0 && tempY < 9))
		{
			tempColor = mBoard[tempX][tempY];
			if (mBoard[tempX][tempY] == color)
			{
				count = +1;
				Cell tempCell;
				tempCell.x = tempX;
				tempCell.y = tempY;
				eraseShapes.push_back(tempCell);
			}
		}
		else

		{
			tempColor = -1;
		}
	} while (tempColor == color);

	//Checking if there are 5 same in a row
	if (count < 5)
	{
		for (int i = 0; i < count - 1; i++)
		{
			eraseShapes.pop_back();
		}
	}

	if (eraseShapes.size()>=5)
	{
		deleted = true;
		for (size_t i = 0; i < eraseShapes.size(); i++)
		{
			mBoard[eraseShapes[i].x][eraseShapes[i].y] = 0;
		}
		score = score + eraseShapes.size()*10;
	}
	CheckFreeCells();
	return deleted;
}

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
	state->AddCurrent(score, mBoard);
	
}
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
