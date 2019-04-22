#ifndef __LINEAR_LIST
#define __LINEAR_LIST

#define OK           1
#define ERROR        0
#define INFEASIBLE  -1
#define OVERFLOW    -2

#define NAME_LENGTH 20
#define MAX_SIZE    20
typedef int Status;
typedef struct
{
    char *name;
    int  age;
}Stu;
#endif