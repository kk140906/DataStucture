#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int* top;
    int* bottom;
    int size;
}Stack;



//函数声明
void init(Stack* s, int size);
bool isFull(Stack* s);
bool isEmpty(Stack* s);
bool isDestoryed(Stack* s);
bool push(Stack* s, int var);
bool pop(Stack* s, int* pVar = NULL);
void show(Stack* s);
bool clear(Stack* s);
void destory(Stack* s);


int main(void)
{
    Stack s;
    init(&s, 5);
    puts(">>开始压栈...");
    for (int i = 0; i < 7; ++i)
    {
        if (push(&s, i))
            printf("数值:%d压栈成功\n", i);
    }
    puts("压栈后的栈内容为:");
    show(&s);


    puts(">>开始出栈...");
    int var;
    for (int i = 0; i < 3; ++i)
    {
        if (pop(&s, &var))
            printf("出栈成功,出栈数值：%d\n", var);
    }
    puts("出栈后的栈内容为:");
    show(&s);

    puts(">>开始销毁栈...");
    destory(&s);

    puts(">>开始清空栈...");
    if (clear(&s))
    {
        puts("清空后的栈内容为:");
        show(&s);
    }

    puts(">>开始再次压栈...");
    if (push(&s, 1))
    {
        printf("数值:%d压栈成功\n", 1);
        show(&s);
    }

    puts(">>开始再次出栈...");
    if (pop(&s, &var))
    {
        printf("出栈成功,出栈数值：%d\n", var);
        show(&s);
    }

    return 0;
}

void init(Stack* s, int size)
{
    s->size = size;
    ++size;
    s->bottom = (int*)malloc(sizeof(int) * size);
    if (!s->bottom)
    {
        puts("内存分配失败");
        exit(-1);
    }
    s->top = s->bottom = s->bottom;
}

bool isFull(Stack* s)
{
    if (s->top == s->bottom + s->size)
        return true;
    return false;
}


bool isEmpty(Stack* s)
{
    if (s->top == s->bottom)
        return true;
    return false;
}

bool isDestoryed(Stack* s)
{
    if (!s->top && !s->bottom && s->size == 0)
    {
        puts("栈已被销毁!");
        return true;
    }

    return false;
}

bool push(Stack* s, int var)
{
    if (isDestoryed(s))
        return false;
    if (isFull(s))
    {
        printf("数值:%d压栈失败!,栈已满!\n", var);
        return false;
    }
    ++s->top;
    *s->top = var;
    return true;
}


bool pop(Stack* s, int* pVar)
{
    if (isDestoryed(s))
        return false;
    if (isEmpty(s))
    {
        printf("出栈失败!,栈已空!\n");
        return false;
    }
    *pVar = *s->top;
    --s->top;
    return true;
}

void show(Stack* s)
{
    if (isDestoryed(s))
        return;
    int* top = s->top;
    while (top != s->bottom)
    {
        printf("%d\t", *top);
        --top;
    }
    puts("\n");
}

bool clear(Stack* s)
{
    if (isDestoryed(s))
        return false;
    if (isEmpty(s))
    {
        printf("栈已空!");
        return false;
    }
    s->top = s->bottom;
    return true;
}

void destory(Stack* s)
{
    free(s->bottom);
    //释放栈内存后避免再次被使用
    s->size = 0;
    s->top = NULL;
    s->bottom = NULL;
    puts("栈销毁成功！");
    return;
}
