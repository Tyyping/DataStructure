#include "LinearList.h"
#include <stdio.h>
typedef struct 
{
    Stu stu[MAX_SIZE];
    int length;
}AList;

/*初始化一个线性顺序表*/
Status InitAList(AList *L)
{
    L->length = 0;
    return OK;
}

/*在指定位置插入一个元素， 0 <= pos <= L.length*/
Status AListInsert(AList *L, int pos, Stu stu)
{
    /* 顺序线性表已满 */
    if(L->length >= MAX_SIZE)
        return ERROR;
    /* 插入位置有误 */
    if(pos < 0 || pos > L->length)
        return ERROR;
    /* pos位置之后的元素，依次向后移一位 */
    for(int p = L->length - 1; p >= pos; --p)
    {
        L->stu[p + 1] = L->stu[p];
    }
    L->stu[pos] = stu;      //插入点赋值，结构体可以整体赋值
    ++L->length;            //长度+1
    return OK;
}

Status AListDelete(AList *L, int pos, Stu *pStu)
{
    /* 删除位置有误 */
    if(pos < 0 || pos > L->length - 1)
        return ERROR;
    
    *pStu = L->stu[pos];    //提取删除点元素
    /* pos位置之后的元素，依次向前移一位 */
    for(int p = pos; p <= L->length - 2; ++p)
    {
        L->stu[p] = L->stu[p + 1];
    }
    --L->length;
    return OK;
}
int main()
{
    AList al;
    InitAList(&al);
    
    Stu stu;
    stu.age = 1; stu.name = "abc";
    AListInsert(&al, 0, stu);
    stu.age = 2; stu.name = "def";
    AListInsert(&al, 0, stu);
    stu.age = 3; stu.name = "ghi";
    AListInsert(&al, 0, stu);
    stu.age = 4; stu.name = "jkl";
    AListInsert(&al, 0, stu);
    stu.age = 5; stu.name = "mn ";
    AListInsert(&al, 0, stu);
    stu.age = 6; stu.name = "opq";
    AListInsert(&al, 0, stu);
    stu.age = 7; stu.name = "rst";
    AListInsert(&al, 0, stu);
    stu.age = 8; stu.name = "uvw";
    AListInsert(&al, 0, stu);
    stu.age = 9; stu.name = "xyz";
    AListInsert(&al, 0, stu);

    for(int cnt = 0, len = al.length; cnt < len; cnt++)
    {
        AListDelete(&al, 0, &stu);
        printf("name=%s\tage=%d\r\nthe number of remain elements is %d\r\n", stu.name, stu.age, al.length);
    }

    getchar();
    return 0;
}
