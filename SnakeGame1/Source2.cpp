//Name:Michael Racz
//Date:December 31,2019
//
//Project name:SnakeGame1
//
//This game plays snake. Found off of some youtube tutorial. 'W' 'A' 'S' 'D' makes the snake move, and the 'X' key will cancel the game. The snake head is a '0' and the fruit is an 'F'
//
//

#include <iostream>
using namespace std;
//for sleep(10) function in main
//#include <Windows.h>
//for input, has 2 functions we will use in Input()
#include <conio.h>
//width & height = Map Dimensions
//x,y,fruitX,fruitY = Head Position variables, positions of the fruit, total score
//eDirection is for the directions
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() {
	gameOver = false;
	dir = STOP;
	//Snake centered on the map
	x = width / 2;
	y = height / 2;
	// random from 0-> width-1; etc
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}

void Draw() {
	//call the system, --cls-- clears the screen
	system("cls");
    //display the top border of the map with this
	for (int i = 0; i < width + 2 ; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{ 
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if(!print)
				  cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	//print the bottom row of our border
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;

} 

void Input() {
	// "_kbhit" returns positive number if a character on the keyboard is pressed, nothing is pressed returns a 0
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		//stops the game.
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	//behind the scenes drawing the tail
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
	}
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	//if the cursor is on the fruit then add score and generate a new fruit
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}