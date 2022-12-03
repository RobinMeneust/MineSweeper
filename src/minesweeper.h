#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Cell
{
	int isMine;
	int isDiscovered;
	int isMarked;
	int nearMines;
	int doDisplayNearMines;
}Cell;

typedef struct IntPoint
{
	int x;
	int y;
}IntPoint;

typedef struct Board
{
	Cell **cells;
	int height;
	int width;
	int nbMines;
	IntPoint lastActivatedMineCoord;
}Board;

int getInteger();
void init(Board *board);
void displayBoard(Board board);
int play(Board* board, int moveType, IntPoint cell);
void start(Board *board);

#endif