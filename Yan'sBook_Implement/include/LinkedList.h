#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stdio.h>
#include <stdlib.h>
/*
    线性结构:链式结构
*/

typedef struct NODE
{
    int data;
    NODE* pNext;
}Node;

typedef struct
{
    Node* pHead;
    Node* pTail;
    int size;
}List;

void init(List* l, int* array, int size); //链表初始化:创建一个包含array内每一个元素的链表
void show(List* l);//显示链表所有元素
bool append(List* l, int var);//在链表最后追加一个新的元素
bool contain(List* l, int var);//判断链表内是否包含某个元素
// bool isEmpty(List* l);//判断链表是否为空
int getSize(List* l);//获取链表大小


#endif // !__LINKED_LIST__