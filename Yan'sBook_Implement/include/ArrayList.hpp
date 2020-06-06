#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
    线性结构:顺序结构
*/

#define ARRAY_LIST_POSITION_ERROR -1

typedef enum{NO_INITIALED, IS_INITIALED = 99} ArrayListInitState;

typedef void* ArrayListType;

typedef struct
{
    ArrayListType* base;
    ArrayListType data ;
    int size;
    int capacity;
    bool isAutoResize;
    int dataBytes;
    ArrayListInitState isInited ;
}ArrayList;

typedef struct
{
    // 数组初始化
    void (*init)(ArrayList*, int, int, bool);
    // 在数组最后追加一个新的元素
    bool (*addLast)(ArrayList*, ArrayListType);
    // 在数组最前面插入一个新的元素
    bool (*addFirst)(ArrayList*, ArrayListType);
    // 在数组某个位置插入新的元素
    bool (*insert)(ArrayList*, int, ArrayListType);
    // 移除数组最后一个元素
    bool (*removeLast)(ArrayList*, ArrayListType*);
    // 移除数组第一个元素
    bool (*removeFirst)(ArrayList*, ArrayListType*);
    // 移除数组某个位置的元素
    bool (*remove)(ArrayList*, int, ArrayListType*);
    // 设置数组最后一个元素
    bool (*setLastData)(ArrayList*, ArrayListType);
    // 设置数组第一个元素
    bool (*setFirstData)(ArrayList*, ArrayListType);
    // 设置数组某个位置的元素
    bool (*setData)(ArrayList*, int, ArrayListType);
    // 获取数组最后一个元素
    bool (*getLastData)(ArrayList*, ArrayListType*);
    // 获取数组第一个元素
    bool (*getFirstData)(ArrayList*, ArrayListType*);
    // 获取数组某个位置的元素
    bool (*getData)(ArrayList*, int, ArrayListType*);
    // 查找数组内是否包含某个元素，并返回位置
    bool (*locateData)(ArrayList*, ArrayListType, int*);
    // 在数组内的一段区间内查找某个元素的所有位置
    bool (*locateAllData) (ArrayList*, int, int, ArrayListType, ArrayList*);
    // 判断数组是否已满
    bool (*isFull)(ArrayList*);
    // 判断数组是否为空
    bool (*isEmpty)(ArrayList*);
    // 获取数组大小
    int (*getSize)(ArrayList*);
    // 销毁数组
    void (*destory)(ArrayList*);
    // 清空数组
    void (*clear)(ArrayList*);
}ArrayListFuncs;

// 函数前置声明
void ArrayList_Init(ArrayList*, int, int, bool);
bool ArrayList_AddLast(ArrayList*, ArrayListType);
bool ArrayList_AddFirst(ArrayList*, ArrayListType);
bool ArrayList_Insert(ArrayList*, int, ArrayListType);
bool ArrayList_RemoveLast(ArrayList*, ArrayListType*);
bool ArrayList_RemoveFirst(ArrayList*, ArrayListType*);
bool ArrayList_Remove(ArrayList*, int, ArrayListType*);
bool ArrayList_SetLastData(ArrayList*, ArrayListType);
bool ArrayList_SetFirstData(ArrayList*, ArrayListType);
bool ArrayList_SetData(ArrayList*, int, ArrayListType);
bool ArrayList_GetLastData(ArrayList*, ArrayListType*);
bool ArrayList_GetFirstData(ArrayList*, ArrayListType*);
bool ArrayList_GetData(ArrayList*, int, ArrayListType*);
bool ArrayList_LocateData(ArrayList*, ArrayListType, int*);
bool ArrayList_LocateAllData(ArrayList*, int, int, ArrayListType, ArrayList*);
bool ArrayList_IsFull(ArrayList*);
bool ArrayList_IsEmpty(ArrayList*);
int ArrayList_GetSize(ArrayList*);
void ArrayList_Destory(ArrayList*);
void ArrayList_Clear(ArrayList*);
static int Arraylist_calPos(int, int);

/**
 * 数组初始化，创建头结点，初始化空间大小为0
 */
void ArrayList_Init(ArrayList* l, int dataBytes, int capacity, bool isAutoResize)
{
    l->capacity = capacity;
    l->size = 0;
    l->dataBytes = dataBytes;
    l->isAutoResize = isAutoResize;
    l->isInited = IS_INITIALED;
    /**
     * 
     * 内存分配一定要记得转换内存大小类型为size_t,不同的运行环境转换和计算可能会丢失精度.
     * 导致分配的内存没有预想的那么大,在多次对内存写操作时就会发生堆溢出
     * 在这个地方以及后面所有涉及内存分配地方的memsize的计算不能用
     * size_t memsize = (size_t)l->dataBytes * (size_t)l->capacity;
     * l->base实际是void**的指针变量,存放的是data的地址.而不是data本身,data的地址所占据的大小根据编译环境可能是4也可能是8,
     * 如果这时候l->dataBytes的大小比l->base所占据的大小小的就会导致l->base实际分配的空间没有预想的那么大
     * 在多次++l->base操作并向指向内存写值就会发生在堆结束位置之后写内容错误！
     * 'the application wrote to memory after end of heap buffer'或者'SIGTRAP,Trace/breakpoint trap'
     * 
     */ 
    size_t memsize = sizeof(ArrayListType) * (size_t)l->capacity;
    l->base = (ArrayListType*)malloc(memsize);
    if (!l->base)
    {
        puts("内存分配失败!");
        exit(-1);
    }
}

/**
 * 数组末尾追加新的结点元素
 */ 
bool ArrayList_AddLast(ArrayList* l, ArrayListType var)
{
    return ArrayList_Insert(l,-1,var);
}

/**
 * 数组头部插入新的结点元素
 */ 
bool ArrayList_AddFirst(ArrayList* l, ArrayListType var)
{
    return ArrayList_Insert(l,1,var);
}

/**
 * 在数组指定位置插入新的元素
 */ 
bool ArrayList_Insert(ArrayList* l, int pos, ArrayListType var)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("数组未初始化!");
        exit(-1);
    }
    if (ArrayList_IsFull(l))
    {
        if (l->isAutoResize)
        {
            //自动调整内存大小为原来的2倍，防止满了再次添加的时候再次重新分配内存

            l->capacity *= 2;
            ArrayListType* tempBase = NULL;
            size_t memsize = sizeof(ArrayListType) * (size_t)l->capacity;
            tempBase = (ArrayListType*)realloc(l->base,memsize);
            if (!l->base)
            {
                puts("内存分配失败!");
                exit(-1);       
            }
            l->base = tempBase;
        }
        else
        {
            puts("数组已满!");
            return false;
        }
    }
    
    // size + 1 目的是为了可以向数组头部和尾部再插入一个新的元素
    if(ARRAY_LIST_POSITION_ERROR == (pos = Arraylist_calPos(pos,l->size + 1)))
        return false;

    int tail = l->size - 1;
    while(tail >= pos - 1)
    {
        // memcpy(l->base+tail+1,l->base+tail,l->dataBytes);
        l->base[tail + 1] = l->base[tail];
        --tail;
    }
    l->base[pos - 1] = var;
    ++l->size;
	return true;
}

/**
 * 移除数组末尾结点元素
 */ 
bool ArrayList_RemoveLast(ArrayList* l, ArrayListType* var)
{
    return ArrayList_Remove(l,-1,var);
}

/**
 * 移除数组头部结点元素
 */ 
bool ArrayList_RemoveFirst(ArrayList* l, ArrayListType* var)
{
    return ArrayList_Remove(l,1,var);
}

/**
 * 删除数组指定位置的元素，并把值返回
 */ 
bool ArrayList_Remove(ArrayList* l, int pos, ArrayListType* var)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("数组未初始化!");
        exit(-1);
    }

    if (ArrayList_IsEmpty(l))
    {
        puts("数组为空!");
        return false;
    }
    // 此处利用'lazy'的方式,当移除后的元素个数小于容量的1/4就调整大小,防止后续频繁插入移除时内存频繁分配
    if (l->isAutoResize && l->size <= l->capacity / 4 && l->capacity / 2 != 0)
    {
        l->capacity /= 2;
        ArrayListType* tempBase;
        size_t memsize = sizeof(ArrayListType) * (size_t)l->capacity;
        tempBase = (ArrayListType*)realloc(l->base,memsize);
        if (!tempBase)
        {
            puts("内存分配失败!");
            exit(-1);       
        }
        l->base = tempBase;
    }

    if(ARRAY_LIST_POSITION_ERROR == (pos = Arraylist_calPos(pos,l->size)))
        return false;

    if (var)
	    *var = l->base[pos - 1];
    while(pos <= l->size - 1)
    {
        l->base[pos-1] = l->base[pos];
        ++pos;
    }
    --l->size;
    return true;
}

/**
 * 设置数组最后一个元素的值
 */ 
bool ArrayList_SetLastData(ArrayList* l, ArrayListType var)
{
    return ArrayList_SetData(l,-1,var);
}

/**
 * 设置数组第一个元素的值
 */ 
bool ArrayList_SetFirstData(ArrayList* l, ArrayListType var)
{
    return ArrayList_SetData(l,1,var);
}

/**
 * 设置数组某个位置的元素的值 
 */ 
bool ArrayList_SetData(ArrayList* l, int pos, ArrayListType var)
{
    if (IS_INITIALED != l->isInited)
    {
        puts("数组未初始化!");
        exit(-1);
    }
    if (ArrayList_IsEmpty(l))
    {
        puts("数组为空!");
        return false;
    }

    if(ARRAY_LIST_POSITION_ERROR == (pos = Arraylist_calPos(pos,l->size)))
        return false;

    l->base[pos - 1] = var;
    return true;
}

/**
 * 获取数组最后一个位置的元素 
 */ 
bool ArrayList_GetLastData(ArrayList* l, ArrayListType* var)
{
    return ArrayList_GetData(l,-1,var);
}

/**
 * 获取数组最后一个位置的元素 
 */ 
bool ArrayList_GetFirstData(ArrayList* l, ArrayListType* var)
{
    return ArrayList_GetData(l,1,var);
}

/**
 * 获取数组某一个位置的元素 
 */ 
bool ArrayList_GetData(ArrayList* l, int pos, ArrayListType* var)
{
     if (IS_INITIALED != l->isInited)
    {
        puts("数组未初始化!");
        exit(-1);
    }
    if (ArrayList_IsEmpty(l))
    {
        puts("数组为空!");
        return false;
    }

    if(ARRAY_LIST_POSITION_ERROR == (pos = Arraylist_calPos(pos,l->size)))
        return false;

    if (var)
        *var = l->base[pos-1];
    return true;
}

/**
 * 判断某个值是否在数组内
 * 
 */ 
bool ArrayList_LocateData(ArrayList* l , ArrayListType var, int* pPos)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("数组未初始化!");
        exit(-1);
    }

    if (ArrayList_IsEmpty(l))
    {
        puts("数组为空!");
        return false;
    }
    
    int pos = 1;
    while (pos <= l->size)
    {
        /**
         * ArrayListType 实际是void*类型的指针,函数形参变量var的地址一定与结点的数据域地址不同;
         * 这里直接根据初始化传输进来的数据字节大小比较内存里面的值
         */
        if (memcmp(var,l->base[pos-1],l->dataBytes) == 0)
        {
            if (pPos)
                *pPos = pos;
            return true;
        }   

        ++pos;
    }
    return false;
}

/**
 * 在数组内的一段区间内查找某个元素的所有位置
 */ 
bool ArrayList_LocateAllData(
    ArrayList* l,
    int start,
    int stop,
    ArrayListType var,
    ArrayList* pPosList)
{
    return true;
}

/**
 * 判断数组是否为满
 */ 
bool ArrayList_IsFull(ArrayList* l )
{
    // 注意数组满的时候容量大小一定不能是0
    if (l->capacity && l->capacity == l->size)
        return true;
    return false;
}

/**
 * 判断数组是否为空
 */ 
bool ArrayList_IsEmpty(ArrayList* l )
{
    if (0 == l->size)
        return true;
    return false;
}

/**
 * 获取数组大小
 */ 
int ArrayList_GetSize(ArrayList* l)
{
    return l->size;
}

/**
 * 销毁整个数组
 */ 
void ArrayList_Destory(ArrayList* l)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("数组未初始化!");
        exit(-1);
    }

    free(l->base);
    l->base = NULL;
    l->size = 0;
}
/**
 * 清空数组
 * 注意数组每次添加新的结点都会分配一次内存；
 * 在清空数组时需要把所有结点的内存全部释放,只留下头结点
 * 最后头结点的指针域重置为NULL，数组大小重置为0
 */ 
void ArrayList_Clear(ArrayList* l)
{
    if (IS_INITIALED != l->isInited )
    {
        puts("数组未初始化!");
        exit(-1);
    }
    
    for(int i = 0; i < l->size; ++i)
    {
        l->base[i] = NULL;
    }
    l->size = 0;
}

/**
 * 计算倒数位置
 */
static int Arraylist_calPos(int pos, int size)
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
		return ARRAY_LIST_POSITION_ERROR;
	}
    return pos;
}

/**
 * ArrayList函数绑定
 */
ArrayListFuncs ArrayList_func = {
    ArrayList_Init,
    ArrayList_AddLast,
    ArrayList_AddFirst,
    ArrayList_Insert,
    ArrayList_RemoveLast,
    ArrayList_RemoveFirst,
    ArrayList_Remove,
    ArrayList_SetLastData,
    ArrayList_SetFirstData,
    ArrayList_SetData,
    ArrayList_GetLastData,
    ArrayList_GetFirstData,
    ArrayList_GetData,
    ArrayList_LocateData,
    ArrayList_LocateAllData,
    ArrayList_IsFull,
    ArrayList_IsEmpty,
    ArrayList_GetSize,
    ArrayList_Destory,
    ArrayList_Clear };

/**
 * ArrayList外部调用接口
 */
ArrayListFuncs* ArrayList_Func = &ArrayList_func;

#endif // !_ARRAY_LIST_