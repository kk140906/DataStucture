/*
    例2.1:求A = A U B
    插入法:插入法的本质是循环遍历两个集合，判断其中一个集合中的每一个元素是否在另一个集合中，如果不在即插入，如果在就继续判断下一个元素
*/
#include "../include/LinkedList.h"
// 插入法实现并集
void unionSets(List* l1, List* l2);
int main()
{
    int A[] = { 2,3,4,5 };
    int B[] = { 1,3,6,2,7 };
    List LA, LB;
    init(&LA, A, 4);
    init(&LB, B, 5);
    puts("A链表内容为:");
    show(&LA);
    puts("B链表内容为:");
    show(&LB);

    unionSets(&LA, &LB);
    puts("A与B求并集后A链表内容为:");
    show(&LA);
    return 0;
}


void unionSets(List* l1, List* l2)
{
    Node* next = l2->pHead->pNext;
    int var;
    while (next)
    {
        var = next->data;
        next = next->pNext;
        if (contain(l1, var))
            continue;

        Node* node = (Node*)malloc(sizeof(Node));
        if (!node)
        {
            puts("内存分配失败!");
            return;
        }
        node->data = var;
        node->pNext = NULL;
        l1->pTail->pNext = node;
        l1->pTail = node;
    }
}