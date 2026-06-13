/* File: B2T.c
    【习题4-50】二次树转换为三叉树    */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define BINODE struct binode
#define TRINODE struct trinode
#define M     80
BINODE
{
    char key;
    BINODE *left, *right;
};
TRINODE
{
    char key;
    TRINODE *sub1, *sub2, *sub3;
};
    
BINODE    *RootB=NULL;    /* 二叉树的根结点指针        */
TRINODE    *RootT=NULL;    /* 三次树的根结点指针        */
char String[M];    /* 输入字符串    */
int  Ptr=0;        /* 字符数组指针 */
void error(char *string)
{
    printf("%s\n", string);
    exit(0);
    system("pause");
}
/* 递归方法前序遍历三次树        */
void preOrderT(TRINODE *node)
{
    if(!node)
        return;
    printf("%c ", node->key); 
    preOrderT(node->sub1);
    preOrderT(node->sub2);
    preOrderT(node->sub3);
}
/* 递归方法后序遍历三次树        */
void postOrderT(TRINODE *node)
{
    if(!node)
        return;
    postOrderT(node->sub1);
    postOrderT(node->sub2);
    postOrderT(node->sub3);
    printf("%c ", node->key); 
}
void preOrder(BINODE *node)
{
    if(!node)
        return;
    printf("%c ", node->key); 
    preOrder(node->left);
    preOrder(node->right);
}
void symOrder(BINODE *node)
{
    if(!node)
        return;
    symOrder(node->left);
    printf("%c ", node->key); 
    symOrder(node->right);
}
void postOrder(BINODE *node)
{
    if(!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    printf("%c ", node->key); 
}
void input(void)                /* 输入树的括号表示    */
{
    int i=0, c;  
    printf("请输入括号表示的二叉树"); 
    printf("(以控制符^Z+换行符为结束):\n"); 
    while( (c=getchar()) != EOF )
        if(!isspace(c))            /* 删除空字符        */
            String[i++] = c;
    String[i] = '\0';
/*    printf("输入的二叉树括号表示: \n%s\n", String); 
*/
}
int GetKey(char *key)            /* 获取结点值的函数    */
{
    int i = 0;
    if(!isalnum(String[Ptr]))
        return(0);                    /* 取值失败        */
    while(isalnum(String[Ptr]))        /* 获取数据        */
        *key = String[Ptr++];
    return(1);                         /* 取值成功        */
}
int GetSymbol(char symbol)     /* 获取指定符号的函数    */
{
    if(String[Ptr] != symbol)
        return(0);                    /* 取符号失败    */
    Ptr++;
    return(1);                         /* 取符号成功    */
}
BINODE *newNode(char key)     /* 生成结点空间的函数    */
{
    BINODE *node;
    node = (BINODE *)(malloc(sizeof(BINODE)));
    if(node == NULL)
        error("no space!"); 
    node->left = node->right = NULL; /* 左右子初始赋空    */
    node->key = key;                 /* 结点赋值        */
    return(node);
}
void MakeNode(BINODE *root)     /* 生成子树的函数        */
{
    char key;
    if(!GetSymbol('('))                    /* 1. 获取左括号'('    */
        return;
    if(GetKey(&key))                    /* 2. 获取左子数据    */
    {  
        root->left = newNode(key);         /* 生成左子空间        */
        MakeNode(root->left);            /* 递归生成左子树    */
    }
    if(!GetSymbol(','))                    /* 3. 获取逗号','    */
        error("missing , !"); 
    if(GetKey(&key))                    /* 4. 获取右子数据    */
    {  
        root->right = newNode(key);     /* 生成右子空间        */
        MakeNode(root->right);             /* 递归生成右子树    */
    }
    if(!GetSymbol(')'))                    /* 5. 获取又括号')'    */
        error("missing ) !"); 
    if(root->right == NULL && root->left == NULL)
        error("no node !");             /* 无左右子，出错    */ 
}
void MakeBitree()                        /* 生成二叉树的函数    */
{
    char key;
    if(GetKey(&key))                    /* 获取根结点数据    */
    {    
        RootB = newNode(key);             /* 生成根结点        */
        MakeNode(RootB);                 /* 调用生成子树函数    */
    }
    else
        error("Empty tree!"); 
}
void B2T(BINODE * bi_node, TRINODE *tri_node)
{
    if(tri_node == NULL || bi_node == NULL)
        error ("empty tree");
    tri_node->key = bi_node->key;
    /* complete the following code            */
    tri_node->sub1 = tri_node->sub2 = tri_node->sub3 = NULL;
    if (bi_node->left) {
        tri_node->sub1 = (TRINODE *)malloc(sizeof(TRINODE));
        if (tri_node->sub1 == NULL) {
            error("no space");
        }
        B2T(bi_node->left, tri_node->sub1);
        if (bi_node->left->right) {
            tri_node->sub2 = (TRINODE *)malloc(sizeof(TRINODE));
            if (tri_node->sub2 == NULL) {
                error("no space");
            }
            B2T(bi_node->left->right, tri_node->sub2);
            if (bi_node->left->right->right) {
                tri_node->sub3 = (TRINODE *)malloc(sizeof(TRINODE));
                if (tri_node->sub3 == NULL) {
                    error("no space");
                }
                B2T(bi_node->left->right->right, tri_node->sub3);
            }
        }
    }
    /* End */
}
void main()
{
    input();
    MakeBitree();
    printf("前序遍历二叉树：");
    preOrder(RootB);
    printf("\n");
    printf("中序遍历二叉树：");
    symOrder(RootB);
    printf("\n");
    printf("后序遍历二叉树：");
    postOrder(RootB);
    printf("\n");

    RootT = (TRINODE *)malloc(sizeof(TRINODE));
    if(RootT == NULL)
        error("no space");
    B2T(RootB, RootT);
    printf("前序遍历三次树: "); 
    preOrderT(RootT);
    printf("\n");
    printf("后序遍历三次树: "); 
    postOrderT(RootT);
    printf("\n");
    system("pause");
}

/*
请输入括号表示的二叉树(以控制符^Z+换行符为结束):
A(E
   (,6(8
        (,3(,G)),2(4,))),)
^Z
前序遍历二叉树：A E 6 8 3 G 2 4
中序遍历二叉树：E 8 3 G 6 4 2 A
后序遍历二叉树：G 3 8 4 2 6 E A
前序遍历三次树: A E 6 8 3 G 2 4
后序遍历三次树: E 8 3 G 6 4 2 A

请输入括号表示的二叉树(以控制符^Z+换行符为结束):
A(B( ,C(E( ,F(H( ,J(,K)), )),D(G, ))),)
^Z
前序遍历二叉树：A B C E F H J K D G
中序遍历二叉树：B E H J K F C G D A
后序遍历二叉树：K J H F E G D C B A
前序遍历三次树: A B C E F H J K D G
后序遍历三次树: B E H J K F C G D A
*/