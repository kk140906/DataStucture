#include "../include/LinkedList.h"
/*
    线性表LA、LB按照非递减有序排列,实现LA、LB归并为LC仍然按照非递减有序排列
    LA = (3,5,8,11);
    LB = (2,6,8,8,11,15,20);
    LC = (2,3,5,6,8,8,8,11,11,15,20); 
*/

List unionSets(List* l1, List* l2);
int main()
{
    int A[] = {3,5,8,11};
    int B[] = {2,6,8,8,11,15,20};
    List LA, LB,LC;
    init(&LA, A, 4);
    init(&LB, B, 7);
    puts("A链表内容为:");
    show(&LA);
    puts("B链表内容为:");
    show(&LB);

    LC = unionSets(&LA, &LB);
    puts("A链表与B链表求并集后C链表内容为:");
    show(&LC);
    return 0;
}

List unionSets(List* l1, List* l2)
{
    List list;
    init(&list,NULL, 0);
    int size = 0;
    Node* headList1;
    Node* headList2;
    if (l1->size > l2->size)
    {
        headList1 = l1->pHead->pNext;
        headList2 = l2->pHead->pNext;
    }
    else
    {
        headList1 = l2->pHead->pNext;
        headList2 = l1->pHead->pNext;
    }
    //外层循环一定要是长度较长的
    //如果外层较短，当外层结束后，内层剩余的结点就无法添加到新的链表上
    while (headList1)
    {
        while (headList2)
        {
            if (headList1->data >= headList2->data)
            {
                append(&list, headList2->data);
                headList2 = headList2->pNext;
                ++size;
            }
            else
                break;
        }
        append(&list, headList1->data);
        headList1 = headList1->pNext;
        ++size;
    }
    list.size = size;
    return list;
}

//指针方式重新创建新的链表
//List* unionSets(List* l1, List* l2);
//List* unionSets(List* l1, List* l2)
//{
//    List* l = (List*)malloc(sizeof(List));
//    if (!l)
//    {
//        puts("内存分配失败!");
//        exit(-1);
//    }
//
//    Node* head = (Node*)malloc(sizeof(Node));
//    if (!head)
//    {
//        puts("内存分配失败!");
//        exit(-1);
//    }
//    Node* tail = head;
//    tail->pNext = NULL;
//
//
//    int size = 0;
//    Node* headList1;
//    Node* headList2;
//    Node* node;
//    if (l1->size > l2->size)
//    {
//        headList1 = l1->pHead->pNext;
//        headList2 = l2->pHead->pNext;
//    }
//    else
//    {
//        headList1 = l2->pHead->pNext;
//        headList2 = l1->pHead->pNext;
//    }
//    
//    while (headList1)
//    {
//        while (headList2)
//        {
//            node = (Node*)malloc(sizeof(Node));
//            if (!node)
//            {
//                puts("内存分配失败!");
//                exit(-1);
//            }
//            if (headList1->data >= headList2->data)
//            {
//                node->data = headList2->data;
//                node->pNext = NULL;
//                tail->pNext = node;
//                tail = node;
//                headList2 = headList2->pNext;
//                ++size;
//            }
//            else
//                break;
//        }
//        node = (Node*)malloc(sizeof(Node));
//        if (!node)
//        {
//            puts("内存分配失败!");
//            exit(-1);
//        }
//        node->data = headList1->data;
//        node->pNext = NULL;
//        tail->pNext = node;
//        tail = node;
//        headList1 = headList1->pNext;
//        ++size;
//    }
//    l->pHead = head;
//    l->pTail = tail;
//    l->size = size;
//    return l;
//}
