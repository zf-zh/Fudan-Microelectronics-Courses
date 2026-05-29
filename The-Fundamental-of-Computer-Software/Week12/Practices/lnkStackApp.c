/* File: lnkStackApp.c
    【习题4-47】链接栈应用
    【例题4-11】空栈
    【例题4-9】铁路车厢编组 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NODE struct node
#define M 10
#define MAX M-1
#define MIN 0
NODE
{
    char key;
    NODE *next;
};
NODE *Free=NULL;                 /* 空链表栈的栈顶指针 */
NODE *Top=NULL;
error(char *string)                /* 出错处理函数 */
{
    printf("%s\n", string);
    exit(1);
}
void inputOp(char *op, int n)
{
    int i=0, ch;
    while(i < 2*n)
    {
        if( (ch=getchar()) == EOF)
            break;
        if(ch == 'P' || ch == 'O')
            op[i++] = ch;
    }
    if(i != 2*n || op[0] != 'P' || op[2*n-1] != 'O')
        error("operator error!");
}
void inputData(char *a, int *n)
{
    int i=0;
    char str[10];
    scanf("%d", n);
    for(i=0; i<*n; i++)
    {
        scanf("%s", str);
        a[i] = str[0];
    }
}
void pushFree(NODE *node)         /* 空链表栈的进栈函数 */
{
    node->next = Free;
    Free = node;
}
NODE *popFree()                    /* 空链表栈的出栈函数 */
{
    NODE *node;
    int i;
    if(Free == NULL)
    {
    
        Free = (NODE *)malloc(M * sizeof(NODE));    /* 动态申请M个结点 */
        if(Free == NULL)                             /* 上溢出 */
            error("overflow!");
        node = Free;
        for(i=MIN; i<MAX; node++, i++)
            node->next = node + 1;                 /* 将M个结点构成链表 */
        node->next = NULL;
    }
    node = Free;                                 /* 空链表栈顶结点出栈 */
    Free = Free->next;
    return(node);
}
void push(char key)
{
    NODE *node;
    /* complete the follwing code */
    node = popFree();
    node->key = key;
    node->next = Top;
    Top = node;
}
char pop()
{
    NODE *node;
    char key;
    /* complete the follwing code */
    if (Top == NULL) {
        error("stack empty!");
    }
    key = Top->key;
    node = Top;
    Top = Top->next;
    pushFree(node);
    return(key);
}
void stackApp(char *a, char *b, char *op, int n)
{
    int ia=0, ib=0, iop;
    
    for(iop=0; iop<2*n; iop++)
    {
        if(op[iop] == 'P')
            push(a[ia++]);
        else if(op[iop] == 'O')
            b[ib++] = pop();
    }
    if(ia != n || ib != n)
        error("data error!");
}
void main()
{
    int n, i;
    char a[30], b[30], op[50];
    printf("输入数据和操作序列\n");
    inputData(a, &n);
    inputOp(op, n);
    printf("栈操作\n");
    stackApp(a, b, op, n);
    for(i=0; i<n; i++)
        printf("%c ", b[i]);
    printf("\n");
}
/*
输入数据和操作序列
7
B A L E M D F
PPOPOOPPOPPOOO
栈操作
A L B M F D E

6
6 1 9 2 5 3
P P O P O O P P O O P O
栈操作
1 9 6 5 2 3

7
B A L E M D F
PPOPOOPPOPP
^Z
operator error!

6
1 9 2 5 3
P P O P O O P P O O P O
^Z
operator error!

5
O R C I M
P P O P O P P O O O
栈操作
R C M I O

7
B A L E M D F
PPPPOPPOOOPOOO
栈操作
E D M L F A B

7
F D M I C R 0
PPOPOOPPOPPOOO
栈操作
D M F C 0 R I

7 F D M I C R 0
PPPPOPPOOOPOOO
栈操作
I R C M 0 D F

7
F D M E L A B
PPOPOOPPOPPOOO
栈操作
D M F L B A E

7
F D M E L A B
PPPPOPPOOOPOOO
栈操作
E A L M B D F
*/