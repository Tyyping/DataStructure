#include "LinearList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LIST_INIT_LENGTH  20
#define LIST_INCREASE     10

typedef struct 
{
	Stu * stu;
	int length;
	int listSize;
}SqList;


/*用动态内存分配的方式初始化一个线性顺序表*/
Status InitList(SqList *pL)
{
    pL->stu = (Stu *)malloc(LIST_INIT_LENGTH * sizeof(Stu));

    if(!pL->stu)
        return OVERFLOW;
    pL->length = 0;
    pL->listSize = LIST_INIT_LENGTH;
    return OK;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：清空一个线性表，释放分配的内存资源，同时将元素长度和实际分配的内存单元数清零 */
Status ClearList(SqList *pL)
{
    free(pL->stu);
    pL->length = 0;
    pL->listSize = 0;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：判断顺序表是否为空表 */
bool ListEmpty(SqList L)
{
    if(L.length == 0)
        return true;
    else
        return false;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：获取顺序表的长度 */
int ListLength(SqList L)
{
    return L.length;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：在指定位置插入一个元素， pos的范围[0,pL->length] */
Status ListInsert(SqList *pL, int pos, Stu stu)
{
    //如果给定pos不在当前顺序表范围内，返回ERROR
    if(pos < 0 || pos > pL->length)
        return ERROR;
    //如果当前存储空间已满，需增加分配
    if(pL->length >= pL->listSize)
    {
        Stu *newBase = (Stu *)realloc(pL->stu, (pL->listSize + LIST_INCREASE) * sizeof(Stu));
        if(!newBase)
            return OVERFLOW;
        pL->stu = newBase;
        pL->listSize += LIST_INCREASE;
    }
    //插入点及其后面的数据，都要逐位向后移一位
    Stu *p = &pL->stu[pos];
    for(Stu *q = &pL->stu[pL->length - 1]; q >= p; q--)
    {
        *(q + 1) = *q;
    }
    //插入点插入
    *p = stu;

    ++pL->length;
    return OK;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：删除指定位置上的元素，并将删除的元素存在stu中 */
Status ListDelete(SqList *pL, int pos, Stu *pStu)
{
    if(pos < 0 || pos >= pL->length)
        return ERROR;
    //删除点数据删除
    *pStu = pL->stu[pos];
    //删除点后面的数据，逐位向前移一位
    for(Stu * p = &pL->stu[pos]; p <= &pL->stu[pL->length - 2]; p++)
    {
        *p = *(p + 1);
    }

    --pL->length;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：获取指定位置上的元素 */
Status ListGetElem(SqList L, int pos, Stu *pStu)
{
    //若给定位置不在顺序表的合法范围内，返回ERROR
    if(pos < 0 || pos > L.length - 1)
        return ERROR;
    //将给定位置上的元素内容赋给*pStu
    *pStu = L.stu[pos];
    return OK;
}


/*比较x,y的值，相等时返回TRUE，不等返回FALSE*/
static bool isEquals(Stu x, Stu y)
{
    if(x.age == y.age)
    {
        if(strcmp((const char *)x.name, (const char *)y.name) == 0)
        {
            return true;
        }
    }
    return false;
}
/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：在顺序表中查找给定元素第一次出现的位置并返回，若顺序表中不存在该元素，则返回-1 */
int ListLocate(SqList *pL, Stu stu)
{
    //若顺序表长度小于等于0，表示顺序表内无任何元素
    if(pL->length <= 0)
        return -1;
    //从起始位置到终止位置，依次比较元素，当有相同元素出现时，返回元素位置，否则，返回-1
    Stu *p = pL->stu;
    for(int cnt = 0; cnt < pL->length; cnt++)
    {
        if(isEquals(stu, p[cnt]))
            return cnt;
    }
    return -1;
}


static Status visit(Stu stu)
{
    printf("name=%s\tage=%d\r\n", stu.name, stu.age);
    return OK;
}
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
    for(int len = 0; len < L.length; len++)
    {
        visit(L.stu[len]);
    }
    printf("Traverse over!\r\n\r\n");
    return OK;
}


/* 初始条件：顺序线性表*pL和La已存在 */
/* 操作结果：将La中的元素，依次添加到*pL表的尾部，实现两个顺序线性表的组合 */
Status ListMerge(SqList *pL, SqList La)
{
    for(int cnt = 0; cnt < La.length; cnt++)
    {
        Stu tmp = La.stu[cnt];
        ListInsert(pL, pL->length, tmp);
    }
    return OK;
}

int main()
{
    SqList List;
    InitList(&List);
    
    Stu stu;
    stu.age = 21; stu.name = "abc";
    ListInsert(&List, 0, stu);
    stu.age = 20; stu.name = "def";
    ListInsert(&List, 0, stu);
    stu.age = 23; stu.name = "ghi";
    ListInsert(&List, 0, stu);
    stu.age = 22; stu.name = "jkl";
    ListInsert(&List, 0, stu);
    stu.age = 21; stu.name = "mn ";
    ListInsert(&List, 0, stu);
    stu.age = 19; stu.name = "opq";
    ListInsert(&List, 0, stu);
    stu.age = 20; stu.name = "rst";
    ListInsert(&List, 0, stu);
    stu.age = 21; stu.name = "uvw";
    ListInsert(&List, 0, stu);
    stu.age = 22; stu.name = "xyz";
    ListInsert(&List, 0, stu);

    SqList la;
    InitList(&la);

    stu.age = 23; stu.name = "Lon";
    ListInsert(&la, 0, stu);
    stu.age = 22; stu.name = "Wen";
    ListInsert(&la, 0, stu);
    stu.age = 21; stu.name = "Zhang";
    ListInsert(&la, 0, stu);

    int pos;
    printf("Input a integer number to get the position of a certern element: ");
    scanf("%d", &pos);
    if(ListGetElem(List, pos, &stu) == OK)
        printf("\r\nElement: name=%s\tage=%d\r\n\r\n", stu.name, stu.age);
    else
        printf("\r\nEnter number illigal\r\n\r\n");
    
    ListMerge(&List, la);

    if(ListEmpty(List) == false)
    {
        ListTraverse(List);
    }else
    {
        printf("List is Empty!\r\n");
    }
    

    for(int cnt = 0, len = List.length; cnt < len; cnt++)
    {
        ListDelete(&List, 0, &stu);
        //printf("Delete: name=%s\tage=%d\r\nthe number of remain elements is %d\r\n\r\n", stu.name, stu.age, List.length);
    }

    if(ListEmpty(List) == false)
    {
        ListTraverse(List);
    }else
    {
        printf("List is Empty!\r\n");
    }

    getchar();getchar();
    return 0;
	
}