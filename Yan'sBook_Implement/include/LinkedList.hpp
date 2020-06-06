#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 *  线性结构:链式结构
 */

#define LINKED_LIST_POSITION_ERROR -1

typedef enum{NO_INITIALED, IS_INITIALED = 99} LinkedListInitState;

typedef void* LinkedListType;

typedef struct NODE
{
    LinkedListType data;
    struct NODE* pNext;
}Node;

typedef struct
{
    Node* pHead ;
    Node* pTail ;
    int size ;
    int dataBytes  ;
    LinkedListInitState isInited  ;
}LinkedList;

typedef struct
{
    // 链表初始化
    void (*init)(LinkedList*, int);
    // 在链表最后追加一个新的元素
    bool (*addLast)(LinkedList*, LinkedListType);
    // 在链表最前面插入一个新的元素
    bool (*addFirst)(LinkedList*, LinkedListType);
    // 在链表某个位置插入新的元素
    bool (*insert)(LinkedList*, int, LinkedListType);
    // 移除链表最后一个元素
    bool (*removeLast)(LinkedList*, LinkedListType*);
    // 移除链表第一个元素
    bool (*removeFirst)(LinkedList*, LinkedListType*);
    // 移除链表某个位置的元素
    bool (*remove)(LinkedList*, int, LinkedListType*);
    // 设置链表最后一个元素的值
    bool (*setLastData)(LinkedList*, LinkedListType);
    // 设置链表第一个元素的值
    bool (*setFirstData)(LinkedList*, LinkedListType);
    // 设置链表某个位置的元素的值
    bool (*setData)(LinkedList*, int, LinkedListType);
    // 获取链表最后一个元素
    bool (*getLastData)(LinkedList*, LinkedListType*);
    // 获取链表第一个元素
    bool (*getFirstData)(LinkedList*, LinkedListType*);
    // 获取链表某一个位置的元素
    bool (*getData)(LinkedList*, int, LinkedListType*);
    // 查找链表内是否包含某个元素，并返回位置
    bool (*locateData)(LinkedList*, LinkedListType, int*);
    // 在链表内的一段区间内查找某个元素的所有位置
    bool (*locateAllData) (LinkedList*, int, int, LinkedListType, LinkedList*);
    // 判断链表是否为空
    bool (*isEmpty)(LinkedList*);
    // 获取链表大小
    int (*getSize)(LinkedList*);
    // 销毁链表
    void (*destory)(LinkedList*);
    // 清空链表
    void (*clear)(LinkedList*);
}LinkedListFuncs;

// 函数前置声明
void LinkedList_Init(LinkedList*, int);
bool LinkedList_AddLast(LinkedList*, LinkedListType);
bool LinkedList_AddFirst(LinkedList*, LinkedListType);
bool LinkedList_Insert(LinkedList*, int, LinkedListType);
bool LinkedList_RemoveLast(LinkedList*, LinkedListType*);
bool LinkedList_RemoveFirst(LinkedList*, LinkedListType*);
bool LinkedList_Remove(LinkedList*, int, LinkedListType*);
bool LinkedList_SetLastData(LinkedList*, LinkedListType);
bool LinkedList_SetFirstData(LinkedList*, LinkedListType);
bool LinkedList_SetData(LinkedList*, int, LinkedListType);
bool LinkedList_GetLastData(LinkedList*, LinkedListType*);
bool LinkedList_GetFirstData(LinkedList*, LinkedListType*);
bool LinkedList_GetData(LinkedList*, int, LinkedListType*);
bool LinkedList_LocateData(LinkedList*, LinkedListType, int*);
bool LinkedList_LocateAllData(LinkedList*, int, int, LinkedListType, LinkedList*);
bool LinkedList_IsEmpty(LinkedList*);
int LinkedList_GetSize(LinkedList*);
void LinkedList_Destory(LinkedList*);
void LinkedList_Clear(LinkedList*);
static int linkedlist_calPos(int, int);

/**
 * 链表初始化，创建头结点，初始化空间大小为0
 */
void LinkedList_Init(LinkedList* l, int dataBytes)
{
    l->pHead = (Node*)malloc(sizeof(Node));
    if (!l->pHead)
    {
        printf("内存分配失败,头结点创建失败!\n");
        exit(-1);
    }
    l->pHead->pNext = NULL;
    l->pTail = l->pHead;
    l->size = 0;
    l->dataBytes = dataBytes;
    l->isInited = IS_INITIALED;
}

/**
 * 链表末尾追加新的结点元素
 */ 
bool LinkedList_AddLast(LinkedList* l, LinkedListType var)
{
    if (LinkedList_Insert(l,-1,var))
        return true;
    return false;
}

/**
 * 链表头部插入新的结点元素
 */ 
bool LinkedList_AddFirst(LinkedList* l, LinkedListType var)
{
    if (LinkedList_Insert(l,1,var))
        return true;
    return false;
}

/**
 * 在链表指定位置插入新的元素
 */ 
bool LinkedList_Insert(LinkedList* l, int pos, LinkedListType var)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("链表未初始化!");
        exit(-1);
    }

    // size + 1 目的是为了可以向链表头部和尾部再插入一个新的元素
    if(LINKED_LIST_POSITION_ERROR == (pos = linkedlist_calPos(pos,l->size + 1)))
        return false;

	Node* pNode = l->pHead;

	// 插入结点只需将结点指针指向插入结点位置前一个结点
	for (int i = 1; i < pos; ++i)
	{
		pNode = pNode->pNext;
	}

	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
	{
		puts("内存分配失败!");
		return false;
	}
	node->data = var;
	node->pNext = pNode->pNext;
	pNode->pNext = node;
    ++l->size;
	return true;
}

/**
 * 移除链表末尾结点元素
 */ 
bool LinkedList_RemoveLast(LinkedList* l, LinkedListType* var)
{
    if (LinkedList_Remove(l,-1,var))
        return true;
    return false;
}

/**
 * 移除链表头部结点元素
 */ 
bool LinkedList_RemoveFirst(LinkedList* l, LinkedListType* var)
{
    if (LinkedList_Remove(l,1,var))
        return true;
    return false;
}

/**
 * 删除链表指定位置的元素，并把值返回
 */ 
bool LinkedList_Remove(LinkedList* l, int pos, LinkedListType* var)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    if (LinkedList_IsEmpty(l))
    {
        puts("链表为空!");
        return false;
    }

    if(LINKED_LIST_POSITION_ERROR == (pos = linkedlist_calPos(pos,l->size)))
        return false;

    // 删除结点只需将结点指针指向需要删除结点位置前一个结点，从头结点开始遍历需要遍历pos位置
    // 如果从首结点开始只需要遍历到'pos - 1'位置
    Node* pNode = l->pHead;
   
	for (int i = 1; i < pos; ++i)
	{
		pNode = pNode->pNext;
	}
    //需要被删除的结点在pNode的下一个结点

    if (var)
	    *var = pNode->pNext->data;

    Node* removedNode = pNode->pNext;
    pNode->pNext = removedNode->pNext;
    free(removedNode);
    --l->size;
    return true;
}

/**
 * 设置链表最后一个元素的值
 */ 
bool LinkedList_SetLastData(LinkedList* l, LinkedListType var)
{
    if (LinkedList_SetData(l,-1,var))
        return true;
    return false;
}

/**
 * 设置链表第一个元素的值
 */ 
bool LinkedList_SetFirstData(LinkedList* l, LinkedListType var)
{
    if (LinkedList_SetData(l,1,var))
        return true;
    return false;
}

/**
 * 设置链表某个位置的元素的值 
 */ 
bool LinkedList_SetData(LinkedList* l, int pos, LinkedListType var)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    if (LinkedList_IsEmpty(l))
    {
        puts("链表为空!");
        return false;
    }

    if(LINKED_LIST_POSITION_ERROR == (pos = linkedlist_calPos(pos,l->size)))
        return false;

    //定位结点到需要修改的结点上一个结点
    Node* pNode = l->pHead;
   
	for (int i = 1; i < pos; ++i)
	{
		pNode = pNode->pNext;
	}
    //需要被修改的结点在pNode的下一个结点
    pNode->pNext->data = var;
    return true;
}

/**
 * 获取链表最后一个位置的元素 
 */ 
bool LinkedList_GetLastData(LinkedList* l, LinkedListType* var)
{
    if (LinkedList_GetData(l,-1,var))
        return true;
    return false;
}

/**
 * 获取链表最后一个位置的元素 
 */ 
bool LinkedList_GetFirstData(LinkedList* l, LinkedListType* var)
{
    if (LinkedList_GetData(l,1,var))
        return true;
    return false;
}

/**
 * 获取链表某一个位置的元素 
 */ 
bool LinkedList_GetData(LinkedList* l, int pos, LinkedListType* var)
{
     if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    if (LinkedList_IsEmpty(l))
    {
        puts("链表为空!");
        return false;
    }

    if(LINKED_LIST_POSITION_ERROR == (pos = linkedlist_calPos(pos,l->size)))
        return false;

    // 定位结点到需要获取的结点上一个结点
    Node* pNode = l->pHead;
   
	for (int i = 1; i < pos; ++i)
	{
		pNode = pNode->pNext;
	}
    //需要获取的结点在pNode的下一个结点
    if (var)
        *var = pNode->pNext->data;
    return true;
}

/**
 * 判断某个值是否在链表内
 * 
 */ 
bool LinkedList_LocateData(LinkedList* l , LinkedListType var, int* pPos)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    if (LinkedList_IsEmpty(l))
    {
        puts("链表为空!");
        return false;
    }
    //从首结点开始比较
    Node* next = l->pHead->pNext;
    int pos = 1;
    while (next)
    {
        /**
         * LinkedListType 实际是void*类型的指针,函数形参变量var的地址一定与结点的数据域地址不同;
         * 这里直接根据初始化传输进来的数据字节大小比较内存里面的值
         */
        if (memcmp(var,next->data,l->dataBytes) == 0)
        {
            if (pPos)
                *pPos = pos;
            return true;
        }   
        next = next->pNext;
        ++pos;
    }
    return false;
}

/**
 * 在链表内的一段区间内查找某个元素的所有位置
 */ 
bool LinkedList_LocateAllData(
    LinkedList* l,
    int start,
    int stop,
    LinkedListType var,
    LinkedList* pPosList)
{
    return true;
}

/**
 * 判断链表是否为空
 */ 
bool LinkedList_IsEmpty(LinkedList* l )
{
    if (0 == l->size)
        return true;
    return false;
}

/**
 * 获取链表大小
 */ 
int LinkedList_GetSize(LinkedList* l)
{
    return l->size;
}

/**
 * 销毁整个链表
 */ 
void LinkedList_Destory(LinkedList* l)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    //从头结点开始释放内存
    Node* next = l->pHead;
    Node* pNode = NULL;
    while (next)
    {   pNode = next;
        next = pNode->pNext;
        free(pNode);
    }
    //释放后重置为NULL，防止再次被使用
    l->pTail = l->pHead = NULL;
    l->size = 0;
}
/**
 * 清空链表
 * 注意链表每次添加新的结点都会分配一次内存；
 * 在清空链表时需要把所有结点的内存全部释放,只留下头结点
 * 最后头结点的指针域重置为NULL，链表大小重置为0
 */ 
void LinkedList_Clear(LinkedList* l)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("链表未初始化!");
        exit(-1);
    }
    //从首结点开始释放内存
    Node* next = l->pHead->pNext;
    Node* pNode = NULL;
    while (next)
    {   pNode = next;
        next = pNode->pNext;
        free(pNode);
    }
    l->pHead->pNext = NULL;
    l->pTail = l->pHead;
    l->size = 0;
}

/**
 * 计算倒数位置
 */
static int linkedlist_calPos(int pos, int size)
{
    // pos合法的范围[1,size]
	if (pos > 0 && pos <= size) {}
    /**
     * pos表征的是第几个位置，0是无意义的，'size + 1'操作可以保证计数是从1开始的；
     */ 
	else if (pos < 0 && pos >= -size)
	{
		pos += size + 1;
	}
	else
	{
		puts("元素位置设置错误!");
		return LINKED_LIST_POSITION_ERROR;
	}
    return pos;
}

/**
 * LinkedList函数绑定
 */
LinkedListFuncs linkedlist_func = {
    LinkedList_Init,
    LinkedList_AddLast,
    LinkedList_AddFirst,
    LinkedList_Insert,
    LinkedList_RemoveLast,
    LinkedList_RemoveFirst,
    LinkedList_Remove,
    LinkedList_SetLastData,
    LinkedList_SetFirstData,
    LinkedList_SetData,
    LinkedList_GetLastData,
    LinkedList_GetFirstData,
    LinkedList_GetData,
    LinkedList_LocateData,
    LinkedList_LocateAllData,
    LinkedList_IsEmpty,
    LinkedList_GetSize,
    LinkedList_Destory,
    LinkedList_Clear };

/**
 * LinkedList外部调用接口
 */
LinkedListFuncs* LinkedList_Func = &linkedlist_func;

#endif // !_LINKED_LIST_