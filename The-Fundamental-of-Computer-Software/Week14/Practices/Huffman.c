/* File: Huffman.c
    【习题4-51】哈夫曼编码(Huffman码)生成算法    */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define HNODE struct hnode
#define NODE struct node
HNODE
{
    NODE *node;
    HNODE *next;
};
NODE
{
    char key;
    int weigh;
    char code[10];
    NODE *left, *right;
};
HNODE *Head=NULL;
NODE *Root=NULL;
int sumWPL=0;
void prt()
{
    HNODE *hnode = Head->next;
    for(hnode=Head->next; hnode ; hnode = hnode->next)
        printf("%c %d ", hnode->node->key, hnode->node->weigh);
    printf("\n");
}
void insertHnode(HNODE *hnode)            /* 按频度升序插入结点的函数    */
{
    HNODE *prev = Head;
    while(prev->next && hnode->node->weigh > prev->next->node->weigh)
        prev = prev->next;
    hnode->next = prev->next;             /* 插入结点                    */
    prev->next = hnode;
}
HNODE *getHnode()                        /* 从H链表中摘取结点的函数    */
{
    HNODE *hnode;
    hnode = Head->next;
    Head->next = hnode->next;
    return(hnode);
}
void inputNode(FILE *fp)
{
    char key[10];
    int weigh;
    HNODE *hnode;
    NODE *node;
    while(fscanf(fp, "%s%d", key, &weigh) == 2)
    {
        if((node = (NODE *)malloc(sizeof(NODE))) == NULL)
            exit(0);
        node->key = key[0];
        node->weigh = weigh;
        node->code[0] = '\0';
        node->left = node->right = NULL;
        if((hnode = (HNODE *)malloc(sizeof(HNODE))) == NULL)
            exit(0);
        hnode->node = node;
        insertHnode(hnode);
    }
}
void inputTree()
{
    FILE *fp;
    char filename[60];
    printf("输入结点文件: ");
    scanf("%s", filename);
    if((fp = fopen(filename, "r")) == NULL)
        exit(0);
    if((Head = (HNODE *)malloc(sizeof(HNODE))) == NULL)
        exit(0);
    Head->next = NULL;
    inputNode(fp);
}
void MakeTree()                            /* 生成哈夫曼树的函数        */
{
    HNODE *hnode1, *hnode2;
    NODE *node;
    while(Head->next->next)
    {
        if((node = (NODE *)malloc(sizeof(NODE))) == NULL)
            exit(0);                     /* 新增一个根结点            */
        /* complete the following code            */
        hnode1 = getHnode();
        hnode2 = getHnode();
        node->left = hnode1->node;
        node->right = hnode2->node;
        node->key = '#';
        node->code[0] = '\0';
        node->weigh = node->left->weigh + node->right->weigh;
        hnode1->node = node;
        insertHnode(hnode1);
        free(hnode2);
        /* End */
        prt();
    }
}
void MakeCode(NODE *node)                 /* 生成哈夫曼编码的函数        */
{
    int wpl;
    /* complete the following code            */
    if (node == NULL) {
        return;
    }
    if (!node->left && !node->right) {
        wpl = strlen(node->code) * node->weigh;
        sumWPL += wpl;
        printf("%c %d [%s] %d\n", node->key, node->weigh, node->code, wpl);
    }
    if (node->left) {
        strcpy(node->left->code, node->code);
        strcat(node->left->code, "0");
        MakeCode(node->left);
    }
    if (node->right) {
        strcpy(node->right->code, node->code);
        strcat(node->right->code, "1");
        MakeCode(node->right);
    }
    /* End */
}
void main()
{
    inputTree();
    prt();
    printf("MakeTree\n");
    MakeTree();
    Root = Head->next->node;
    printf("MakeCode\n");
    MakeCode(Root);
    printf("wpl = %d\n", sumWPL);
    system("pause");
}
/*
node1.txt
A 2 D 4 G 5 O 8
MakeTree
G 5 # 6 O 8
O 8 # 11
# 19
MakeCode
O 8 [0] 8
G 5 [10] 10
A 2 [110] 6
D 4 [111] 12
wpl = 36

node2.txt
V 1 G 2 L 5 R 6 N 7 E 10
MakeTree
# 3 L 5 R 6 N 7 E 10
R 6 N 7 # 8 E 10
# 8 E 10 # 13
# 13 # 18
# 31
MakeCode
R 6 [00] 12
N 7 [01] 14
V 1 [1000] 4
G 2 [1001] 8
L 5 [101] 15
E 10 [11] 20
wpl = 73

node3.txt
B 2 Y 3 D 4 A 8 H 10 O 11
MakeTree
D 4 # 5 A 8 H 10 O 11
A 8 # 9 H 10 O 11
H 10 O 11 # 17
# 17 # 21
# 38
MakeCode
A 8 [00] 16
D 4 [010] 12
B 2 [0110] 8
Y 3 [0111] 12
H 10 [10] 20
O 11 [11] 22
wpl = 90

node4.txt
P 2 F 3 C 4 S 7 O 8 E 10
MakeTree
C 4 # 5 S 7 O 8 E 10
S 7 O 8 # 9 E 10
# 9 E 10 # 15
# 15 # 19
# 34
MakeCode
S 7 [00] 14
O 8 [01] 16
C 4 [100] 12
P 2 [1010] 8
F 3 [1011] 12
E 10 [11] 20
wpl = 82

node5.txt
P 2 M 3 U 4 H 6 N 7 T 8
MakeTree
U 4 # 5 H 6 N 7 T 8
H 6 N 7 T 8 # 9
T 8 # 9 # 13
# 13 # 17
# 30
MakeCode
H 6 [00] 12
N 7 [01] 14
T 8 [10] 16
U 4 [110] 12
P 2 [1110] 8
M 3 [1111] 12
wpl = 74

node6.txt
P 2 M 3 U 6 H 12 N 13 T 14
MakeTree
# 5 U 6 H 12 N 13 T 14
# 11 H 12 N 13 T 14
N 13 T 14 # 23
# 23 # 27
# 50
MakeCode
P 2 [0000] 8
M 3 [0001] 12
U 6 [001] 18
H 12 [01] 24
N 13 [10] 26
T 14 [11] 28
wpl = 116
*/