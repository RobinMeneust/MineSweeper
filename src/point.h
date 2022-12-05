/**
 * @file point.h
 * @author Robin MENEUST
 * @brief Contain a type used for the position of the cells in a board of minesweeper
 * @version 0.1
 * @date 2022-12-05
 */
#ifndef POINT_H
#define POINT_H

/**
 * @struct IntPoint
 * @brief Point with integer coordinates
 */

typedef struct IntPoint{
	int x; /*!< X coordinate (width)*/
	int y; /*!< Y coordinate (height)*/
}IntPoint;

#endif