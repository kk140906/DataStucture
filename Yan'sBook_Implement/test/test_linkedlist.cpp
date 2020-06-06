#include "../include/LinkedList.hpp"

void showListAllData(LinkedList* l,char* title)
{
    puts(title);
    Node* next = l->pHead->pNext;
    while (next)
    {
        printf("%c\t", *(int*)next->data);
        next = next->pNext;
    }
    puts("\n");
}


int main()
{
    char  Array[] = { 'a','b','c','x','y','z','t'};
    LinkedList l;
    LinkedList_Func->init(&l,sizeof(Array[0]));

    for (int i = 0; i < 7; ++i)
    {
        LinkedList_Func->addLast(&l,(LinkedListType)(Array+i));
    }
    showListAllData(&l,(char*)"初始链表:");

    char a = '1';
    if (LinkedList_Func->addFirst(&l,(LinkedListType)&a))
        showListAllData(&l,(char*)"链表首部插入字符'1':");
    char b = '2';
    if (LinkedList_Func->addLast(&l,(LinkedListType)&b))
        showListAllData(&l,(char*)"链表尾部插入字符'2':");
    char c = '3';
    if (LinkedList_Func->insert(&l,3,(LinkedListType)&c))
        showListAllData(&l,(char*)"链表第3个位置插入字符'3':");
    char d = '4';
    if (LinkedList_Func->insert(&l,-2,(LinkedListType)&d))
        showListAllData(&l,(char*)"链表倒数第2个位置插入字符'4':");

    LinkedListType removed;
    if(LinkedList_Func->remove(&l,2,(LinkedListType*)&removed))
    {
        showListAllData(&l,(char*)"移除链表第2个位置的字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(LinkedList_Func->remove(&l,-2,(LinkedListType*)&removed))
    {
        showListAllData(&l,(char*)"移除链表倒数第2个位置的字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(LinkedList_Func->removeFirst(&l,(LinkedListType*)&removed))
    {
        showListAllData(&l,(char*)"移除链表首部元素字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(LinkedList_Func->removeLast(&l,(LinkedListType*)&removed))
    {
        showListAllData(&l,(char*)"移除链表尾部元素字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }

    char e = 'm';
    if (LinkedList_Func->setFirstData(&l,(LinkedListType)&e))
        showListAllData(&l,(char*)"链表头部元素修改为字符'm':");
    char f = 'n';
    if (LinkedList_Func->setLastData(&l,(LinkedListType)&f))
        showListAllData(&l,(char*)"链表尾部元素修改为字符'n':");
    char g = 'o';
    if (LinkedList_Func->setData(&l,2,(LinkedListType)&g))
        showListAllData(&l,(char*)"链表第二个元素修改为字符'o':");
    char h = 'p';
    if (LinkedList_Func->setData(&l,-3,(LinkedListType)&h))
        showListAllData(&l,(char*)"链表倒数第三个元素修改为字符'p':");

    LinkedListType data;
    if(LinkedList_Func->getFirstData(&l,(LinkedListType*)&data))
        printf("链表首部元素 data:%c\n\n",*(char*)data);
    if(LinkedList_Func->getLastData(&l,(LinkedListType*)&data))
        printf("链表尾部元素 data:%c\n\n",*(char*)data);
    if(LinkedList_Func->getData(&l,3,(LinkedListType*)&data))
        printf("链表第3个元素 data:%c\n\n",*(char*)data);
    if(LinkedList_Func->getData(&l,-2,(LinkedListType*)&data))
        printf("链表倒数第2个元素 data:%c\n\n",*(char*)data);

    int size;
    size= LinkedList_Func->getSize(&l);
    printf("链表大小为:%d\n\n",size);
    
    int pos;
    char k = 'd';
    if (LinkedList_Func->locateData(&l,(LinkedListType)&k, &pos))
        printf("%c:在链表第%d个位置\n",k,pos);
    else
    {
        printf("%c:不在链表内\n",k);
    }
    
    LinkedList_Func->clear(&l);
    showListAllData(&l,(char*)"清空后的链表:");
    size= LinkedList_Func->getSize(&l);
    printf("清空后的链表大小为:%d\n\n",size);
    // LinkedList_Func->destory(&l);
    system("pause");
}