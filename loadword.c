#include "ADT_QUEUE.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

FILE *openFile();

int main(void) {
	QUEUE *queue = createQueue();
	FILE *fp = openFile();
	int i;
	char buf[100][20];

	for(i=0;i<100;i++) {
		fgets(buf[i],100,fp);
		enqueue(queue,buf[i]);
	}
	for(i=0;i<100;i++) {
		printf("%s",(char*)dequeue(queue));
	}
}

FILE *openFile() {
	FILE *fp = fopen("wordlist.txt","r");
	if(fp == -1){
		fprintf(stderr, "Cannot read file");
		exit(3);
	}
	return fp;
}

