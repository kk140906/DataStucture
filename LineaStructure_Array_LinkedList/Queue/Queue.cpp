#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int* pBase;
	int front;
	int rear;
	int length;
} Queue;

// 函数声明
void init(Queue* pQueue, int length);//队列初始化
void enqueue(Queue* pQueue, int var);
void show(Queue* pQueue);

int main(void)
{
	Queue q;
	init(&q,4);
	enqueue(&q,1);
	enqueue(&q,2);
	show(&q);
	
	return 0;
}

void init(Queue* pQueue, int length)
{
	pQueue->pBase = (int*)malloc(sizeof(int) * (length + 1));
	if (!pQueue)
	{
		puts("内存分配失败!");
		exit(-1);
	}
	pQueue->length = length + 1; 
	pQueue->front = 0;
	pQueue->rear = 0;
}

void enqueue(Queue* pQueue, int var)
{
	pQueue->pBase[pQueue->rear] = var;
	pQueue->rear = (pQueue->rear + 1) % pQueue->length; 
}

void show(Queue* pQueue)
{
	while(pQueue->front != pQueue->rear)	
	{
		printf("%d\t",pQueue->pBase[pQueue->front]);
		pQueue->front++;
	}
}