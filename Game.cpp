#include "Game.h"


Game::Game()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gameBoard[i][j] = 0;
		}
		std::cout << std::endl;
	}
	
	playerPosX = 0;
	playerPosY = 5;
	gameBoard[0][5] = 1;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << gameBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void Game::drawBoard(){

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << gameBoard[i][j] << " ";
		}

		std::cout << std::endl;
	}

}

void Game::clearScreen(){
	for (int i = 0; i < 30; i++)
		std::cout << std::endl;
}

void Game::updateBoard(){

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gameBoard[i][j] = gameBoard[i + 1][j];
		}
	}

	srand(time(NULL));

	/* generate secret number between 1 and 10: */

	for (int i = 0; i < 10; i++)
	{
		int p = rand() % 10 + 1;

		if (p != 1)
			p = 0;
		else
			p = 2;

		gameBoard[9][i] = p;
	}

	
	gameBoard[playerPosX][playerPosY] = 1;
}

void Game::mainLoop(){

	bool exit = false;

	while (!exit)
	{
		system("clear");
		updateBoard();
		drawBoard();
		Sleep(500);
	}

}

Game::~Game()
{
}
