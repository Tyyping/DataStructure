#include "LinearList.h"
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

typedef struct 
{
    Stu stu[MAX_SIZE];
    int length;
}List;


/* ��ʼ��һ������˳��� */
Status InitList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �����������L����Ϊ�ձ� */
Status ClearList(List *pL)
{
    pL->length = 0;
    return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �����������LΪ�ձ��򷵻�true�����򷵻�true */
bool ListEmpty(List L)
{
    if(L.length == 0)
        return true;
    else
        return false;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L������Ԫ�ظ��� */
int ListLength(List L)
{
    return L.length;
}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �����������*pL���е�posλ�ò���һ��Ԫ�أ� pos�ķ�Χ��[0, pL->length]*/
Status ListInsert(List *pL, int pos, Stu stu)
{
    /* ˳�����Ա����� */
    if(pL->length >= MAX_SIZE)
        return ERROR;
    /* ����λ������ */
    if(pos < 0 || pos > pL->length)
        return ERROR;
    /* posλ��֮���Ԫ�أ����������һλ */
    for(int p = pL->length - 1; p >= pos; --p)
    {
        pL->stu[p + 1] = pL->stu[p];
    }
    pL->stu[pos] = stu;      //����㸳ֵ���ṹ��������帳ֵ
    ++pL->length;            //����+1
    return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ���������ɾ��*pL����posλ���ϵ�Ԫ�أ� pos�ķ�Χ��[0, pL->length-1]*/
Status ListDelete(List *pL, int pos, Stu *pStu)
{
    /* ɾ��λ������ */
    if(pos < 0 || pos > pL->length - 1)
        return ERROR;
    
    *pStu = pL->stu[pos];    //��ȡɾ����Ԫ��
    /* posλ��֮���Ԫ�أ�������ǰ��һλ */
    for(int p = pos; p <= pL->length - 2; ++p)
    {
        pL->stu[p] = pL->stu[p + 1];
    }
    --pL->length;
    return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �����������L����posλ���ϵ�Ԫ��ֵ����*pStu�� pos�ķ�Χ��[0, pL->length-1]*/
Status ListGetElem(List L, int pos, Stu *pStu)
{
    /* Ԫ��λ�÷�Χ���� */
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
/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �����������˳�����Ա�L�в���ָ�����ݵ�Ԫ�أ������д��ڸ�Ԫ�أ��򷵻ص�һ�γ��ֵ�λ�ã��������ڣ��򷵻�-1 */
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
/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
Status ListTraverse(List L)
{
    
    for(int len = 0; len < L.length; len++)
    {
        visit(L.stu[len]);
    }
    printf("Traverse over!\r\n\r\n");
    return OK;
}


/* ��ʼ������˳�����Ա�*pL��La�Ѵ��� */
/* �����������La�е�Ԫ�أ�������ӵ�*pL���β����ʵ������˳�����Ա����� */
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
