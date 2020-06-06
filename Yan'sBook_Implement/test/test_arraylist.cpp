
#include "../include/ArrayList.hpp"

void showListAllData(ArrayList* l,char* title)
{
    puts(title);
    for (int i = 0; i < l->size; ++i)
    {
        printf("%c\t", *(char*)l->base[i]);
    }
    puts("\n");
}


int main()
{
    char  Array[] = { 'a','b','c','x','y','z','t'};
    ArrayList l;
    ArrayList_Func->init(&l,sizeof(Array[0]), 7,true);

    for (int i = 0; i < 7; ++i)
    {
        ArrayList_Func->addLast(&l,(ArrayListType)(Array+i));
    }
    showListAllData(&l,(char*)"初始数组:");

    char a = '1';
    if (ArrayList_Func->addFirst(&l,(ArrayListType)&a))
        showListAllData(&l,(char*)"数组首部插入字符'1':");
    char b = '2';
    if (ArrayList_Func->addLast(&l,(ArrayListType)&b))
        showListAllData(&l,(char*)"数组尾部插入字符'2':");
    char c = '3';
    if (ArrayList_Func->insert(&l,3,(ArrayListType)&c))
        showListAllData(&l,(char*)"数组第3个位置插入字符'3':");
    char d = '4';
    if (ArrayList_Func->insert(&l,-2,(ArrayListType)&d))
        showListAllData(&l,(char*)"数组倒数第2个位置插入字符'4':");

    ArrayListType removed;
    if(ArrayList_Func->remove(&l,2,(ArrayListType*)&removed))
    {
        showListAllData(&l,(char*)"移除数组第2个位置的字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(ArrayList_Func->remove(&l,-2,(ArrayListType*)&removed))
    {
        showListAllData(&l,(char*)"移除数组倒数第2个位置的字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(ArrayList_Func->removeFirst(&l,(ArrayListType*)&removed))
    {
        showListAllData(&l,(char*)"移除数组首部元素字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }
    if(ArrayList_Func->removeLast(&l,(ArrayListType*)&removed))
    {
        showListAllData(&l,(char*)"移除数组尾部元素字符:");
        printf("removed data is:%c\n\n",*(char*)removed);
    }

    char e = 'm';
    if (ArrayList_Func->setFirstData(&l,(ArrayListType)&e))
        showListAllData(&l,(char*)"数组头部元素修改为字符'm':");
    char f = 'n';
    if (ArrayList_Func->setLastData(&l,(ArrayListType)&f))
        showListAllData(&l,(char*)"数组尾部元素修改为字符'n':");
    char g = 'o';
    if (ArrayList_Func->setData(&l,2,(ArrayListType)&g))
        showListAllData(&l,(char*)"数组第二个元素修改为字符'o':");
    char h = 'p';
    if (ArrayList_Func->setData(&l,-3,(ArrayListType)&h))
        showListAllData(&l,(char*)"数组倒数第三个元素修改为字符'p':");

    ArrayListType data;
    if(ArrayList_Func->getFirstData(&l,(ArrayListType*)&data))
        printf("数组首部元素 data:%c\n\n",*(char*)data);
    if(ArrayList_Func->getLastData(&l,(ArrayListType*)&data))
        printf("数组尾部元素 data:%c\n\n",*(char*)data);
    if(ArrayList_Func->getData(&l,3,(ArrayListType*)&data))
        printf("数组第3个元素 data:%c\n\n",*(char*)data);
    if(ArrayList_Func->getData(&l,-2,(ArrayListType*)&data))
        printf("数组倒数第2个元素 data:%c\n\n",*(char*)data);

    int size;
    size= ArrayList_Func->getSize(&l);
    printf("数组大小为:%d\n\n",size);
    
    int pos;
    char k = 'd';
    if (ArrayList_Func->locateData(&l,(ArrayListType)&k, &pos))
        printf("%c:在数组第%d个位置\n",k,pos);
    else
    {
        printf("%c:不在数组内\n",k);
    }
    
    ArrayList_Func->clear(&l);
    showListAllData(&l,(char*)"清空后的数组:");
    size= ArrayList_Func->getSize(&l);
    printf("清空后的数组大小为:%d\n\n",size);
    // ArrayList_Func->destory(&l);
    system("pause");
}