#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h> //stdlib.h 包含了malloc
/*
	数据结构：单向链表的创建
*/

typedef struct NODE {
	int data;
	NODE* pNext;
} Node;


// 函数声明
Node* create(void);//创建一个单向链表
void show(Node* pHead);//遍历链表
bool isEmpty(Node* pHead);//判断链表是否为空
int getSize(Node* pHead);//获取链表大小
bool append(Node* pHead, int var);//在链表最后附加一个值
bool insert(Node* pHead, int pos, int var);//在链表第几个位置插入一个值
bool remove(Node* pHead, int pos, int* pVar = NULL);//移除链表第几个位置的值,返回被移除的值
bool contains(Node* pHead, int var, int* pPos = NULL);//查找链表内是否包含某一个值,返回找到的位置
Node* reverse(Node* pHead);//翻转整个链表的值，结点的指针域发生了改变，需要返回一个新的链表
bool sort(Node* pHead);//链表排序
void fill(Node* pHead, int var = 0);//填充链表



int main()
{
	puts(">>开始创建链表:");
	Node* pHead = create();
	puts(">>链表创建完成，内容为:");
	show(pHead);

	puts(">>在链表末尾添加一个结点99:");
	if(append(pHead, 99))
		show(pHead);
	else
		puts(">>在链表末尾添加结点失败！");

	int size = getSize(pHead);
	printf(">>链表大小为:%d\n\n", size);

	puts(">>在链表第2个位置插入一个结点100:");
	if(insert(pHead, 2, 100))
		show(pHead);
	else
		puts(">>在链表第2个位置插入结点失败！");
	puts(">>在链表倒数第2个位置插入一个结点101:");
	if (insert(pHead, -2, 101))
		show(pHead);
	else
		puts(">>在链表倒数第2个位置插入结点失败！");

	int var;
	puts(">>删除链表第4个位置的结点:");
	if (remove(pHead, 4, &var))
	{
		printf(">>被删除的结点是:%d\n", var);
		show(pHead);
	}
	else
		puts(">>链表第4个位置结点删除失败！");
		
	puts(">>删除链表倒数第4个位置的结点:");
	if (remove(pHead, -4, &var))
	{
		printf(">>被删除的结点是:%d\n", var);
		show(pHead);
	}
	else
		puts(">>链表倒数第4个位置结点删除失败！");

	puts(">>查找链表中是否存在数值99:");
	int pos;
	if (contains(pHead, 99, &pos))
		printf(">>数值'%d'在链表第'%d'个位置\n\n", 99, pos);
	else
		printf(">>数值'%d'不在链表内\n\n", 99);
	if (contains(pHead, 3, &pos))
		printf(">>数值'%d'在链表第'%d'个位置\n\n", 3, pos);
	else
		printf(">>数值'%d'不在链表内\n\n", 3);
	
	puts(">>链表反转前内容为:");
	show(pHead);
	Node* node = reverse(pHead);
	puts(">>链表反转后内容为:");
	show(node);
	
	if (sort(node))
	{
		puts(">>链表升序排序后内容为:");
		show(node);
	}
	else
		puts(">>链表升序排序失败！");

	puts(">>用数值1000填充整个链表后的内容为:");
	fill(node, 1000);
	show(node);
	//getchar();
}

Node* create(void)
{
	// 头插法创建单向链表
	Node* pHead = (Node*)malloc(sizeof(Node));
	if (!pHead)
	{
		puts("头结点内存分配失败!");
		exit(-1);
	}
	//把头结点即看做头结点也看做尾结点,赋值为NULL保证尾结点不指向别的地方
	pHead->pNext = NULL;

	printf("请输入需要创建的链表长度:");
	int length;
	scanf("%d", &length);
	for (int i = 0; i < length; ++i)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		if (!node)
		{
			puts("尾结点内存分配失败!");
			exit(-1);
		}
		printf("请输入链表第%d个结点的数值:", i + 1);
		scanf("%d", &node->data);
		/*
			pHead  data|pNext ------> NULL
						 |			  ^
						 |			  |
						 v			  |
					   node    data|pNext
		*/
		node->pNext = pHead->pNext;
		pHead->pNext = node;
	}
	return pHead;
}

void show(Node* pHead)
{
	if(isEmpty(pHead))
	{
		puts("链表为空");
		return;
	}
	while (pHead->pNext)
	{
		printf("%d\t", pHead->pNext->data);
		pHead = pHead->pNext;
	}
	puts("\n");
}

bool isEmpty(Node* pHead)
{
	if (!pHead->pNext)
		return true;
	return false;
}

int getSize(Node* pHead)
{
	int i = 0;
	while (pHead->pNext)
	{
		++i;
		pHead = pHead->pNext;
	}
	return i;
}

bool append(Node* pHead, int var)
{
	Node* pNode = pHead;
	while (pNode->pNext)
		pNode = pNode->pNext;
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
	{
		puts("内存分配失败,附加失败！");
		return false;
	}
	node->data = var;
	node->pNext = NULL;
	pNode->pNext = node;
	return true;
}
bool insert(Node* pHead, int pos, int var)
{
	int size = getSize(pHead);

	if (pos > 0 && pos <= size + 1)
	{

	}
	else if (pos < 0 && pos >= -1 * size)
	{
		pos += size + 1;
	}
	else
	{
		puts("插入位置设置错误！");
		return false;
	}

	Node* pNode = pHead;

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
	return true;
}

bool remove(Node* pHead, int pos, int* pVar)
{
	if (isEmpty(pHead))
		{
			puts("链表为空！");
			return false;
		}

	int size = getSize(pHead);

	if (pos > 0 && pos <= size + 1)
	{

	}
	else if (pos < 0 && pos >= -1 * size)
	{
		pos += size + 1;
	}
	else
	{
		puts("删除位置设置错误！");
		return false;
	}

	Node* pNode = pHead;

	// 删除结点只需将结点指针指向被删除的结点位置的前一个结点
	for (int i = 1; i < pos; ++i)
	{
		pNode = pNode->pNext;
	}

	*pVar = pNode->pNext->data;
	//暂存需要被删除的结点,以便删除结点时释放内存，如果结点被删除确不释放内存将会导致内存泄漏
	Node* tempNode = pNode->pNext;
	pNode->pNext = pNode->pNext->pNext;
	free(tempNode);
	return true;
}

bool contains(Node* pHead, int var, int* pPos)
{
	if (isEmpty(pHead))
	{
		puts("链表为空！");
		return false;
	}
	int pos = 0;
	while (pHead->pNext)
	{
		++pos;
		if (pHead->pNext->data == var)
		{
			*pPos = pos;
			return true;
		}
		pHead = pHead->pNext;
	}
	return false;
}


Node* reverse(Node* pHead)
{
	if(isEmpty(pHead))
	{
		puts("链表为空！");
		return pHead;
	}

	Node* pNode = pHead->pNext;
	Node* pNextNode = NULL;
	Node* pPreviousNode = NULL;
	while(pNode->pNext)
	{
		/*
			前后指针法实现链表反转
		*/
		//暂存下一个结点的内容
		pNextNode = pNode->pNext;
		//当前结点指向前一个结点
		pNode->pNext = pPreviousNode;
		//使当前结点成为下一个结点的前一个结点
		pPreviousNode = pNode;
		//当前结点移动到下一个结点
		pNode = pNextNode;
	}
	//使最后一个结点指向前一个结点
	pNode->pNext = pPreviousNode;
	//使头结点指向新链表的首结点
	pHead->pNext = pNode;
	return pHead;
}
bool sort(Node* pHead)
{
	if (isEmpty(pHead))
	{
		puts("链表为空！");
		return false;
	}
	/*
	选择排序：升序排列
	*/
	Node* pNode = pHead->pNext;
	while (pNode->pNext)
	{
		Node* pNextNode = pNode->pNext;
		while (pNextNode)
		{
			if (pNode->data > pNextNode->data)
			{
				int temp = pNode->data;
				pNode->data = pNextNode->data;
				pNextNode->data = temp;
			}
			pNextNode = pNextNode->pNext;
		}
		pNode = pNode->pNext;
	}
	return true;
}
void fill(Node* pHead, int var)
{
	Node* pNode = pHead->pNext;
	while (pNode)
	{
		pNode->data = var;
		pNode = pNode->pNext;
	}
}