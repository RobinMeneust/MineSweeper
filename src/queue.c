/**
 * @file queue.c
 * @author Robin MENEUST
 * @brief Implementing queues functions with queues containing IntPoint elements
 * @version 0.1
 * @date 2022-12-05
 */
#include "queue.h"


/**
 * @brief Initialize the queue
 * 
 * @param queue Queue initialized
 */

void initQueue(Queue *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

/**
 * @brief Free the queue
 * 
 * @param queue Queue freed
 */

void freeQueue(Queue *queue)
{
	Node* p = NULL; // Temporary pointer used to free the nodes
	while(queue->front != NULL){
		p = queue->front;
		queue->front = queue->front->next;
		free(p);
	}
	queue->front = NULL;
	queue->rear = NULL;
}

/**
 * @brief Create a node
 * 
 * @return Node created
 */

Node *createNode()
{
	Node *node = (Node *)malloc(sizeof(Node)); // New node
	IntPoint point; // Element that will be in the node

	if (node == NULL)
	{
		fprintf(stderr, "ERROR : Memory could not be allocated with malloc in createNode\n");
		exit(EXIT_FAILURE);
	}

	point.x = 0;
	point.y = 0;
	node->element = point;
	node->next = NULL;
	return node;
}

/**
 * @brief Enqueue x in the queue
 * 
 * @param queue Queue where a new node is inserted
 * @param x New element inserted
 */

void enqueue(Queue *queue, IntPoint x)
{
	Node *node = createNode(); // New node

	node->element = x;
	node->next = NULL;
	if (queue->rear == NULL)
	{
		// The queue is empty
		queue->front = node;
	}
	else
	{
		// The queue is not empty
		queue->rear->next = node;
	}
	queue->rear = node;
}

/**
 * @brief Dequeue an element from the queue
 * 
 * @param queue Queue from which an element is dequeued
 * @return Element at the front of the queue, that has been removed from the it
 */

IntPoint dequeue(Queue *queue)
{
	Node* p = NULL; // Temporary pointer used to free the node
	IntPoint element; // Element dequeued

	if(queue->front!=NULL)
	{
		element = queue->front->element;
		p = queue->front;
		queue->front = queue->front->next;
		free(p);
		if(queue->front == NULL){
			queue->rear = NULL;
		}
	}
	return element;
}

/**
 * @brief Check if an element is in the queue
 * 
 * @param queue Queue where we search for elmnt
 * @param elmnt Element searched
 * @return 1 if it's in the queue and 0 if it's not
 */

int isInQueue(Queue queue, IntPoint elmnt)
{
	Node* p = queue.front; // Pointer used to move in the queue to search elmnt

	while(p != NULL){
		if(p->element.x == elmnt.x && p->element.y == elmnt.y){
			return 1;
		}
		p = p->next;
	}
	return 0;
}