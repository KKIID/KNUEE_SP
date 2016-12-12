#include <stdio.h>
#include <stdlib.h>
#include "ADT_QUEUE.h"

QUEUE *createQueue() {
	QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));
	if(queue==NULL) {
		fprintf(stderr,"Cannot create queue");
		exit(1);
	}
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

NODE *createNode(void *dataIn) {
	NODE *node = (NODE*)malloc(sizeof(NODE));
	if(node==NULL) {
		fprintf(stderr,"Cannot create node");
		exit(1);
	}
	node->data = dataIn;
	node->next = NULL;
	return node;
}

void enqueue(QUEUE* queue, void *dataIn) {
	NODE *temp = createNode(dataIn);
	if(queue==NULL){
		fprintf(stderr,"Null pointer exception");
		exit(2);
	}
	if(queue->size == 0) {
		queue->head = temp;
		queue->tail = temp;
	} else {	
		queue->tail->next = temp;
		queue->tail = temp;
	}
	queue->size++;
}

void *dequeue(QUEUE* queue) {
	NODE *temp = queue->head;
	void *dataOut = queue->head->data;	
	if(queue==NULL){
		fprintf(stderr,"Null pointer exception");
		exit(2);
	}
	queue->head = queue->head->next;
	queue->size--;
	free(temp);
	return dataOut;
}

void *front(QUEUE* queue) {
	if(queue==NULL) {
		fprintf(stderr,"Null pointer exception");
		exit(2);
	}
	return queue->head->data;
}

