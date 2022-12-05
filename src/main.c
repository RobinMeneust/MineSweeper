/**
 * @file main.c
 * @author Robin MENEUST
 * @brief Play minesweeper
 * @version 0.1
 * @date 2022-12-05
 */
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
	Board board; // board where we play. It contains all the cells
	
	// The board is initialized
	board.cells = NULL;
	board.width = 0;
	board.height = 0;
	board.nbMines = 0;

	printf("Board width (>0): ");
	board.width = getInteger();
	printf("\nBoard height (>0): ");
	board.height = getInteger();

	if(board.width < 1 || board.height < 1){
		fprintf(stderr, "ERROR: width and height can't be lesser than 1\n");
		exit(EXIT_FAILURE);
	}

	printf("\nBoard nbMines (>0): ");
	board.nbMines = getInteger();
	
	if(board.nbMines < 1 || board.width*board.height < board.nbMines){
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

	for(int i=0; i<board.height; i++){
        free(board.cells[i]);
    }
	free(board.cells);

	return 0;
}