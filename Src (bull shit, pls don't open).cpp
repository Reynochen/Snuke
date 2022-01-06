#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <ctime>

//Map
const int side = 20;
const int SIZE = side * side;

char gameField[SIZE];

int dif;

//Food
int foodX;
int foodY;

//Tail
int Length = 0;

//Player
int score = 0;

int dirX = 0;
int dirY = -1;

short int bodyX[400];
short int bodyY[400];

char stateWalk = 'w';

void RandFood()
{
	do
	{
		bool tailCol = false;
		foodY = rand() % side;
		foodX = rand() % side;

		for (int i = 1; i <= Length; i++)
			if (foodX == bodyX[i] && foodY == bodyY[i])
				tailCol = true;
				

		if (!(foodY == 0 || foodY == side - 1 || foodX == 0 || foodX == side - 1 || tailCol))
			break;
	} while (true);
}

bool Collision()
{
	for (int i = 1; i <= Length; i++)
		if (bodyX[0] == bodyX[i] && bodyY[0] == bodyY[i])
			return true;

	return bodyX[0] == 0 || bodyX[0] == side - 1 || bodyY[0] == 0 || bodyY[0] == side - 1;
}

void TailLogics(char& sAir)
{
	gameField[bodyY[Length] * side + bodyX[Length]] = sAir;
	//Input
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (stateWalk != 's')
			{
				dirX = 0;
				dirY = -1;
				stateWalk = 'w';
			}
			break;
		case 'a':
			if (stateWalk != 'd')
			{
				dirX = -1;
				dirY = 0;
				stateWalk = 'a';
			}
			break;
		case 's':
			if (stateWalk != 'w')
			{
				dirX = 0;
				dirY = 1;
				stateWalk = 's';
			}
			break;
		case 'd':
			if (stateWalk != 'a')
			{
				dirX = 1;
				dirY = 0;
				stateWalk = 'd';
			}
			break;
		}
		//Clear Key buffer
		while (_kbhit()) _getch();
	}

	int CurrentX;
	int CurrentY;
	int prevX = bodyX[0];
	int prevY = bodyY[0];
	bodyX[0] += dirX;
	bodyY[0] += dirY;
	for (int i = 1; i <= Length; i++)
	{
		CurrentX = bodyX[i];
		CurrentY = bodyY[i];
		bodyX[i] = prevX;
		bodyY[i] = prevY;
		prevX = CurrentX;
		prevY = CurrentY;
	}
}

bool PlayerWalk(char& sTail, char& sPlayer, char& sFood, char& sWall, char& sAir)
{
	if (bodyX[0] != foodX || bodyY[0] != foodY)
	{
		TailLogics(sAir);
	}
	else
	{
		gameField[foodY * side + foodX] = sAir;

		Length++;
		score += 1 * (dif + 1);
		bodyX[Length] = bodyX[0];
		bodyY[Length] = bodyY[0];
		
		TailLogics(sAir);

		RandFood();
	}
	return Collision();
}

void CreateMap(char& sWall, char& sAir)
{
	for (int y = 0; y < SIZE; )
	{
		for (int x = 0; x < side; x++)
		{
			if (y == 0 || y == SIZE - side || x == 0 || x == side - 1)
				gameField[y + x] = sWall;
			else
				gameField[y + x] = sAir;
		}
		y += side;
	}
}

void DrawMap(char& sTail, char& sPlayer, char& sFood, char& sWall, char& sAir)
{	
	for (int i = 1; i <= Length; i++)
	{
		gameField[bodyY[i] * side + bodyX[i]] = sTail;
	}

	gameField[foodY * side + foodX] = sFood;
	gameField[bodyY[0] * side + bodyX[0]] = sPlayer;
	if (sPlayer == 'S')
	{
		for (int i = 0; i <= Length; i += 2)
			gameField[bodyY[i] * side + bodyX[i]] = sPlayer;
		for (int i = 3; i <= Length; i += 4)
			gameField[bodyY[i] * side + bodyX[i]] = '\\';
	}
				
	for (int y = 0; y < SIZE; )
	{
		for (int x = 0; x < side; x++)
		{
			std::cout << gameField[y + x];
		}
		y += side;
		std::cout << std::endl;
	}

	std::cout << "Score: " << score << "\tLength: " << Length << std::endl;
	
	std::cout << "\tControl WASD\n";
}

void WaitEnter()
{
	bool wait = _getch();
}

void StartGame(char& sWall, char& sAir)
{
	stateWalk = 'w';

	Length = 0; 
	score = 0;
	
	dirX = 0;
	dirY = -1;
	
	RandFood();

	bodyX[0] = side / 2;
	bodyY[0] = side / 2;

	CreateMap(sWall, sAir);
}

void StartSettings(char& sTail, char& sPlayer, char& sFood, char& sWall, char& sAir)
{	
	sTail = 'o';
	sPlayer = '@';
	sFood = 'F';
	sWall = '#';
	sAir = ' ';

	std::cout << "Select difficulty.\n" << " 0. So slow, that i'm dead\n 1. Normal \n 2. Hard\n 3. Insane\n\n";
	std::cout << "Special dif:\n 4. Sus\n 5. Demon\n 6. Demon Sus";
	//Select difficulty
	while (true)
	{
		switch (_getch())
		{
		case 48:
			dif = 0;
			break;
		case 49:
			dif = 6;
			break;
		case 50:
			dif = 7;
			break;
		case 51:
			dif = 8;
			break;
		case 52:
			dif = 7;
			sPlayer = 'S';
			sTail = 'U';
			break;
		case 53:
			dif = 7;
			sWall = ' ';
			break;
		case 54:
			dif = 7;
			sWall = ' ';
			sPlayer = 'S';
			sTail = 'U';
			break;
		default:
			system("cls");
			std::cout << "Select difficulty.\n" << " 0. So slow, that i'm dead\n 1. Normal \n 2. Hard\n 3. Insane\n\n";
			std::cout << "Special dif:\n 4. Sus\n 5. Demon\n 6. Demon Sus";
			std::cout << "\n\tPlease, select correct difficulty.";
			continue;
		}
		break;
	}
}

int main(int argc, char* argv)
{
	char sWall = '#';
	char sAir = ' ';
	char sFood = 'F';
	char sTail = 'o';
	char sPlayer = '@';

	srand(unsigned(time(0)));

	//Texture

	std::cout << "\tSnuke\n" << "\n Welcome in my first game\nIs just a snake in console\n\t   Made by Reych636 \n\nPress anythink for continue.";
	WaitEnter();    
	system("cls");
	
	StartSettings(sTail, sPlayer, sFood, sWall, sAir);

	bool GameOn = true;
	while (true)
	{
		StartGame(sWall, sAir);

		//Main game loop
		while (GameOn)
		{
			system("cls");
			GameOn = !PlayerWalk(sTail, sPlayer, sFood, sWall, sAir);
			DrawMap(sTail, sPlayer, sFood, sWall, sAir);
			std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 - (dif * 135000000)));
		}

		//Select keep or del the old settings
		int randGameOverText = rand() % 2;
		if (randGameOverText) std::cout << "\nGet dunked on.";
		else std::cout << "\nGameOver.";
		std::cout << "\n\nShould keep the old settings?\n" << "Yes - 1\nNo - 0";
		while (true)
		{
			switch (_getch())
			{
			case '1':
				system("cls");
				StartGame(sWall, sAir);
				GameOn = true;
				break;
			case '0':
				system("cls");
				GameOn = true;
				StartSettings(sTail, sPlayer, sFood, sWall, sAir);
				break;
			default:
				system("cls");
				DrawMap(sTail, sPlayer, sFood, sWall, sAir);
				std::cout << "\nShould keep the old settings?\n" << "Yes - 1\nNo - 0";
				std::cout << "\n\nSelect the correct option";
				continue;
			}
			break;
		}		
	}
	return 0;
}