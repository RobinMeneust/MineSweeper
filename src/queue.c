#include "queue.h"

void initQueue(Queue *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

void freeQueue(Queue *queue)
{
	Node* p = NULL;
	while(queue->front != NULL){
		p = queue->front;
		queue->front = queue->front->next;
		free(p);
	}
	queue->front = NULL;
	queue->rear = NULL;
}

Node *createNode()
{
	Node *node = (Node *)malloc(sizeof(Node));
	IntPoint point;

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

void enqueue(Queue *queue, IntPoint x)
{
	Node *node = createNode();

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

IntPoint dequeue(Queue *queue)
{
	Node* p = NULL;
	IntPoint element;
	if(queue->front!=NULL)
	{
		element.x = queue->front->element.x;
		element.y = queue->front->element.y;
		p = queue->front;
		queue->front = queue->front->next;
		free(p);
		if(queue->front == NULL){
			queue->rear = NULL;
		}
	}
	return element;
}

IntPoint peekFront(Queue queue)
{
	return queue.front->element;
}

void displayQueue(Queue queue)
{
	Node* p = queue.front;
	while(p != NULL){
		printf("(%d|%d) ", p->element.x, p->element.y);
		p = p->next;
	}
}

int isInQueue(Queue queue, IntPoint elmnt)
{
	Node* p = queue.front;

	while(p != NULL){
		if(p->element.x != elmnt.x && p->element.y != elmnt.y){
			return 1;
		}
		p = p->next;
	}
	return 0;
}