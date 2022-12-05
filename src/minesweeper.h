/**
 * @file minesweeper.h
 * @author Robin MENEUST
 * @brief Functions prototypes and types used by minesweeper.c
 * @version 0.1
 * @date 2022-12-05
 */

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "point.h"

/**
 * @struct Cell
 * @brief Cell of a minesweeper game
 */

typedef struct Cell
{
	int isMine; /*!< Is a mine (boolean) */
	int isDiscovered; /*!< Is discovered (boolean) */
	int isMarked; /*!< Is marked (boolean) */
	int nearMines; /*!< Number of neighboring mines */
	int doDisplayNearMines; /*!< Do display number of neighboring mines in this cell (boolean) */
}Cell;

/**
 * @struct Board
 * @brief Board of a minesweeper game
 */

typedef struct Board
{
	Cell **cells; /*!< Matrix of cells*/
	int height; /*!< Height of the board*/
	int width; /*!< Width of the board*/
	int nbMines; /*!< Number of discovered mines*/
	int nbDiscoveredCells; /*!< Number of discovered cells*/
	int nbDiscoveredCellsAtEnd; /*!< Expected number of discovered cells at the end*/
	int nbMarkedCells; /*!< Number of marked cells*/
	IntPoint lastActivatedMineCoord; /*!< Coordinates of the last activated mine. It has negative coordinates if no mine has exploded*/
}Board;

int getInteger();
IntPoint createIntPoint(int x, int y);
void init(Board *board);
void displayBoard(Board board);
void play(Board* board, int moveType, IntPoint cell);
void start(Board *board);

#endif