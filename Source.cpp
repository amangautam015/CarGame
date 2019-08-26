#include "Header.h"

#define LENGTH  5

void setScreen();
void MulString(string& s, int i);
void gotoxy(int x, int y);
void displace_cursor(int delta_x, int delta_y);
double playGame(Game& game, int sleep);
void ClearScreen();
void ChangePosition(int k, Game& game);
void moveAllObstacle(Game& game);
void addObstacle(Game& game, int ep);
SHORT x = 0, y = 0, init_x, init_y;
SHORT bottom_limit, top_limit, left_limit, right_limit;
string test = "*";
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO area;
DWORD cellCount;
int extcrsh = 1;


int main() {
	setScreen(); //Maximise Console
	Game game;
	//game.DisplayGame();
	//game.DisplayGame();
	cout<<playGame(game,10)<<endl;
	cout << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}


//Play main Game
double playGame(Game& game, int sleep) {
	double score = 0;
	int enem = 1;
	int move = 1;
	while (1) {
		if (extcrsh != 1) {
			cout << "CAR CRASH\n";
			return score;
		}
		game.DisplayGame();
		if (GetAsyncKeyState(VK_LEFT)) {
			if (game.car.posX == 1) {
				cout << "CAR CRASH\n";
				return score;
			}
				
			ChangePosition(-1, game);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (game.car.posX == right_limit - game.car.right_b) {
				cout << "CAR CRASH\n";
				return score;
			}
		
			ChangePosition(1, game);
			
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}

		if (enem % 3 == 0) {
			enem = 0;
            //Put Obsticle

			int entringObstacle_X = rand() % ((right_limit-LENGTH-2) - 2 + 1) + 2;
			addObstacle(game, entringObstacle_X);
		    
		}
		
			
			moveAllObstacle(game);

		
		enem++;
	
		

		Sleep(sleep);
		ClearScreen();
	}
	return score;
}



void addObstacle(Game &game,int ep) {
	Obstacle obs;
	obs.setPosition(ep, 0);
	int f = 0;
	game.obs.push_back(obs);
	for (int i = 0;i < right_limit - 2;i++) {
		if (i >= ep && f < LENGTH) {
			(game.game_lines[0])[i] = (game.obs.back()).shape[f];
			f++;
		}
	}
}

void MObstacle(Game& game, int ep) {
	Obstacle obs;
	obs.setPosition(ep, 0);
	int f = 0;
	game.obs.push_back(obs);
	for (int i = 0;i < right_limit - 2;i++) {
		if (i >= ep && f < LENGTH) {
			(game.game_lines[0])[i] = (game.obs.back()).shape[f];
			f++;
		}
	}
}

void moveAllObstacle(Game& game) {
	for (int j = 0; j < game.obs.size();j++) {
		int f = 0;
		
		for (int i = 0;i < right_limit - 2;i++) {

			if (i >= game.obs[j].posX && f < LENGTH) {
				(game.game_lines[game.obs[j].posY])[i] = ' ';
				if (game.obs[j].posY != game.car.posY - 1) {
					(game.game_lines[game.obs[j].posY + 1])[i] = (game.obs[j]).shape[f];
					
				}
				else {
					if (game.car.posX <= game.obs[j].posX + LENGTH - 1 && game.obs[j].posX <= game.car.posX + game.car.right_b) {
						extcrsh = 0;
						return;
					}
				    
					
					break;
				}
				f++;

			}
		}
		
		if (game.obs[j].posY != game.car.posY - 1 ) {
			game.obs[j].setPosition(game.obs[j].posX, game.obs[j].posY + 1);
		}
		else {
			game.obs.erase(game.obs.begin() + j);
			for (int k = 0;k < right_limit - 1;k++) {
				game.game_lines[game.car.posY - 1][k] = ' ';
			}
			game.game_lines[game.car.posY - 1][0] = '|';
			game.game_lines[game.car.posY - 1][right_limit] = '|';
			game.game_lines[game.car.posY - 1][right_limit + 1] = '\n';
		}
	}
}


void ChangePosition(int k ,Game& game) {
	char temp;
	/*temp = (game.game_lines[game.car.posY])[game.car.posX];
	(game.game_lines[game.car.posY])[game.car.posX] = (game.game_lines[game.car.posY])[game.car.posX + k];
	(game.game_lines[game.car.posY])[game.car.posX + k] = temp;
	game.car.posX = game.car.posX + k;*/
	if (k == -1) {
		for (int i = 0;i <= game.car.bottom_b;i++) {
			(game.game_lines[game.car.posY + i]).erase(1, 1);
			(game.game_lines[game.car.posY + i]).insert(right_limit - 2, " ");
		}
		game.car.posX--;
	}
	else {
		for (int i = 0;i <= game.car.bottom_b;i++) {
			(game.game_lines[game.car.posY + i]).erase(right_limit, right_limit);
			(game.game_lines[game.car.posY + i]).insert(1, " ");
			(game.game_lines[game.car.posY + i])[right_limit] = '|';
		}
		game.car.posX++;
	}
	
}

//Does str*i Example : "aman"*2 = amanaman
void MulString(string& s, int i)
{
	string k = s;
	while (i != 0) {
		s = k + s;
		i--;
	}
}

//Set Console to Full Screen .Get Console Parameters
void setScreen()
{
	//SetConsoleDisplayMode(hStdOut, CONSOLE_FULLSCREEN_MODE, 0);
	srand(time(NULL));
	GetConsoleScreenBufferInfo(hStdOut, &area);
	bottom_limit = area.srWindow.Bottom;
	top_limit = area.srWindow.Top;
	left_limit = area.srWindow.Left;
	right_limit = area.srWindow.Right;
	init_x = (bottom_limit + 1) / 2;
	init_y = (right_limit + 1) / 2;
	cellCount = area.dwSize.X * area.dwSize.Y;
	//gotoxy(init_x, init_y);
}

//Goto coords on Console
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displace_cursor(int delta_x, int delta_y)
{
	gotoxy(init_x + delta_x, init_y + delta_y);
	init_x = init_x + delta_x;
	init_y = init_y + delta_y;
}

void ClearScreen()
{
	COORD  homeCoords = { 0,0 };
	DWORD  countt;
	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&countt
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}