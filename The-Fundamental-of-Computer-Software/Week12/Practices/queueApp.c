/* File: queueApp.c
    【习题4-48】环形队列：家谱图
    相关文件：queueSub.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define F struct family
F                        /* 家族(family)信息 */
{
    int n;                /* 族人编号(number) */
    int g;                /* 辈分(generation) */
    int p;                /* 父母编号(parent) */
    F *next;
};
F *Top;                    /* 族人链表 */
F *Clan;                /* 家谱链表 */
void error(char *);
void enCirQueue(F *);
F *deCirQueue(void);

void input(void)            /* 初始输入信息的函数 */
{
    int    n, g, p;
    F *node;
    FILE *fp;
    char filename[60];
    printf("输入哪个文件: ");
    scanf("%s", filename);
    if((fp = fopen(filename, "r")) == NULL)
        error("cannot open file");
    /* 设置族人链表哨兵 */
    Top = (F *)malloc(sizeof(F));
    if(Top == NULL)
        error("no space");
    Top->next = NULL;
    /* 设置家谱链表哨兵 */
    Clan = (F *)malloc(sizeof(F));
    if(Clan == NULL)
        error("no space");
    Clan->next = NULL;
    /* 输入族人信息，插入族人链表 */
    while(fscanf(fp, "%d%d%d", &n, &g, &p) == 3)
    {
        node = (F *)malloc(sizeof(F));
        if(node == NULL)
            error("no space");
        node->n = n;
        node->g = g;
        node->p = p;
        node->next = Top->next;
        Top->next = node;
    }
}
void prt(F *head)            /* 打印链表的函数 */
{
    F *node;
    for(node=head->next; node; node=node->next)
    printf("n=%-4dg=%-4dp=%-4d\n",
            node->n, node->g, node->p);
}
void prtClan(F *clan)        /* 打印家谱图的函数 */
{
    int i;
    F *node;
    for(node=Clan; node->next; node=node->next)
    {
        if(node->next && node->g >= node->next->g)
        {
            for(i=1; i<node->next->g; i++)
                printf("________  ");
        }
        printf("%2d,%2d,%2d  ", 
            node->next->n, node->next->g, node->next->p);
        if(node->next->next == NULL || 
            node->next->g >= node->next->next->g)
            printf("\n");
    }
}
void GetClan(void)        /* 获取家谱链表函数 */
{
    int h=1, g=1;
    F *child, *node, *prev;
    /* 在族人链表中删除先祖，进队 */
    node = Top->next;
    Top->next = node->next;
    enCirQueue(node);
    while((node = deCirQueue()) != NULL)    /* 只要队非空 */
    {
        /* 从族人链表中删除node的所有子女，逐个进队 */
        for(prev=Top; prev->next; )
        {
            /* complete the follwing code */
            if (prev->next->p == node->n) {
                child = prev->next;
                prev->next = child->next;
                enCirQueue(child);
            }
            else {
                prev = prev->next;
            }
            /* -------------------------- */
        }
        /* 将node插入家谱链表 */
        for(prev=Clan; prev->next; prev=prev->next)
            if(prev->next->n == node->p)
                break;
        /* complete the follwing code */
        if (prev->next == NULL) {
            node->next = prev->next;
            prev->next = node;
        }
        else {
            node->next = prev->next->next;
            prev->next->next = node;
        }
        /* -------------------------- */
    }
}
void main()
{
    input();                 /* 输入族人信息 */
    printf("族人链表：\n");    /* if debug */
    prt(Top);                /* if debug */
    GetClan();                /* 获取家谱链表 */
    printf("家谱链表：\n");    /* if debug */
    prt(Clan);                /* if debug */
    printf("家谱图：\n");
    prtClan(Clan);            /* 打印家谱图 */
    system("pause");
}
/*
输入哪个文件: clan1.txt
家谱图：
14, 1, 0  12, 2,14  11, 3,12
________  ________  13, 3,12
________  16, 2,14
________  20, 2,14  15, 3,20
________  ________  18, 3,20
________  ________  17, 3,20

输入哪个文件: clan2.txt
家谱图：
24, 1, 0  11, 2,24  12, 3,11  19, 4,12  16, 5,19
________  ________  ________  ________  27, 5,19
________  ________  ________  29, 4,12  25, 5,29
________  ________  18, 3,11  37, 4,18  22, 5,37
________  ________  21, 3,11  20, 4,21  13, 5,20
________  ________  ________  31, 4,21
________  ________  35, 3,11
________  28, 2,24  15, 3,28
________  ________  17, 3,28  30, 4,17  14, 5,30
________  ________  ________  33, 4,17
________  ________  39, 3,28  34, 4,39  38, 5,34
________  32, 2,24  26, 3,32  36, 4,26  23, 5,36
*/