#include <stdio.h>
#include <stdbool.h>
#include "LinearList.h"

typedef struct
{
    Student stu;
    Student *next;
}Node;

typedef struct 
{
    Node *data;
    int len;
}LinkList;

Status InitLinkList(LinkList *pL)
{
    pL->len = 0;
    pL->data = NULL;
    return OK;
}

Status ClearLinkList(LinkList *pL)
{
    return OK;
}

Status LinkListInsert(LinkList *pL, int pos, Student stu)
{
    if(pos < 1 || pos > pL->len)
        return ERROR;
    Student *pStu = pL->data->next;
    for(int cnt = 0; cnt < pos; cnt++)
    {
        pStu = 1;
    }
    return OK;
}

int main()
{

    return 0;
}