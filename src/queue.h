/**
 * @file queue.h
 * @author Robin MENEUST
 * @brief Function prototypes and types needed by queue.c
 * @version 0.1
 * @date 2022-12-05
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include "point.h"

/**
 * @struct Node 
 * @brief Node of a linked list, containing IntPoint elements
 */

typedef struct Node{
	IntPoint element; /*!< Element of the node*/
	struct Node* next; /*!< Pointer to the next node in the list*/
}Node;

/**
 * @struct Queue
 * @brief Queue of nodes
 */

typedef struct Queue{
	Node* front; /*!< Pointer to the front node of the queue, where elements are dequeued*/
	Node* rear; /*!< Pointer to the rear node of the queue, where elements are enqueued*/
}Queue;

void initQueue(Queue *queue);
void freeQueue(Queue *queue);
Node* createNode();
void enqueue(Queue *queue, IntPoint x);
IntPoint dequeue(Queue *queue);
int isInQueue(Queue queue, IntPoint elmnt);

#endif