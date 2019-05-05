#include "LinearList.h"
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

typedef struct 
{
    Student stu[MAX_SIZE];
    int length;
}List;


/* 初始化一个线性顺序表 */
Status InitList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：清空一个线性表，将顺序线性表长度清零 */
Status ClearList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：判断顺序表是否为空表 */
bool ListEmpty(List L)
{
    if(L.length == 0)
        return true;
    else
        return false;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：获取顺序表的长度 */
int ListLength(List L)
{
    return L.length;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：在指定位置插入一个元素， pos的范围[0,pL->length] */
Status ListInsert(List *pL, int pos, Student stu)
{
    //如果线性表数组已满，则无法插入新元素，返回ERROR
    if(pL->length >= MAX_SIZE)
        return ERROR;
    //如果给定pos不在当前顺序表范围内，返回ERROR
    if(pos < 0 || pos > pL->length)
        return ERROR;
    //插入点及其后面的数据，都要逐位向后移一位
    for(int p = pL->length - 1; p >= pos; --p)
    {
        pL->stu[p + 1] = pL->stu[p];
    }
    pL->stu[pos] = stu;
    ++pL->length;
    return OK;
}


/* 初始条件：顺序线性表*pL已存在 */
/* 操作结果：删除指定位置上的元素，并将删除的元素存在stu中 */
Status ListDelete(List *pL, int pos, Student *pStu)
{
    if(pos < 0 || pos > pL->length - 1)
        return ERROR;
    //删除点数据记录
    *pStu = pL->stu[pos];
    //删除点后面的数据，逐位向前移一位
    for(int p = pos; p <= pL->length - 2; ++p)
    {
        pL->stu[p] = pL->stu[p + 1];
    }
    --pL->length;
    return OK;
}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：获取指定位置上的元素 */
Status ListGetElem(List L, int pos, Student *pStu)
{
    //若给定位置不在顺序表的合法范围内，返回ERROR
    if(pos < 0 || pos > L.length - 1)
        return ERROR;
    //将给定位置上的元素内容赋给*pStu
    *pStu = L.stu[pos];
    return OK;
}


/*比较x,y的值，相等时返回TRUE，不等返回FALSE*/
static bool isEquals(Student x, Student y)
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
int ListLocate(List L, Student stu)
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


static Status visit(Student stu)
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
        Student tmp = La.stu[cnt];
        ListInsert(pL, pL->length, tmp);
    }
    return OK;
}

int main()
{
    List al;
    InitList(&al);
    
    Student stu;
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
