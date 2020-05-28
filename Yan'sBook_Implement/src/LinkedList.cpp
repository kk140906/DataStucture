
#include "..\include\LinkedList.h"

/*
    �����ʼ��:����һ������array��ÿһ��Ԫ�ص�����
*/
void init(List* l, int* array, int size)
{
    l->pHead = (Node*)malloc(sizeof(Node));
    if (!l->pHead)
    {
        printf("�ڴ����ʧ��,ͷ��㴴��ʧ��!\n");
        exit(-1);
    }
    l->pHead->pNext = NULL;
    l->pTail = l->pHead;
    for (int i = 0; i < size; ++i)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        if (!node)
        {
            puts("�ڴ����ʧ��,��㴴��ʧ��!");
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
    ��ʾ��������Ԫ��
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
    ���������׷��һ���µ�Ԫ��
*/
bool append(List* l, int var)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
    {
        puts("�ڴ����ʧ��,��㴴��ʧ��!");
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
    �ж��������Ƿ����ĳ��Ԫ��
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
    ��ȡ�����С
*/
int getSize(List* l)
{
    return l->size;
}