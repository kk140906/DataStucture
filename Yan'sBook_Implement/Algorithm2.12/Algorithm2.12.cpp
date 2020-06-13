#include "../include/LinkedList.hpp"
/*
* 线性表LA、LB按照非递减有序排列,实现LA、LB归并为LC仍然按照非递减有序排列
*   LA = (3,5,8,11);
*   LB = (2,6,8,8,11,15,20);
*   LC = (2,3,5,6,8,8,8,11,11,15,20);
* 时间复杂度:O(LA) + O(LB)
* 空间复杂度:O(LA) + O(LB)
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
 * 直接循环比较,保证元素个数少的先排完序，然后再把元素个数多剩余部分直接添加到新的列表后面
 * L1、L2从首结点开始比较，将L1的头结点与首结点断开，直接在L1的头结点后添加新的结点地址形成一个新的链表
 */
LinkedList unionSets(LinkedList* l1, LinkedList* l2)
{
    Node* pL1 = l1->pHead->pNext;
    Node* pL2 = l2->pHead->pNext;
    Node* pL3 = l1->pHead;
    while (pL1 && pL2)
    {
        if (memcmp(pL1->data, pL2->data, l1->dataBytes) <= 0)
        {
            pL3->pNext = pL1;
            pL3 = pL1;
            pL1 = pL1->pNext;
        }
        else
        {
            pL3->pNext = pL2;
            pL3 = pL2;
            pL2 = pL2->pNext;
        }
    }
    pL3->pNext = pL1 ? pL1 : pL2;
    l1->size += l2->size;
    return *l1; 
}

