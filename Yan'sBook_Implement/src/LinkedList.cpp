
#include "..\include\LinkedList.h"

/*
    链表初始化:创建一个包含array内每一个元素的链表
*/
void init(List* l, int* array, int size)
{
    l->pHead = (Node*)malloc(sizeof(Node));
    if (!l->pHead)
    {
        printf("内存分配失败,头结点创建失败!\n");
        exit(-1);
    }
    l->pHead->pNext = NULL;
    l->pTail = l->pHead;
    for (int i = 0; i < size; ++i)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        if (!node)
        {
            puts("内存分配失败,结点创建失败!");
            exit(-1);
        }
        node->data = array[i];
        node->pNext = NULL;
        l->pTail->pNext = node;
        l->pTail = node;
    }
    l->size = size;
}

/*
    显示链表所有元素
*/
void show(List* l)
{
    Node* next = l->pHead->pNext;
    while (next)
    {
        printf("%d\t", next->data);
        next = next->pNext;
    }
    puts("\n");
}
/*
    在链表最后追加一个新的元素
*/
bool append(List* l, int var)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
    {
        puts("内存分配失败,结点创建失败!");
        return false;
    }
    node->data = var;
    node->pNext = NULL;
    l->pTail->pNext = node;
    l->pTail = node;
    ++l->size;
    return true;
}
/*
    判断链表内是否包含某个元素
*/
bool contain(List* l, int var)
{
    Node* next = l->pHead->pNext;
    while (next)
    {
        if (var == next->data)
            return true;
        next = next->pNext;
    }
    return false;
}
/*
    获取链表大小
*/
int getSize(List* l)
{
    return l->size;
}