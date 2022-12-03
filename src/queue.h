#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include "point.h"

typedef struct Node{
	IntPoint element;
	struct Node* next;
}Node;

typedef struct Queue{
	Node* front;
	Node* rear;
}Queue;

void initQueue(Queue *queue);
void freeQueue(Queue *queue);
Node* createNode();
void enqueue(Queue *queue, IntPoint x);
IntPoint dequeue(Queue *queue);
IntPoint peekFront(Queue queue);
void displayQueue(Queue queue);
int isInQueue(Queue queue, IntPoint elmnt);

#endif