/*
    例2.1:求A = A U B
    插入法:插入法的本质是循环遍历两个集合，判断其中一个集合中的每一个元素是否在另一个集合中，如果不在即插入，如果在就继续判断下一个元素
*/
#include "../include/LinkedList.hpp"
// 插入法实现并集
void unionSets(LinkedList* l1, LinkedList* l2);
void showListAllData(LinkedList* l, char* title);

int main()
{
    int sizeA = 4;
    int sizeB = 5;
    int A[] = { 2,3,4,5 };
    int B[] = { 1,3,6,2,7 };
    LinkedList LA, LB;
    LinkedList_Func->init(&LA, sizeof(A[0]));
    LinkedList_Func->init(&LB, sizeof(B[0]));
    for (int i = 0; i < sizeA; ++i)
    {
        LinkedList_Func->addLast(&LA, (LinkedListType)(A + i));
    }
    showListAllData(&LA, (char*)"A链表内容:");
    for (int i = 0; i < sizeB; ++i)
    {
        LinkedList_Func->addLast(&LB, (LinkedListType)(B + i));
    }
    showListAllData(&LB, (char*)"B链表内容:");

    unionSets(&LA, &LB);
    showListAllData(&LA, (char*)"A与B求并集后A链表内容为:");
    return 0;
}

void showListAllData(LinkedList* l, char* title)
{
    puts(title);
    Node* next = l->pHead->pNext;
    while (next)
    {
        printf("%d\t", *(int*)next->data);
        next = next->pNext;
    }
    puts("\n");
}


void unionSets(LinkedList* l1, LinkedList* l2)
{
    LinkedListType var;
    for (int i = 1; i <= l2->size; ++i)
    {
        if (!LinkedList_Func->getData(l2,i, &var))
            exit(-1);
        if (!LinkedList_Func->locateData(l1, var, NULL))
            LinkedList_Func->addLast(l1, var);
    }
    return;
}