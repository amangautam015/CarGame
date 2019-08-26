#pragma once
#include "Header.h"



ControlKeys::ControlKeys()
{
	Right = VK_RIGHT;
	Left = VK_LEFT;
}

Car::Car() {
	shape = " |*|\n  |\n|***|";
}


Game::Game()
{	
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO area;
	GetConsoleScreenBufferInfo(hStdOut, &area);
	bottom_limit = area.srWindow.Bottom - 10; //-10 Bottom Offset
	top_limit = area.srWindow.Top;
	left_limit = area.srWindow.Left;
	right_limit = area.srWindow.Right;
	//cout << right_limit  << " " << bottom_limit  << endl;
	//cout << right_limit/2 << " " << bottom_limit/2 << endl;
	int j = -1, max = 0, h = 0 ;
	for (int i = 0; i < (car.shape).length() ; i++) {
		if (car.shape[i] == '\n') {
			player.push_back("");
			j++;
			continue;	
		}
		if (i == 0) {
			player.push_back("");
			j++;
		}
		player[j] = player[j] + car.shape[i];
	}
	car.bottom_b = j;
	car.top_b = 0;
	j = 0;
	for (auto i = player.begin(); i != player.end(); ++i)
	{
		h = (*i).length();
		if (h > max) {
			max = h;
			car.max_i = j;
		}
		j++;
	}
	car.left_b = 0;
	car.right_b = max;
	for (int i = 0; i < bottom_limit; i++) {
		game_lines.push_back("|");
		for (int j = 0;j < right_limit - 1;j++) {
			if (i ==(int)((float)(bottom_limit / 1.2)) && j == right_limit / 2) {
				//cout << j << " " << i << endl;
				car.posX = j + 1;
				car.posY = i;
				  
			}

			game_lines[i] = game_lines[i] + " ";
		}
		game_lines[i] = game_lines[i] + "|\n";
	}
	for (int i = 0;i < bottom_limit;i++) {
		for (int j = 0;j < right_limit - 1; j++) {
			if (i == car.posY && j == car.posX) {
				int f = 0;
				for (int k = 0;k < player.size();k++) {
					for (f = 0;f < player[k].length(); f++) {
						(game_lines[i])[j+f] = (player[k])[f];
					}
					i++;
				}
				j = j + f;
			}
		}
	}
	
}

void Game::DisplayGame()
{
	for (auto i = game_lines.begin(); i != game_lines.end(); ++i)
		cout << *i;
}
void Game::DisplayPlayer()
{
	for (auto i = player.begin(); i != player.end(); ++i)
		cout << *i <<endl;

	cout << car.max_i << " " << car.right_b << " " << car.bottom_b << endl;
}

Obstacle::Obstacle()
{
	posX = 1;
	posY = 1;
	shape = "=====";

}

void Obstacle::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}
