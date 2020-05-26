#define _CRT_SECURE_NO_DEPRECATE；
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
	int data;
	NODE* pNext;
} Node;

typedef struct 
{
	Node* pTop;
	Node* pBottom;
} Stack;

// 函数声明
bool init(Stack* pStack);
bool push(Stack* pStack,int var);
bool pop(Stack* pStack,int* pVar);
bool isEmpty(Stack* pStack);
bool clear(Stack* pStack);
void show(Stack* pStack);
bool destory(Stack* pStack);

int main(void)
{
	Stack stack;
	init(&stack);
	for (int i = 0; i < 15; ++i)
	{
		push(&stack, i);
	}
	
	show(&stack);
	int var;
	pop(&stack,&var);
	printf("\n出栈的元素是：%d\n",var);
	pop(&stack,&var);
	printf("\n出栈的元素是：%d\n",var);
	show(&stack);
	if (clear(&stack))
		show(&stack);
	return 0;
}

bool init(Stack* pStack)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
	{
		puts("内存分配失败！");
		return false;
	}
	node->pNext = NULL;
	pStack->pTop = pStack->pBottom = node;
	return true;
}

void show(Stack* pStack)
{
	if (isEmpty(pStack))
	{
		puts("栈为空栈！");
		return;
	}
	Node* pTop = pStack->pTop;
	puts("\n从栈顶到栈底的内容依次为:");
	while(pTop != pStack->pBottom)
	{
		printf("%d\t",pTop->data);
		pTop = pTop->pNext;
	}
	puts("\n");
}

bool push(Stack* pStack, int var)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
	{
		puts("内存分配失败！");
		return false;
	}
	node->data = var;
	node->pNext = pStack->pTop;
	pStack->pTop = node;
	return true;
}

bool pop(Stack* pStack, int* pVar)
{
	if (isEmpty(pStack))
	{
		puts("栈为空栈！");
		return false;
	}
	Node* pNode = pStack->pTop;
	*pVar = pNode->data;
	pStack->pTop = pStack->pTop->pNext;
	free(pNode);
	return true;
}
bool isEmpty(Stack* pStack)
{
	if(pStack->pTop == pStack->pBottom)
		return true;
	return false;
}
bool clear(Stack* pStack)
{
	if (isEmpty(pStack))
	{
		puts("栈为空栈！");
		return false;
	}
	Node* pNode = NULL;
	while(pStack->pTop != pStack->pBottom)
	{
		// pNode在循环内反复定义存在隐藏bug
		// 警告	C6001 使用未初始化的内存“* pStack->pTop”
		// Node* pNode = pStack->pTop;
		pNode = pStack->pTop;
		pStack->pTop = pNode->pNext;
		free(pNode);
	}
	return true;	
}