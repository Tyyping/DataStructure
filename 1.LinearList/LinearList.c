#include "LinearList.h"
#include <stdlib.h>
#include <stdio.h>
#define LIST_INIT_LENGTH  20
#define LIST_INCREASE     10

typedef struct 
{
	Stu * stu;
	int length;
	int listSize;
}SqList;

/*用动态内存分配的方式初始化一个线性顺序表*/
Status ListInit(SqList *L)
{
    L->stu = (Stu *)malloc(LIST_INIT_LENGTH * sizeof(Stu));

    if(!L->stu)
        return OVERFLOW;
    L->length = 0;
    L->listSize = LIST_INIT_LENGTH;
    return OK;
}
/*在指定位置插入一个元素， 0 <= pos <= L.length*/
Status ListInsert(SqList *L, int pos, Stu stu)
{
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
Status ListDelete(SqList *L, int pos, Stu *stu)
{
    if(pos < 0 || pos >= L->length)
        return ERROR;
    //删除点数据删除
    *stu = L->stu[pos];
    //删除点后面的数据，逐位向前移一位
    for(Stu * p = &L->stu[pos]; p <= &L->stu[L->length - 2]; p++)
    {

        *p = *(p + 1);
    }

    --L->length;
    return OK;
}

Status main()
{
	getchar();

    SqList List;
    ListInit(&List);

    Stu stu;
    stu.number = 1;
    stu.name = "wenlon";
    ListInsert(&List, 0, stu);

    stu.number = 2;
    stu.name = "cheung";
    ListInsert(&List, 1, stu);

    stu.number = 3;
    stu.name = "Lon";
    ListInsert(&List, 1, stu);

    printf("%d\n", List.length);

    ListDelete(&List, 0, &stu);
    printf("name=%s, number=%d\n", stu.name, stu.number);
    ListDelete(&List, 0, &stu);
    printf("name=%s, number=%d\n", stu.name, stu.number);
    ListDelete(&List, 0, &stu);
    printf("name=%s, number=%d\n", stu.name, stu.number);
    
	getchar();
    getchar();
	
}