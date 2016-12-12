#ifndef __QUEUE__
#define __QUEUE__

typedef struct _node {
	void *data;
	struct _node *next;
}NODE;

typedef struct _queue {
	int size;
	NODE* head;
	NODE* tail; 
}QUEUE;

QUEUE *createQueue();
void enqueue(QUEUE*, void*);
void *dequeue(QUEUE*);
void *front(QUEUE*);

#endif
