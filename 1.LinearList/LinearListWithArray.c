#include "LinearList.h"
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

typedef struct 
{
    Stu stu[MAX_SIZE];
    int length;
}List;


/* 初始化一个线性顺序表 */
Status InitList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：将L重置为空表 */
Status ClearList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：若L为空表，则返回true，否则返回true */
bool ListEmpty(List L)
{
    if(L.length == 0)
        return true;
    else
        return false;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中数据元素个数 */
int ListLength(List L)
{
    return L.length;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：在*pL表中的pos位置插入一个元素， pos的范围是[0, pL->length]*/
Status ListInsert(List *pL, int pos, Stu stu)
{
    /* 顺序线性表已满 */
    if(pL->length >= MAX_SIZE)
        return ERROR;
    /* 插入位置有误 */
    if(pos < 0 || pos > pL->length)
        return ERROR;
    /* pos位置之后的元素，依次向后移一位 */
    for(int p = pL->length - 1; p >= pos; --p)
    {
        pL->stu[p + 1] = pL->stu[p];
    }
    pL->stu[pos] = stu;      //插入点赋值，结构体可以整体赋值
    ++pL->length;            //长度+1
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：删除*pL表中pos位置上的元素， pos的范围是[0, pL->length-1]*/
Status ListDelete(List *pL, int pos, Stu *pStu)
{
    /* 删除位置有误 */
    if(pos < 0 || pos > pL->length - 1)
        return ERROR;
    
    *pStu = pL->stu[pos];    //提取删除点元素
    /* pos位置之后的元素，依次向前移一位 */
    for(int p = pos; p <= pL->length - 2; ++p)
    {
        pL->stu[p] = pL->stu[p + 1];
    }
    --pL->length;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：将L表中pos位置上的元素值赋给*pStu， pos的范围是[0, pL->length-1]*/
Status ListGetElem(List L, int pos, Stu *pStu)
{
    /* 元素位置范围超出 */
    if(pos < 0 || pos > L.length - 1)
        return ERROR;
    *pStu = L.stu[pos];
    return OK;
}


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
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：在顺序线性表L中查找指定内容的元素，若表中存在该元素，则返回第一次出现的位置，若不存在，则返回-1 */
int ListLocate(List L, Stu stu)
{
    for(int cnt = 0; cnt < L.length; cnt++)
    {
        if(isEquals(stu, L.stu[cnt]))
        {
            return cnt;
        }
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
Status ListTraverse(List L)
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
Status ListMerge(List *pL, List La)
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
    List al;
    InitList(&al);
    
    Stu stu;
    stu.age = 21; stu.name = "abc";
    ListInsert(&al, 0, stu);
    stu.age = 20; stu.name = "def";
    ListInsert(&al, 0, stu);
    stu.age = 23; stu.name = "ghi";
    ListInsert(&al, 0, stu);
    stu.age = 22; stu.name = "jkl";
    ListInsert(&al, 0, stu);
    stu.age = 21; stu.name = "mn ";
    ListInsert(&al, 0, stu);
    stu.age = 19; stu.name = "opq";
    ListInsert(&al, 0, stu);
    stu.age = 20; stu.name = "rst";
    ListInsert(&al, 0, stu);
    stu.age = 21; stu.name = "uvw";
    ListInsert(&al, 0, stu);
    stu.age = 22; stu.name = "xyz";
    ListInsert(&al, 0, stu);

    List la;
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
    if(ListGetElem(al, pos, &stu) == OK)
        printf("\r\nElement: name=%s\tage=%d\r\n\r\n", stu.name, stu.age);
    else
        printf("\r\nEnter number illigal\r\n\r\n");
    
    ListMerge(&al, la);

    if(ListEmpty(al) == false)
    {
        ListTraverse(al);
    }else
    {
        printf("List is Empty!\r\n");
    }
    

    for(int cnt = 0, len = al.length; cnt < len; cnt++)
    {
        ListDelete(&al, 0, &stu);
        //printf("Delete: name=%s\tage=%d\r\nthe number of remain elements is %d\r\n\r\n", stu.name, stu.age, al.length);
    }

    if(ListEmpty(al) == false)
    {
        ListTraverse(al);
    }else
    {
        printf("List is Empty!\r\n");
    }

    getchar();getchar();
    return 0;
}
