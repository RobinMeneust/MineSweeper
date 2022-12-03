#include "minesweeper.h"

/**
 * @brief Get an integer from the user and check if it was correctly got
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

IntPoint createIntPoint(int x, int y)
{
	IntPoint point;

	point.x = x;
	point.y = y;
	return point;
}

void init(Board *board)
{
	int nbAddedMines = 0;
	int iter = 0;
	int i = 0;
	int j = 0;

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
				if (j >= board->width)
				{
					j = 0;
					i++;
				}
			}
			if (i < board->height && j < board->width && board->cells[i][j].isMine == 0)
			{
				board->cells[i][j].isMine = 1;
			}
			else
			{
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
			else if (j < board->width - 1)
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
			if (board.cells[i][j].isMarked)
			{
				printf(" F ");
			}
			else if (board.cells[i][j].isDiscovered || board.lastActivatedMineCoord.x >= 0)
			{
				// Is discovered or we lost (a mine has exploded)
				if (board.cells[i][j].isMine)
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
				else
				{
					printf(" . ");
				}
			}
			else
			{
				if (board.cells[i][j].doDisplayNearMines)
				{
					printf(" %d ", board.cells[i][j].nearMines);
				}
				else
				{
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

void enqueueNeighbors(Board board, IntPoint cell, Queue* cellsToCheck)
{
	if(cell.x > 0){
		if(!board.cells[cell.x - 1][cell.y].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y))){
			enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y));
		}
		if(cell.y > 0){
			if(!board.cells[cell.x - 1][cell.y - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y - 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y - 1));
			}
		}
		if(cell.y < board.height){
			if(!board.cells[cell.x - 1][cell.y + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x - 1, cell.y + 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x - 1, cell.y + 1));
			}
		}
	}
	if(cell.x < board.width){
		if(!board.cells[cell.x + 1][cell.y].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y))){
			enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y));
		}
		if(cell.y > 0){
			if(!board.cells[cell.x + 1][cell.y - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y - 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y - 1));
			}
		}
		if(cell.y < board.height){
			if(!board.cells[cell.x + 1][cell.y + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x + 1, cell.y + 1))){
				enqueue(cellsToCheck, createIntPoint(cell.x + 1, cell.y + 1));
			}
		}
	}
	if(cell.y > 0 && !board.cells[cell.x][cell.y - 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x, cell.y - 1))){
		enqueue(cellsToCheck, createIntPoint(cell.x, cell.y - 1));
	}
	if(cell.y < board.height && !board.cells[cell.x][cell.y + 1].isDiscovered && !isInQueue(*cellsToCheck, createIntPoint(cell.x, cell.y - 1))){
		enqueue(cellsToCheck, createIntPoint(cell.x, cell.y + 1));
	}
}

void play(Board* board, int moveType, IntPoint cell)
{
	Queue cellsToCheck;

	initQueue(&cellsToCheck);

	if(moveType == 0){
		// The cell is being discovered
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

				printf("board->cells[%d][%d].nearMines = %d\n", cell.x, cell.y, board->cells[cell.y][cell.x].nearMines );
				if(board->cells[cell.y][cell.x].nearMines > 0){
					board->cells[cell.y][cell.x].doDisplayNearMines = 1;
				}
				else{
					enqueueNeighbors(*board, cell, &cellsToCheck);
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

void start(Board *board)
{
	int moveType = 0;
	IntPoint cell;

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
			printf("\nYour move:\nChoose a number between 0 and %d for the x coordinate: ", board->width - 1);
			cell.x = getInteger();

			printf("\nChoose a number between 0 and %d for the y coordinate: ", board->height - 1);
			cell.y = getInteger();
		}while(cell.x<0 || cell.y<0 || cell.x>=board->width || cell.y>=board->height);

		play(board, moveType, cell);
		displayBoard(*board);
	}
}