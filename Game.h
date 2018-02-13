#pragma once

#include <stdio.h>      
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <Windows.h>
#include<conio.h>

class Game
{
public:
	Game();
	void updateBoard();
	void drawBoard();
	void mainLoop();
	void clearScreen();
	~Game();
private:
	int playerPosX;
	int playerPosY;
	int gameBoard[10][10];
	int score = 0;
};

