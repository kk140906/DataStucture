#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h> //stdlib.h 包含了malloc
/*
    数据结构：数组的创建
    数组长度从0开始计数，数值表示数组包含多少个元素
    数组索引下标从0开始计数
    元素位置从1开始计数，数值表示元素在数组的第几个位置
*/

typedef struct {
    int maxLenth; //数组最大长度
    int length; //数组元素个数
    int* pArrHead; //数组首地址
    bool isArrResize; //是否是自增长数组
} Array;


// 函数声明
void initArr(Array* pArr, int maxLength = 0); //数组初始化,当不设定数组最大长度时,数组长度自动修改
bool isEmpty(Array*);//判断数组是否为空
bool isFull(Array* pArr);//判断数组是否已满
void showArr(Array* pArr);//显示数组内容
bool append(Array* pArr, int var);//在数组最后附加一个值
bool insert(Array* pArr, int pos, int var);//在数组第几个位置插入一个值
bool remove(Array* pArr, int pos, int* pVar);//移除数组第几个位置的值,返回被移除的值
bool contains(Array* pArr, int var, int* pPos = NULL);//查找数组内是否包含某一个值,返回找到的位置
Array reverse(Array* pArr);//翻转整个数组的值
Array sort(Array* pArr);//数组排序
void fill(Array* pArr, int var = 0);//填充数组
int getSize(Array* pArr);//获取数组大小


int main()
{
    Array arr;
    //数组初始化
    initArr(&arr);
    for (int i = 0; i < 10; ++i)
    {
        //在数组最后追加赋值
        append(&arr, i);
    }
    puts("追加后的数组内容为:");
    showArr(&arr);
    //在数组倒数第二个位置插入一个元素
    if (insert(&arr, -2, 99))
    {
        puts("在倒数第2个位置插入一个元素后的数组内容为:");
        showArr(&arr);
    }
    //在数组第二个位置插入一个元素
    if (insert(&arr, 2, 15))
    {
        puts("在第2个位置插入一个元素后的数组内容为:");
        showArr(&arr);
    }
    //移除数组倒数第7个位置的元素,并把移除的数值返回
    int var;
    if (remove(&arr, -7, &var))
    {
        printf("被删除的数值是：%d\n", var);
        puts("在倒数第7个位置删除一个元素后的数组内容为:");
        showArr(&arr);
    }
    //移除数组第4个位置的元素,并把移除的数值返回
    if (remove(&arr, 5, &var))
    {
        printf("被删除的数值是：%d\n", var);
        puts("在第4个位置删除一个元素后的数组内容为:");
        showArr(&arr);
    }
    //判断数组是否包含某一个数值,并把位置返回
    int pos;
    if (contains(&arr, 2, &pos))
    {
        printf("查找的数值：%d 在数组第 %d 个位置\n\n", 2, pos);
    }
    //翻转数组,返回一个新的数组
    Array newarr = reverse(&arr);
    puts("翻转后的数组内容为:");
    showArr(&newarr);
    //升序排列数组,返回一个新的数组
    Array sortedArr = sort(&newarr);
    puts("升序排列后的数组内容为:");
    showArr(&sortedArr);
    //填充数组
    fill(&arr, 2);
    puts("填充后的数组内容为:");
    showArr(&arr);
    //获取数组大小
    printf("数组大小：%d\n", getSize(&arr));

    free(arr.pArrHead);
    free(newarr.pArrHead);
    free(sortedArr.pArrHead);
    //getchar();
}

void initArr(Array* pArr, int maxLength)
{
    int* pArrHead = (int*)malloc(sizeof(int) * maxLength);
    if (NULL == pArrHead)
    {
        puts("内存分配失败!");
        exit(-1);
    }
    pArr->length = 0;
    pArr->maxLenth = maxLength;
    pArr->pArrHead = pArrHead;
    if (0 == maxLength)
        pArr->isArrResize = true;
    else
        pArr->isArrResize = false;
}


bool isEmpty(Array* pArr)
{
    if (0 == pArr->length)
        return true;
    return false;
}

bool isFull(Array* pArr)
{
    if (pArr->maxLenth == pArr->length)
        return true;
    return false;
}

void showArr(Array* pArr)
{
    for (int i = 0; i < pArr->length; ++i)
    {
        printf("%d\t", pArr->pArrHead[i]);
    }
    puts("\n");
}

bool append(Array* pArr, int var)
{
    if (isFull(pArr))
    {
        /*
            数组自增长
        */
        if (pArr->isArrResize)
        {
            ++pArr->maxLenth;
            int* pArrHead = (int*)realloc(pArr->pArrHead, sizeof(Array) * pArr->maxLenth);
            if (!pArrHead)
            {
                puts("附加失败,内存空间不足!");
                return false;
            }
            pArr->pArrHead = pArrHead;
        }
        else
        {
            puts("附加失败,数组空间已满!");
            return false;
        }
    }
    pArr->pArrHead[pArr->length] = var;
    ++pArr->length;
    return true;
}


bool insert(Array* pArr, int pos, int var)
{
    /*
    length表示元素的个数,pos表示第几个元素的位置,计数都是从1开始
    数组下标从0开始计数，注意切换
    */

    if (0 < pos && pos <= pArr->maxLenth)
    {

    }
    else if (-1 * pArr->maxLenth <= pos && pos < 0)
    {
        pos += pArr->maxLenth + 1;
    }
    else
    {
        puts("插入失败,插入位置超出范围！");
        return false;
    }

    if (isFull(pArr))
    {
        if (pArr->isArrResize)
        {
            ++pArr->maxLenth;
            int* pArrHead = (int*)realloc(pArr->pArrHead, sizeof(Array) * pArr->maxLenth);
            if (!pArrHead)
            {
                puts("插入失败,内存空间不足!");
                return false;
            }
            pArr->pArrHead = pArrHead;
        }
        else
        {
            puts("插入失败,数组空间已满!");
            return false;
        }
    }
    if (isEmpty(pArr))
    {

    }
    for (int i = pArr->length - 1; i >= pos - 1; --i)
    {
        pArr->pArrHead[i + 1] = pArr->pArrHead[i];
    }
    pArr->pArrHead[pos - 1] = var;
    ++pArr->length;
    return true;
}


bool remove(Array* pArr, int pos, int* pVar)
{
    if (isEmpty(pArr))
    {
        puts("数组为空，无法删除！");
        return false;
    }

    if (0 < pos && pos <= pArr->maxLenth)
    {

    }
    else if (-1 * pArr->maxLenth <= pos && pos < 0)
    {
        pos += pArr->maxLenth + 1;
    }
    else
    {
        puts("删除失败,删除位置超出范围！");
        return false;
    }
    *pVar = pArr->pArrHead[pos - 1];
    for (int i = pos; i <= pArr->length - 1; ++i)
    {
        pArr->pArrHead[i - 1] = pArr->pArrHead[i];
    }
    --pArr->length;
    if (pArr->isArrResize)
    {
        --pArr->maxLenth;
        int* pArrHead = (int*)realloc(pArr->pArrHead, sizeof(Array) * pArr->maxLenth);
        if (!pArrHead)
        {
            puts("删除失败,内存空间不足!");
            return false;
        }
        pArr->pArrHead = pArrHead;
    }
    return true;
}

bool contains(Array* pArr, int var, int* pPos)
{
    for (int i = 0; i < pArr->length; ++i)
    {
        if (var == pArr->pArrHead[i])
        {
            if (pPos)
                *pPos = i + 1;
            return true;
        }
    }
    return false;
}

Array reverse(Array* pArr)
{
    Array newArr = *pArr;
    /*
    数组的首地址以指针形式存储,
    如果不希望修改实参的值,newArr = *pArr或者整个结构体的内存拷贝都是无法实现的,
    因为数组的首地址并没有改变
    如果要实现不修改实参的值就需要在结构体内部重新指定数组的首地址,再通过一次内存拷贝数组首地址实现；
    */
    int* head = (int*)malloc(sizeof(int) * pArr->maxLenth);
    memcpy(head, pArr->pArrHead, sizeof(int) * pArr->maxLenth);
    newArr.pArrHead = head;
    int i = 0, j = newArr.length - 1;
    int temp;
    while (i < j)
    {
        temp = newArr.pArrHead[i];
        newArr.pArrHead[i] = newArr.pArrHead[j];
        newArr.pArrHead[j] = temp;
        ++i;
        --j;
    }
    return newArr;
}

Array sort(Array* pArr)
{
    Array newArr = *pArr;
    int* head = (int*)malloc(sizeof(int) * pArr->maxLenth);
    memcpy(head, pArr->pArrHead, sizeof(int) * pArr->maxLenth);
    newArr.pArrHead = head;
    //冒泡排序
    for (int i = 0; i < newArr.length - 1; ++i)
    {
        for (int j = 0; j < newArr.length - 1 - i; ++j)
        {
            if (newArr.pArrHead[j] > newArr.pArrHead[j + 1])
            {
                int temp = newArr.pArrHead[j];
                newArr.pArrHead[j] = newArr.pArrHead[j + 1];
                newArr.pArrHead[j + 1] = temp;
            }
        }
    }
    return newArr;
}
void fill(Array* pArr, int var)
{
    for (int i = 0; i < pArr->length; ++i)
    {
        pArr->pArrHead[i] = var;
    }
    return;
}
int getSize(Array* pArr)
{
    return pArr->length;
}