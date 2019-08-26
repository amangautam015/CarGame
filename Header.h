#pragma once

#include<iostream>
#include<Windows.h>
#include<winuser.h>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>

using namespace std;

class ControlKeys {
public:
	int Right;
	int Left;
	ControlKeys();
};


class Car {
public:
	int left_b;
	int right_b;
	int top_b;
	int bottom_b;
	int posX;
	int posY;
	int max_i;
	string shape;
	Car();
};

class Obstacle {
public:
	int posX;
	int posY;
	string shape;
	Obstacle();
	void setPosition(int x, int y);
};

class Game {
public:
	Car car;
	vector<Obstacle> obs;
	int bottom_limit, left_limit, top_limit, right_limit;
	vector<string> game_lines; //Each row of game frame
	vector<string> player; //Player rows
	Game();
	void DisplayGame();
	void DisplayPlayer();
};


