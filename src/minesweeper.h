#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "point.h"

typedef struct Cell
{
	int isMine;
	int isDiscovered;
	int isMarked;
	int nearMines;
	int doDisplayNearMines;
}Cell;

typedef struct Board
{
	Cell **cells;
	int height;
	int width;
	int nbMines;
	int nbDiscoveredCells;
	int nbDiscoveredCellsAtEnd;
	int nbMarkedCells;
	IntPoint lastActivatedMineCoord;
}Board;

int getInteger();
IntPoint createIntPoint(int x, int y);
void init(Board *board);
void displayBoard(Board board);
void play(Board* board, int moveType, IntPoint cell);
void start(Board *board);

#endif