/**
 * @file minesweeper.c
 * @author Robin MENEUST
 * @brief Functions used to play a minesweeper game
 * @version 0.1
 * @date 2022-12-05 
 */

#include "minesweeper.h"

/**
 * @brief Get an integer from stdin and check if it was correctly got
 * @return Integer given by user
 */

int getInteger()
{
	int n = 0;		   // integer given by user
	int cFlush = 0;	   // integer used to flush stdin
	int testScanf = 0; // value returned by scanf. Used to test if the integer was correctly read

	testScanf = scanf("%d", &n);
	while ((cFlush = getchar()) != '\n' && cFlush != EOF); // we flush stdin
	if (testScanf != 0)
		return n;
	else
	{
		fprintf(stderr, "ERROR: this number is not valid\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Create a IntPoint structure from the x and y coordinates
 * 
 * @param x X coordinate of the new point
 * @param y Y coordinate of the new point
 * @return New point
 */

IntPoint createIntPoint(int x, int y)
{
	IntPoint point; // New point

	point.x = x;
	point.y = y;
	return point;
}

/**
 * @brief Initialize the board
 * 
 * @param board Board being initialized
 */

void init(Board *board)
{
	int nbAddedMines = 0; // Number of mines added to the board during initialization
	int iter = 0; // Number of iterations to find a free space to add a mine. It's used to avoid an infinite loop
	int i = 0; // Current row in the board
	int j = 0; // Current column in the board

	// If the last activated mine coordinates are negative it means it's not initialized, no mine has exploded.
	board->lastActivatedMineCoord.x = -1;
	board->lastActivatedMineCoord.y = -1;
	
	board->nbDiscoveredCells = 0;
	board->nbDiscoveredCellsAtEnd = board->height * board->width - board->nbMines;
	board->nbMarkedCells = 0;


	srand(time(NULL));

	for (i = 0; i < board->height; i++)
	{
		for (j = 0; j < board->width; j++)
		{
			board->cells[i][j].isDiscovered = 0;
			board->cells[i][j].isMarked = 0;
			board->cells[i][j].isMine = 0;
			board->cells[i][j].nearMines = 0;
			board->cells[i][j].doDisplayNearMines = 0;
		}
	}

	while (nbAddedMines < board->nbMines)
	{
		iter = 0;
		while (iter < 50)
		{
			i = rand() % board->height;
			j = rand() % board->width;

			// If it's not already a mine then we add one
			if (!board->cells[i][j].isMine)
			{
				board->cells[i][j].isMine = 1;
				// We found a free space to add a mine so we go to the next step, e.g we add the next mine if nbAddedMines is lesser than the expected number of mines
				break;
			}
			iter++;
		}

		// No free space was found randomly so we have to choose it manually
		if (iter >= 50)
		{
			i = 0;
			j = 0;

			while (i < board->height && j < board->width && board->cells[i][j].isMine)
			{
				j++;
				if (j >= board->width){
					j = 0;
					i++;
				}
			}
			if (i < board->height && j < board->width && board->cells[i][j].isMine == 0)
			{
				board->cells[i][j].isMine = 1;
			}
			else{
				fprintf(stderr, "ERROR: a mine could not be added in init\n");
				exit(EXIT_FAILURE);
			}
		}
		printf("MINE : %d %d \n", i, j);
		nbAddedMines++;
	}

	for (int i = 0; i < board->height; i++)
	{
		for (int j = 0; j < board->width; j++)
		{
			if (j > 0)
			{
				// Left
				board->cells[i][j].nearMines += board->cells[i][j - 1].isMine;

				// Top left
				if (i > 0)
				{
					board->cells[i][j].nearMines += board->cells[i - 1][j - 1].isMine;
				}

				// Bot left
				if (i < board->height - 1)
				{
					board->cells[i][j].nearMines += board->cells[i + 1][j - 1].isMine;
				}
			}
			if (j < board->width - 1)
			{
				// Right
				board->cells[i][j].nearMines += board->cells[i][j + 1].isMine;

				// Top right
				if (i > 0)
				{
					board->cells[i][j].nearMines += board->cells[i - 1][j + 1].isMine;
				}

				// Bot right
				if (i < board->height - 1)
				{
					board->cells[i][j].nearMines += board->cells[i + 1][j + 1].isMine;
				}
			}

			// Top
			if (i > 0)
			{
				board->cells[i][j].nearMines += board->cells[i - 1][j].isMine;
			}

			// Bot
			if (i < board->height - 1)
			{
				board->cells[i][j].nearMines += board->cells[i + 1][j].isMine;
			}
		}
	}
}

/**
 * @brief Display the board with different symbols according to its content
 * @ if the bomb has exploded
 * F if there is a flag (it's marked)
 * . if it's discovered and empty
 * M if there is a mine that did not explode
 * a blank space if it's neither marked nor discovered
 * 
 * @param board Displayed board
 */

void displayBoard(Board board)
{
	printf("   ");
	for (int i = 0; i < board.width; i++)
	{
		printf("  %d ", i);
	}
	printf("\n");

	for (int i = 0; i < board.height; i++)
	{
		printf("   ");
		for (int k = 0; k < board.width; k++)
		{
			printf("+---");
		}
		printf("+\n");
		printf(" %d ", i);
		for (int j = 0; j < board.width; j++)
		{
			printf("|");

			if(board.lastActivatedMineCoord.x >= 0){
				if(board.cells[i][j].isMine)
				{
					if (i == board.lastActivatedMineCoord.y && j == board.lastActivatedMineCoord.x)
					{
						printf(" @ ");
					}
					else
					{
						printf(" M ");
					}
				}
				else if(board.cells[i][j].doDisplayNearMines){
					printf(" %d ", board.cells[i][j].nearMines);
				}
				else{
					printf(" . ");
				}
			}
			else{
				if(board.cells[i][j].isMarked)
				{
					printf(" F ");
				}
				else if(board.cells[i][j].doDisplayNearMines){
					printf(" %d ", board.cells[i][j].nearMines);
				}
				else if(board.cells[i][j].isDiscovered){
					printf(" . ");
				}
				else if(board.nbDiscoveredCells == board.nbDiscoveredCellsAtEnd && board.cells[i][j].isMine){
					printf(" M ");
				}
				else{
					printf("   ");
				}
			}
		}
		printf("|");
		printf("\n");
	}
	printf("   ");
	for (int k = 0; k < board.width; k++)
	{
		printf("+---");
	}
	printf("+\n");
	if(board.lastActivatedMineCoord.x >=0 ){
		printf("BOOUUUUUMMMMMM !!!!!\n");
	}
	else if(board.nbDiscoveredCells == board.nbDiscoveredCellsAtEnd){
		printf("Felicitation !!\n");
	}
	else{
		printf("Mines : %d/%d\n", board.nbMarkedCells, board.nbMines);
	}
}

/**
 * @brief Enqueue all neighbors in the given queue
 * 
 * @param board Board checked
 * @param cell Cell whose neighbors are checked
 * @param cellsToCheck Queue where neighbors are enqueued. They will be checked in another function later on
 */

void enqueueNeighbors(Board board, IntPoint cell, Queue* cellsToCheck)
{
	if(cell.y > 0){
		if(!board.cells[cell.y - 1][cell.x].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x, cell.y - 1))){
			enqueue(cellsToCheck, createIntPoint(cell.x, cell.y - 1));
		}
		if(cell.x > 0){
			if(!board.cells[cell.y - 1][cell.x - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y - 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y - 1));
			}
		}
		if(cell.x < board.width - 1){
			if(!board.cells[cell.y - 1][cell.x + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y - 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y - 1));
			}
		}
	}
	if(cell.y < board.height - 1){
		if(!board.cells[cell.y + 1][cell.x].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x, cell.y + 1))){
			enqueue(cellsToCheck, createIntPoint(cell.x, cell.y + 1));
		}
		if(cell.x > 0){
			if(!board.cells[cell.y + 1][cell.x - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y + 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y + 1));
			}
		}
		if(cell.x < board.width - 1){
			if(!board.cells[cell.y + 1][cell.x + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y + 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y + 1));
			}
		}
	}
	if(cell.x > 0 && !board.cells[cell.y][cell.x - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y))){
		enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y));
	}
	if(cell.x < board.width - 1 && !board.cells[cell.y][cell.x + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y))){
		enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y));
	}
}

/**
 * @brief Make a move on the board
 * 
 * @param board Board that will be updated
 * @param moveType 0 if we discover a cell and 1 if we mark/unmark it
 * @param cell Cell modified
 */

void play(Board* board, int moveType, IntPoint cell)
{
	Queue cellsToCheck; // Queue of cells to check (recursively)

	initQueue(&cellsToCheck);

	if(moveType == 0){
		// The cell is being discovered
		if(!board->cells[cell.y][cell.x].isDiscovered){
			if(board->cells[cell.y][cell.x].isMine){
				board->lastActivatedMineCoord.x = cell.x;
				board->lastActivatedMineCoord.y = cell.y;
			}
			else{
				enqueue(&cellsToCheck, cell);

				while(cellsToCheck.front != NULL){
					cell = dequeue(&cellsToCheck);
					board->cells[cell.y][cell.x].isDiscovered = 1;
					board->nbDiscoveredCells++;

					if(board->cells[cell.y][cell.x].nearMines > 0){
						board->cells[cell.y][cell.x].doDisplayNearMines = 1;
					}
					else{
						enqueueNeighbors(*board, cell, &cellsToCheck);
					}
				}			
			}
		}
	}
	else{
		// The cell is being marked/unmarked
		if(board->cells[cell.y][cell.x].isMarked){
			board->cells[cell.y][cell.x].isMarked = 0;
			board->nbMarkedCells--;
		}
		else{
			board->cells[cell.y][cell.x].isMarked = 1;
			board->nbMarkedCells++;
		}
	}

	freeQueue(&cellsToCheck);
}

/**
 * @brief Launch a game of minesweeper on the given board
 * 
 * @param board Board where we play minesweeper
 */

void start(Board *board)
{
	int moveType = 0; // 0 if we discover a cell and 1 if we mark/unmark it
	IntPoint cell; // Cell modified

	cell.x = 0;
	cell.y = 0;

	displayBoard(*board);

	while(board->lastActivatedMineCoord.x < 0 && board->nbDiscoveredCells < board->nbDiscoveredCellsAtEnd)
	{
		do{
			printf("\nChoose a number between 0 and 1:\n0: Discover the cell\n1: Mark/unmark the cell\nAnswer: ");
			moveType = getInteger();
		}while(moveType != 0 && moveType != 1);
		
		do{
			printf("\nYour move:\nChoose a number between 0 and %d for the x (width) coordinate: ", board->width - 1);
			cell.x = getInteger();

			printf("\nChoose a number between 0 and %d for the y (height) coordinate: ", board->height - 1);
			cell.y = getInteger();
		}while(cell.x<0 || cell.y<0 || cell.x>=board->width || cell.y>=board->height);

		play(board, moveType, cell);
		displayBoard(*board);
	}
}