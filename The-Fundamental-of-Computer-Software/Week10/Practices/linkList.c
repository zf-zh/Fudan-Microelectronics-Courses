/*	File: linkList.c
	【习题4-53】链接存储线性表综合程序	*/

#include <stdio.h>
#include <stdlib.h>
#define NODE struct node
NODE
{
	int num;
	NODE  *next; 
};
void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
void createListL(NODE *head) 		/* 生成线性表	*/
{
	FILE *fp;
	NODE *node, *prev;
	int  num; 
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("无法打开文件inList.txt");
	while(fscanf(fp, "%d", &num) == 1)
	{
		if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
			error("内存分配失败");
		node->num = num;
		for(prev=head; prev->next; prev=prev->next)
			if(prev->next->num < node->num)
				break;
		node->next = prev->next;
		prev->next = node;
	}
}
NODE *searchL(NODE *head, int key) 	/* 查找结点		*/
{
	NODE *node;
	for(node=head->next; node; node=node->next)
		if(node->num == key)
			return(node); 		/* 查找成功		*/
	return(NULL);				/* 查找失败		*/
}
void addNodeL(NODE *head, NODE *node, int key) /* 增添结点	*/
{
	NODE *prev;
	if(head->next == NULL)
		return;
	/* complete the following code			*/
	for (prev=head;prev->next;prev=prev->next) {
		if(prev->next->num==key) {
			node->next=prev->next;
			prev->next=node;
			return;
		}
	}
	printf("无法找到当前结点\n");
	return;
}
void deleteNodeL(NODE *head, int key) /* 删除结点	*/
{
	NODE *prev, *node;
	if(head->next == NULL)
		return;
	/* complete the following code			*/
	for(prev=head;prev->next;prev=prev->next) {
		if(prev->next->num==key) {
			node=prev->next;
			prev->next=node->next;
			free(node);
			return;
		}
	}
	printf("待删除结点不存在\n");
	return;
}
void prtListL(NODE *first)		 	/* 遍历线性表	*/
{
	NODE *node;
	for(node=first; node; node=node->next)
		printf("%d ", node->num);
	printf("\n");
}

void ExitTask(void)
{
	printf("再见！\n");
	system("pause");
	exit(0);
}
void main()
{
	NODE *Head=NULL, *node;
	int key;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] 查找结点", 
						  "[2] 增添结点",
						  "[3] 删除结点",
						  "[4] 遍历线性表",
						  "[0/其他] 结束"};
	if( (Head = (NODE *)(malloc(sizeof(NODE))) )== NULL) /* 生成哨兵*/
		error("内存分配失败");
	Head->next = NULL;
	printf("## 链接存储线性表综合程序 ##\n");
	printf("根据inList.txt创建链表\n");
	createListL(Head);
	prtListL(Head->next);
	while(1)
	{
		printf("\n");
		for(nItem=0; nItem<5; nItem++)			/* 输出菜单选项		*/
			printf("%s\n", MenuTitle[nItem]);
		printf("请选择：");
		MenuItem = 0;
		scanf("%d", &MenuItem);					/* 输入命令选择		*/
		if(MenuItem == 1)						/* [1] 查找结点		*/
		{
			printf("查找结点值? key = ");
			scanf("%d", &key);
			if((node = searchL(Head, key)) == NULL)
				printf("查找失败\n");
			else
				printf("node = %d\n", node->num);
		}
		else if(MenuItem == 2)					/* [2] 增添结点		*/
		{ 
			printf("插入结点值? key = ");
			scanf("%d", &key);
			if( (node = (NODE *)(malloc(sizeof(NODE))) )== NULL)
				error("内存分配失败");
			node->num = key;
			printf("插在哪个结点之前? key = ");
			scanf("%d", &key);
			addNodeL(Head, node, key);
		}
		else if(MenuItem == 3)					/* [3] 删除结点		*/
		{
			printf("删除哪个结点? key = ");
			scanf("%d", &key);
			deleteNodeL(Head, key);
		}
		else if(MenuItem == 4)					/* [4] 遍历线性表	*/
			prtListL(Head->next);
		else if(MenuItem <= 0 || MenuItem > 4)
			error("再见！");
	}
}
