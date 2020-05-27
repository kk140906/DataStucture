
#include <stdio.h>
#include <stdlib.h>
/*
	创建数组形式的循环队列
*/
typedef struct
{
	int* pBase;
	int front;
	int rear;
	int length;
} Queue;

// 函数声明
void init(Queue* pQueue, int length);//队列初始化
void show(Queue* pQueue); //显示队列内容
bool isFull(Queue* pQueue); //判断队列是否已满
bool isEmpty(Queue* pQueue);//判断队列是否已空
bool enqueue(Queue* pQueue, int var);//入队
bool dequeue(Queue* pQueue, int* pVar);//出队


int main(void)
{
	Queue q;
	init(&q, 4);
	for (int i = 0; i < 6; ++i)
	{
		if (enqueue(&q, i))
			printf("数值:'%d',入队成功!\n", i);
	}
	puts("\n队列内容为:");
	show(&q);
	int var;
	for (int i = 0; i < 6; ++i)
	{
		if (dequeue(&q, &var))
			printf("出队成功!出队数值是:'%d'\n", i);
	}
	puts("\n队列内容为:");
	show(&q);
	return 0;
}

void init(Queue* pQueue, int length)
{
	pQueue->length = length + 1;
	pQueue->pBase = (int*)malloc(sizeof(int) * pQueue->length);
	if (!pQueue)
	{
		puts("内存分配失败!");
		exit(-1);
	}

	pQueue->front = 0;
	pQueue->rear = 0;
}

void show(Queue* pQueue)
{
	int front = pQueue->front;
	while (front != pQueue->rear)
	{
		printf("%d\t", pQueue->pBase[front]);
		front = (front + 1) % pQueue->length;
	}
	puts("\n");
}
bool isEmpty(Queue* pQueue)
{
	if (pQueue->front == pQueue->rear)
		return true;
	return false;
}
bool isFull(Queue* pQueue)
{
	if ((pQueue->rear + 1) % pQueue->length == pQueue->front)
		return true;
	return false;
}

bool enqueue(Queue* pQueue, int var)
{
	if (isFull(pQueue))
	{
		printf("队列已满,数值:'%d',入队失败!\n", var);
		return false;
	}
	pQueue->pBase[pQueue->rear] = var;
	pQueue->rear = (pQueue->rear + 1) % pQueue->length;
	return true;
}
bool dequeue(Queue* pQueue, int* pVar)
{
	if (isEmpty(pQueue))
	{
		puts("队列已空,出队失败!");
		return false;
	}
	*pVar = pQueue->pBase[pQueue->front];
	pQueue->front = (pQueue->front + 1) % pQueue->length;
	return true;
}