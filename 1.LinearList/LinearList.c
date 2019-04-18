#include "LinearList.h"
#include <stdlib.h>
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
Status InitList(SqList *L)
{
    L->stu = (Stu *)malloc(LIST_INIT_LENGTH * sizeof(Stu));

    if(!L->stu)
        return OVERFLOW;
    L->length = 0;
    L->listSize = LIST_INIT_LENGTH;
    return OK;
}

/*清空一个线性表，释放分配的内存资源，同时将元素长度和实际分配的内存单元数清零*/
Status ClearList(SqList *L)
{
    //对于空表，不执行任何操作
    if(L->length == 0 && L->stu == NULL)
        return OK;
    
    free(L->stu);
    L->length = 0;
    L->listSize = 0;
    return OK;
}

/*判断顺序表是否为空表*/
Status ListEmpty(SqList *L)
{
    if(L->length == 0)
        return TRUE;
    else
        return FALSE;
}

/*获取顺序表的长度*/
int ListLength(SqList *L)
{
    return L->length;
}

/*在指定位置插入一个元素， 0 <= pos <= L.length*/
Status ListInsert(SqList *L, int pos, Stu stu)
{
    //如果给定pos不在当前顺序表范围内，返回ERROR
    if(pos < 0 || pos > L->length)
        return ERROR;
    //如果当前存储空间已满，需增加分配
    if(L->length >= L->listSize)
    {
        Stu *newBase = (Stu *)realloc(L->stu, (L->listSize + LIST_INCREASE) * sizeof(Stu));
        if(!newBase)
            return OVERFLOW;
        L->stu = newBase;
        L->listSize += LIST_INCREASE;
    }
    //插入点及其后面的数据，都要逐位向后移一位
    Stu *p = &L->stu[pos];
    for(Stu *q = &L->stu[L->length - 1]; q >= p; q--)
    {
        *(q + 1) = *q;
    }
    //插入点插入
    *p = stu;

    ++L->length;
    return OK;
}

/*删除指定位置上的元素，并将删除的元素存在stu中*/
Status ListDelete(SqList *L, int pos, Stu *pStu)
{
    if(pos < 0 || pos >= L->length)
        return ERROR;
    //删除点数据删除
    *pStu = L->stu[pos];
    //删除点后面的数据，逐位向前移一位
    for(Stu * p = &L->stu[pos]; p <= &L->stu[L->length - 2]; p++)
    {
        *p = *(p + 1);
    }

    --L->length;
    return OK;
}

/*获取指定位置上的元素*/
Status ListGetElem(SqList *L, int pos, Stu *pStu)
{
    //若给定位置不在顺序表的合法范围内，返回ERROR
    if(pos < 0 || pos > L->length - 1)
        return ERROR;
    //将给定位置上的元素内容赋给*pStu
    *pStu = L->stu[pos];
    return OK;
}

/*比较x,y的值，相等时返回TRUE，不等返回FALSE*/
static Status isEqual(Stu x, Stu y)
{
    if(x.age == y.age)
    {
        if(strcmp((const char *)x.name, (const char *)y.name) == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
/*在顺序表中查找给定元素第一次出现的位置并返回，若顺序表中不存在该元素，则返回-1*/
int ListLocate(SqList *L, Stu stu)
{
    //若顺序表长度小于等于0，表示顺序表内无任何元素
    if(L->length <= 0)
        return -1;
    //从起始位置到终止位置，依次比较元素，当有相同元素出现时，返回元素位置，否则，返回-1
    Stu *p = L->stu;
    for(int cnt = 0; cnt < L->length; cnt++)
    {
        if(isEqual(stu, p[cnt]))
            return cnt;
    }
    return -1;
}

Status main()
{
    SqList List;
    InitList(&List);

    Stu stu;
    stu.age = 1; stu.name = "abc";
    ListInsert(&List, 0, stu);

    stu.age = 2; stu.name = "def";
    ListInsert(&List, 1, stu);

    stu.age = 3; stu.name = "ghi";
    ListInsert(&List, 2, stu);

    stu.age = 4; stu.name = "jkl";
    ListInsert(&List, 3, stu);

    stu.age = 5; stu.name = "mn";
    ListInsert(&List, 4, stu);

    stu.age = 6; stu.name = "opq";
    ListInsert(&List, 5, stu);

    stu.age = 7; stu.name = "rst";
    ListInsert(&List, 6, stu);

    stu.age = 8; stu.name = "uvw";
    ListInsert(&List, 7, stu);

    stu.age = 9; stu.name = "xyz";
    ListInsert(&List, 8, stu);

    SqList List1;
    InitList(&List1);

    stu.age = 7; stu.name = "rst";
    ListInsert(&List1, 0, stu);

    stu.age = 8; stu.name = "uvwzzz";
    ListInsert(&List1, 0, stu);

    stu.age = 9; stu.name = "xyzw";
    ListInsert(&List1, 0, stu);
    
    ListUnion(&List1, &List);

    printf("the length of List is %d\r\n", ListLength(&List));

    if(ListEmpty(&List) == TRUE)
        printf("List is Empty!\r\n");

    for(int cnt = 0, len = List.length; cnt < len; cnt++)
    {
        ListDelete(&List, 0, &stu);
        printf("name=%s, age=%d\r\nthe number of remain elements is %d\r\n", stu.name, stu.age, ListLength(&List));
    }

    
    
    if(ListEmpty(&List) == TRUE)
        printf("List is Empty!\r\n");

    ClearList(&List);

	getchar();
	
}