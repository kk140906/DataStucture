
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* base;
    int* front;
    int* rear;
    int size;
} Queue;


void init(Queue* q, int size);//队列初始化,创建一个size大小的空队列
void show(Queue* q);//显示队列所有内容
bool enQueue(Queue* q, int var);//入队
bool deQueue(Queue* q, int* pVar = NULL);//出队
bool isEmpty(Queue* q);//判断队列是否为空
bool isFull(Queue* q);//判断队列是否已满
bool clear(Queue* q);//清空队列
void destory(Queue* q);//销毁队列
bool isDestoryed(Queue* q);//判断队列是否已经被销毁



int main(void)
{
    Queue q;
    init(&q, 5);
    for (int i = 0; i < 7; ++i)
    {
        if (enQueue(&q, i))
        {
            printf("入队成功!,入队数值:%d\n", i);
        }
    }
    show(&q);

    int var;
    deQueue(&q, &var);
    printf("出队成功!,出队数值:%d\n", var);
    deQueue(&q, &var);
    printf("出队成功!,出队数值:%d\n", var);
    deQueue(&q, &var);
    printf("出队成功!,出队数值:%d\n", var);

    enQueue(&q, 12);
    enQueue(&q, 20);
    enQueue(&q, 55);
    enQueue(&q, 620);

    show(&q);
    clear(&q);
    destory(&q);
    show(&q);
    for (int i = 0; i < 7; ++i)
    {
        if (deQueue(&q, &var))
        {
            printf("出队成功!,出队数值:%d\n", var);
            show(&q);
        }
    }
    return 0;
}

void init(Queue* q, int size)
{
    q->base = (int*)malloc(sizeof(int) * (size + 1));
    if (!q->base)
    {
        puts("内存分配失败!");
        exit(-1);
    }
    q->front = q->rear = q->base;
    q->size = size;
}

void show(Queue* q)
{
    if (isDestoryed(q))
    {
        puts("队列已被销毁!");
        return;
    }
    //遍历显示,头指针不停向尾指针移动，直至头指针与尾指针重合
    int* temp = q->front;
    while (temp != q->rear)
    {
        printf("%d\t", *temp);
        ++temp;
        //超过内存单元大小时，重置为内存基地址
        if (temp > q->base + q->size)
            temp = q->base;
    }
    puts("\n");
}

bool enQueue(Queue* q, int var)
{
    if (isDestoryed(q))
    {
        puts("队列已被销毁!");
        return false;
    }
    if (isFull(q))
    {
        printf("队列已满!,数值:%d入队失败!\n", var);
        return false;
    }
    //只要认为队列没有满，一定是先进行入队，然后尾指针指向后一个位置
    *q->rear = var;
    ++q->rear;
    //判断一下最新的尾指针位置，当超过分配的内存单元大小时，重置为内存基地址
    if (q->rear > q->base + q->size)
        q->rear = q->base;
    return true;
}

bool deQueue(Queue* q, int* pVar)
{
    if (isDestoryed(q))
    {
        puts("队列已被销毁!");
        return false;
    }

    if (isEmpty(q))
    {
        printf("队列已空!,出队失败!\n");
        return false;
    }
    //只要认为队列没有空，一定是先进行出队，然后头指针指向后一个位置
    *pVar = *q->front;
    ++q->front;
    //判断一下最新的头指针位置，当超过分配的内存单元大小时，重置为内存基地址
    if (q->front > q->base + q->size)
        q->front = q->base;
    return true;
}

bool isEmpty(Queue* q)
{
    //每一次出队操作都是元素出队，然后头指针向下一个位置移动
    //一旦头指针与尾指针重合时就是队列为空
    if (q->front == q->rear)
        return true;
    return false;
}

bool isFull(Queue* q)
{
    //每一次入队操作都是元素入队，然后尾指针向下一个位置移动
    int* rear = q->rear;
    /*
        手动让新的尾指针指向下一个位置,以便空出一个内存，
        空出一个内存的目的是为了区分队列是空还是满。如果没有这个空的内存，
        当队列最后一个元素入队后,尾指针已经指向了下一个位置,此时尾指针与头指针重合，
        此时就无法判断出队列是空还是满了！
    */
    ++rear;
    //如果新的尾指针超过分配的内存单元大小，重置为内存基地址
    if (rear > q->base + q->size)
        rear = q->base;
    //新的尾指针与头指针重合时就是队列为满
    if (q->front == rear)
        return true;
    return false;
}


bool clear(Queue* q)
{
    if (isDestoryed(q))
    {
        puts("队列已被销毁!");
        return false;
    }
    if (isEmpty(q))
    {
        puts("队列已空!");
        return false;
    }
    q->rear = q->front;
    return true;
}

void destory(Queue* q)
{

    free(q->base);
    q->base = NULL;
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    puts("队列销毁成功!");
}

bool isDestoryed(Queue* q)
{
    if (!q->base && !q->front && !q->rear && !q->size)
        return true;
    return false;
}