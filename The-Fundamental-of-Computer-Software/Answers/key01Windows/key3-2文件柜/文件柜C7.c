/*	File: 文件柜C7.c
	【习题 3-2C7】文件柜:定义含有n4,n6,n9,cost和结构指针prs为外部变量。
		每得到一种方案,动态分配一个结构单元,用指针链结各个结构。
		用void drawer()计算, 在main中遍历链表得到n	*/

#include <stdio.h>
#include <stdlib.h>
#define PRS   struct prs
PRS
{
	int n4, n6, n9, cost;
	PRS *next;
};
PRS *prs=NULL;
void drawer()
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, i4, i6, i9;
	PRS *tmp;
	for(i4=1; i4<=e4; i4++)
	for(i6=1; i6<=e6; i6++)
	for(i9=1; i9<=e9; i9++)
		if(i4*4 + i6*6 + i9*9 == 100)
		{
			tmp = (PRS *)malloc(sizeof(PRS));
			tmp->n4 = i4;
			tmp->n6 = i6;
			tmp->n9 = i9;
			tmp->cost = i4*c4 + i6*c6 + i9*c9;
			tmp->next = prs;
			prs = tmp;
		}
}
main()
{
	int c4=20, c6=25, c9=30, n=0;
	PRS *tmp;
	drawer();
	for(tmp=prs; tmp!=NULL; tmp=tmp->next, n++)
		printf("cost = %2d*%2d+%2d*%2d+%2d*%2d = %2d\n",
				tmp->n4, c4, tmp->n6, c6, tmp->n9, c9, tmp->cost);
	printf("n=%2d\n", n);
	system("pause");
}
/*
cost = 19*20+ 1*25+ 2*30 = 465
cost = 16*20+ 3*25+ 2*30 = 455
cost = 13*20+ 5*25+ 2*30 = 445
cost = 13*20+ 2*25+ 4*30 = 430
cost = 10*20+ 7*25+ 2*30 = 435
cost = 10*20+ 4*25+ 4*30 = 420
cost = 10*20+ 1*25+ 6*30 = 405
cost =  7*20+ 9*25+ 2*30 = 425
cost =  7*20+ 6*25+ 4*30 = 410
cost =  7*20+ 3*25+ 6*30 = 395
cost =  4*20+11*25+ 2*30 = 415
cost =  4*20+ 8*25+ 4*30 = 400
cost =  4*20+ 5*25+ 6*30 = 385
cost =  4*20+ 2*25+ 8*30 = 370
cost =  1*20+13*25+ 2*30 = 405
cost =  1*20+10*25+ 4*30 = 390
cost =  1*20+ 7*25+ 6*30 = 375
cost =  1*20+ 4*25+ 8*30 = 360
cost =  1*20+ 1*25+10*30 = 345
n=19
*/
