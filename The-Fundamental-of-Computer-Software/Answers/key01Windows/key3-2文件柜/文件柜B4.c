/*	File: 文件柜B4.c
	【习题 3-2B4】文件柜: 定义含有n4,n6,n9和cost的结构数组rs[]。
		用void drawer()计算	*/

#include <stdio.h>
#include <stdlib.h>
#define RS   struct rs
RS
{
	int n4, n6, n9, cost;
};
drawer(rs, n)
RS rs[];
int *n;
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, i4, i6, i9;
	for(i4=1; i4<=e4; i4++)
	for(i6=1; i6<=e6; i6++)
	for(i9=1; i9<=e9; i9++)
		if(i4*4 + i6*6 + i9*9 == 100)
		{
			rs[*n].n4 = i4;
			rs[*n].n6 = i6;
			rs[*n].n9 = i9;
			rs[(*n)++].cost = i4*c4 + i6*c6 + i9*c9;
		}
}
main()
{
	RS rs[500];
	int c4=20, c6=25, c9=30, n=0, i;
	drawer(rs, &n);
	for(i=0; i<n; i++)
		printf("cost = %2d*%2d+%2d*%2d+%2d*%2d = %2d\n",
				rs[i].n4, c4, rs[i].n6, rs[i].n6, rs[i].n9, c9, rs[i].cost);
	printf("n=%2d\n", n);
	system("pause");
}
/*
cost =  1*20+ 1* 1+10*30 = 345
cost =  1*20+ 4* 4+ 8*30 = 360
cost =  1*20+ 7* 7+ 6*30 = 375
cost =  1*20+10*10+ 4*30 = 390
cost =  1*20+13*13+ 2*30 = 405
cost =  4*20+ 2* 2+ 8*30 = 370
cost =  4*20+ 5* 5+ 6*30 = 385
cost =  4*20+ 8* 8+ 4*30 = 400
cost =  4*20+11*11+ 2*30 = 415
cost =  7*20+ 3* 3+ 6*30 = 395
cost =  7*20+ 6* 6+ 4*30 = 410
cost =  7*20+ 9* 9+ 2*30 = 425
cost = 10*20+ 1* 1+ 6*30 = 405
cost = 10*20+ 4* 4+ 4*30 = 420
cost = 10*20+ 7* 7+ 2*30 = 435
cost = 13*20+ 2* 2+ 4*30 = 430
cost = 13*20+ 5* 5+ 2*30 = 445
cost = 16*20+ 3* 3+ 2*30 = 455
cost = 19*20+ 1* 1+ 2*30 = 465
n=19
*/
