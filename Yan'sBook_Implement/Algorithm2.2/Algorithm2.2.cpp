#include "../include/LinkedList.hpp"
/*
    线性表LA、LB按照非递减有序排列,实现LA、LB归并为LC仍然按照非递减有序排列
    LA = (3,5,8,11);
    LB = (2,6,8,8,11,15,20);
    LC = (2,3,5,6,8,8,8,11,11,15,20); 
*/

LinkedList unionSets(LinkedList* l1, LinkedList* l2);
void showListAllData(LinkedList* l, char* title);

int main()
{
    int sizeA = 4;
    int sizeB = 7;
    int A[] = { 3,5,8,11 };
    int B[] = { 2,6,8,8,11,15,20 };
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

    LinkedList LC = unionSets(&LA, &LB);
    showListAllData(&LC, (char*)"A链表与B链表求并集后C链表内容为:");
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

/**
 * L1,l2都是已经排序完毕的非递减序列
 * 直接循环比较,保证元素个数少的先排完序，然后再把元素个数多剩余部门直接添加到新的列表后面
 */
LinkedList unionSets(LinkedList* l1, LinkedList* l2)
{
    LinkedList list;
    LinkedList_Func->init(&list, sizeof(l1->dataBytes));
    int size = 0;
    int l1_pos = 1, l2_pos = 1;
    LinkedListType l1_data, l2_data;
    while (l1_pos <= l1->size && l2_pos <= l2->size)
    {
        if (!LinkedList_Func->getData(l1, l1_pos, &l1_data))
            exit(-1);
        if (!LinkedList_Func->getData(l2, l2_pos, &l2_data))
            exit(-1);
        if (memcmp(l1_data, l2_data, l1->dataBytes) <= 0)
        {
            LinkedList_Func->addLast(&list, l1_data);
            ++l1_pos;
        }
        else
        {
            LinkedList_Func->addLast(&list, l2_data);
            ++l2_pos;
        }
    }

    while (l1_pos <= l1->size)
    {
        if (!LinkedList_Func->getData(l1, l1_pos, &l1_data))
            exit(-1);
        LinkedList_Func->addLast(&list, l1_data);
        ++l1_pos;
    }

    while (l2_pos <= l2->size)
    {
        if (!LinkedList_Func->getData(l2, l2_pos, &l2_data))
            exit(-1);
        LinkedList_Func->addLast(&list, l2_data);
        ++l2_pos;
    }

    return list;
}

