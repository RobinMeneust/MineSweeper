#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

/**
 * @brief Main function
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Returns 0 if it ends correctly
 */

int main(int argc, char **argv)
{
	Board board;
	board.cells = NULL;
	board.width = 0;
	board.height = 0;
	board.nbMines = 0;

	printf("Board width: ");
	board.width = getInteger();
	printf("\nBoard height: ");
	board.height = getInteger();
	printf("\nBoard nbMines: ");
	board.nbMines = getInteger();
	
	if(board.width*board.height < board.nbMines){
		fprintf(stderr, "ERROR: the number of mines can't be greater than the number of cells in the board\n");
		exit(EXIT_FAILURE);
	}

	board.cells = (Cell**) malloc(sizeof(Cell*) * board.height);

	if(board.cells == NULL){
        fprintf(stderr, "ERROR : Memory could not be allocated with malloc in main\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<board.height; i++){
        board.cells[i] = (Cell*) malloc(sizeof(Cell) * board.width);
		if(board.cells[i] == NULL){
			fprintf(stderr, "ERROR : Memory could not be allocated with malloc in main\n");
			exit(EXIT_FAILURE);
		}
    }

	init(&board);
	start(&board);

	return 0;
}