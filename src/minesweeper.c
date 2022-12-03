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

void init(Board *board)
{
	int nbAddedMines = 0;
	int iter = 0;
	int i = 0;
	int j = 0;

	// If the last activated mine coordinates are negative it means it's not initialized, no mine has exploded.
	board->lastActivatedMineCoord.x = -1;
	board->lastActivatedMineCoord.y = -1;

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
			if (board.cells[i][j].isDiscovered)
			{
				if (board.cells[i][j].isMine)
				{
					// if this coordinate is negative it means it wasn't initialized, thus no mine has exploded
					if (board.lastActivatedMineCoord.x >= 0)
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
				if (board.cells[i][j].isMarked)
				{
					printf(" F ");
				}
				else if (board.cells[i][j].doDisplayNearMines)
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
}

int play(Board** board, int moveType, IntPoint cell)
{
	if(moveType == 0){
		// The cell is being discovered

	}
	else{
		// The cell is being marked
		
	}
}

void start(Board *board)
{
	int status = 0;
	int moveType = 0;
	IntPoint cell;

	cell.x = 0;
	cell.y = 0;

	while (status == 0)
	{
		printf("\nChoose a number between 0 and 1:\n0: Discover the cell\n1: Mark the cell\nAnswer: ");
		moveType = getInteger();
		if (moveType != 0 && moveType != 1)
		{
			fprintf(stderr, "ERROR: You must enter 0 or 1\n");
			exit(EXIT_FAILURE);
		}
		printf("\nYour move:\nChoose a number between 0 and %d for the x coordinate: ", board->width - 1);
		cell.x = getInteger();

		printf("\nChoose a number between 0 and %d for the y coordinate: ", board->height - 1);
		cell.y = getInteger();

		if (cell.x<0 || cell.y<0 || cell.x>=board->width || cell.y>=board->height)
		{
			fprintf(stderr, "ERROR: You must enter coordinates that are in the board: positive integers lesser than the board size\n");
			exit(EXIT_FAILURE);
		}

		status = play(&board, moveType, cell);
		refresh(&board);
	}
}