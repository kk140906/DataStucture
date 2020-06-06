#include "../include/ArrayList.hpp"
/*
    线性表LA、LB按照非递减有序排列,实现LA、LB归并为LC仍然按照非递减有序排列
    LA = (3,5,8,11);
    LB = (2,6,8,8,11,15,20);
    LC = (2,3,5,6,8,8,8,11,11,15,20);
*/

ArrayList unionSets(ArrayList* l1, ArrayList* l2);
void showListAllData(ArrayList* l, char* title);

int main()
{
    int sizeA = 4;
    int sizeB = 7;
    int A[] = { 3,5,8,11 };
    int B[] = { 2,6,8,8,11,15,20 };
    ArrayList LA, LB;
    ArrayList_Func->init(&LA, sizeof(A[0]), sizeA,false);
    ArrayList_Func->init(&LB, sizeof(B[0]),sizeB,false);
    for (int i = 0; i < sizeA; ++i)
    {
        ArrayList_Func->addLast(&LA, (ArrayListType)(A + i));
    }
    showListAllData(&LA, (char*)"A链表内容:");
    for (int i = 0; i < sizeB; ++i)
    {
        ArrayList_Func->addLast(&LB, (ArrayListType)(B + i));
    }
    showListAllData(&LB, (char*)"B链表内容:");

    ArrayList LC = unionSets(&LA, &LB);
    showListAllData(&LC, (char*)"A链表与B链表求并集后C链表内容为:");
    return 0;
}


void showListAllData(ArrayList* l, char* title)
{
    puts(title);
    for (int i = 0; i < l->size; ++i)
    {
        printf("%d\t", *(char*)l->base[i]);
    }
    puts("\n");
}

/**
 * L1,l2都是已经排序完毕的非递减序列
 * 直接循环比较,保证元素个数少的先排完序，然后再把元素个数多剩余部门直接添加到新的列表后面
 */
ArrayList unionSets(ArrayList* l1, ArrayList* l2)
{
    ArrayList list;
    int capacity = l1->size + l2->size;
    ArrayList_Func->init(&list, l1->dataBytes, capacity,false);
    int l1_pos = 1, l2_pos = 1;
    ArrayListType* pL1 = l1->base;
    ArrayListType* pL2 = l2->base; 
    ArrayListType* pList = list.base;

    // 如果指针直接操作内存,数组内统计实际元素个数的参数是没有变化的,每次操作后需要手动给size加1
    while (l1_pos <= l1->size && l2_pos <= l2->size)
    {
        if (memcmp(*pL1, *pL2, l1->dataBytes) <= 0)
        {
            *pList++ = *pL1++;
            ++l1_pos;
        }
        else
        {
            *pList++ = *pL2++;
            ++l2_pos;
        }
        ++list.size;
    }

    while (l1_pos <= l1->size)
    {
        *pList++ = *pL1++;
        ++l1_pos;
        ++list.size;
    }

    while (l2_pos <= l2->size)
    {
        *pList++ = *pL2++;
        ++l2_pos;
        ++list.size;
    }
    
    return list;
}

