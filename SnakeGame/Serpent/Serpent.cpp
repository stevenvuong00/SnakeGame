// Serpent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <cstdlib> 
#include <ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;


bool gameOver;
// map 
const int width = 20;
const int height = 20;

// vars for snake position
int x, y, fruitX, fruitY, score;
// press A, snake go left, press W, go up

// mappings for the keys
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// need 2 arrays to hold the tail information,  X and Y coord, will work in pairs
int tailX[100], tailY[100];
int nTail; // tail length


void Setup() {
    gameOver = false;
    dir = STOP; // snake will not move until we make it move 
    // center the snake head
    x = width / 2;
    y = height / 2;
    // randomize the fruit position
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

//draw the board
void Draw() {
    system("cls"); // will make the screen flicker
    // drawing the top horizontal line
    for (int i = 0; i <= width+1; i++) 
        cout << "#";
    cout << endl;

    // drawing the vertical lines
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0) {
                cout << "#";
            }
            // check the snake position
            if (i == y && j == x) {
                cout << "0";
            }
            // check the fruit position
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            // nothing to print OR printing the tail
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }             
                }  
                if (!print)
                    cout << " ";
            }
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    // drawing the bottom horizontal line
    for (int i = 0; i <= width+1; i++)
        cout << "#";
    cout << endl;

    //Print the score
    cout << "Score: " << score << endl;
}

void Input() {
    // handling the keyboard inputs
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // remember the previous coord of the tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // set the first element
    tailX[0] = x;
    tailY[0] = y;

    // changing the tail 
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    // changing the direction of the snake
    switch (dir) {
    case LEFT:
        // decrease x coor
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        // the board is a 2d array, so the (0,0) coord is on the top left
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //terminate the game when reach the end of board
    //if (x > width || x < 0 || y > height || y < 0)
    //   gameOver = true;

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // eating a fruit --> will increase the tail length
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // increase tail length by 1
    }
}

int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(40); //slows our game 
    }
}
