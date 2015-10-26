//Drawer CPP File.
#include "stdAfx.h"
#include "Drawer.h"

// Initialising the Drawer, and declaring graphincs as we are using them.
void Drawer::init(System::Drawing::Graphics^ g)
{
	formGraphics = g;
}

//Draw method which takes Board as the input.
void Drawer::draw(Board &b)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			//This draws 9/9 sqaures of size 40/40.

			TextureBrush^ brush = gcnew TextureBrush(ball[b.cellContent(i,j)]);
			formGraphics->FillRectangle(brush, i * 40, j * 40, 40, 40);
			delete brush;
		}
	}
}