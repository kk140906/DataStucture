#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stdio.h>
#include <stdlib.h>
/*
    ���Խṹ:��ʽ�ṹ
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

void init(List* l, int* array, int size); //�����ʼ��:����һ������array��ÿһ��Ԫ�ص�����
void show(List* l);//��ʾ��������Ԫ��
bool append(List* l, int var);//���������׷��һ���µ�Ԫ��
bool contain(List* l, int var);//�ж��������Ƿ����ĳ��Ԫ��
// bool isEmpty(List* l);//�ж������Ƿ�Ϊ��
int getSize(List* l);//��ȡ�����С


#endif // !__LINKED_LIST__