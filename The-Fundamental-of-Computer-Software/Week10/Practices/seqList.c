/*	File: seqList.c
	【习题4-52】顺序存储线性表综合程序	*/

// Encoding: UTF-8

#include <stdio.h>
#include <stdlib.h>
#define M 100
void error(char *string)
{
	printf("%s\n", string);
	system("pause");
	exit(0);
}
void createListS(int a[], int *n) 		/* 生成线性表	*/
{
	FILE *fp;
	int  num;
	if((fp = fopen("inList.txt", "r")) == NULL)
		error("无法打开文件inList.txt");
	*n = 0;
	while(fscanf(fp, "%d", &num) == 1)
	{
		for(k=(*n); k>0 && num<a[k-1]; k--)	/* 定位	*/
			a[k] = a[k-1];					/* 移位	*/
		a[k] = num;							/* 插入	*/
		(*n)++;
	}
}
int searchS(int a[], int n, int key) 	/* 查找结点		*/
{
	int i;
	for(i=0; i<n; i++)
		if(a[i] == key)
			return(i); 	/* 查找成功	*/
	return(-1);			/* 查找失败	*/
}
void addNodeS(int a[], int *n, int i, int key)
{
	int j;
	if(*n == M-1)						/* 数组溢出		*/
		error("数组溢出");
	if(i<-1 || i >(*n)-1)				/* 非法结点位置	*/
		error("非法结点位置");	/* 如果i==-1，表示在线性表的前面添加结点 */
	/* complete the following code			*/
	for(j=(*n)-1;j>=i;j--) {
		a[j+1]=a[j];
	}
	a[++j]=key;
	(*n)++;
}
void  deleteNodeS(int a[], int *n, int key) /* 删除结点	*/
{
	int i, k;
	if((i = searchS(a, *n, key)) == -1)
	{
		printf("无法找到待删除结点\n");
		return;
	}
	/* complete the following code			*/
	for(k=i;k<(*n)-1;k++) {
		a[k]=a[k+1];
	}
	(*n)--;
}
void prtListS(int a[], int n)		 	/* 遍历线性表	*/
{
	int i;
	for(i=0; i<n; i++)
		printf("a[%d]=%d ", i, a[i]);
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
	int a[M], n, i, key;
	short MenuItem, nItem;
	char *MenuTitle[] = { "[1] 查找结点", 
						  "[2] 增添结点",
						  "[3] 删除结点",
						  "[4] 遍历线性表",
						  "[0/其他] 结束"};
	printf("## 顺序存储线性表综合程序 ##\n");
	printf("根据inList.txt创建线性表\n");
	createListS(a, &n);
	prtListS(a, n);
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
			printf("查找哪个结点? key = ");
			scanf("%d", &key);
			if((i = searchS(a, n, key)) == -1)
				printf("查找失败\n");
			else
				printf("a[%d] = %d\n", i, key);
		}
		else if(MenuItem == 2)					/* [2] 增添结点		*/
		{ 
			printf("插在哪个结点之前? key = ");
			scanf("%d", &key);
			if((i = searchS(a, n, key)) == -1)
			{
				printf("结点%d不存在\n", key);
				continue;
			}
			printf("插入结点值? key = ");
			scanf("%d", &key);
			addNodeS(a, &n, i, key);
		}
		else if(MenuItem == 3)					/* [3] 删除结点		*/
		{
			printf("删除哪个结点? key = ");
			scanf("%d", &key);
			deleteNodeS(a, &n, key);
		}
		else if(MenuItem == 4)					/* [4] 遍历线性表	*/
			prtListS(a, n);
		else if(MenuItem <= 0 || MenuItem > 4)
			error("再见！");
	}
}
