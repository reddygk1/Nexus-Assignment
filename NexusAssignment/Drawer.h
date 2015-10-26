//Drawer Header file.
#pragma once
#ifndef _DRAWER
#define _DRAWER
#include "Board.h"

using namespace System::Drawing;
//Declaring the images for the game.
ref class Drawer
{
	static array<Bitmap^>^ ball = {
		(Bitmap^)Image::FromFile("img\\free.png"),
		(Bitmap^)Image::FromFile("img\\blue.png"),
		(Bitmap^)Image::FromFile("img\\red.png"),
		(Bitmap^)Image::FromFile("img\\green.png"),
		(Bitmap^)Image::FromFile("img\\yellow.png"),
		(Bitmap^)Image::FromFile("img\\purple.png"),
		(Bitmap^)Image::FromFile("img\\bleau.png"),
		(Bitmap^)Image::FromFile("img\\selected.png"),
	};
	//Also declaring pens(graphics) for different shapes (Outlines etc.)
	static Pen^ border = gcnew Pen(Color::White);
	static Pen^ outline = gcnew Pen(Color::Black);
	static Graphics^ formGraphics;
public:
	//Methods.
	static void init(Graphics^);
	static void draw(Board&);
};

#endif