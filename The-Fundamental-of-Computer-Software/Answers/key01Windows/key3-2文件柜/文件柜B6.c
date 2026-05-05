/*	File: 文件柜B6.c
	【习题 3-2B6】文件柜:定义含有n4,n6,n9和cost的结构指针rs，动态分配存储单元。
		用void drawer()计算	*/

#include <stdio.h>
#include <stdlib.h>
#define RS   struct rs
RS
{
	int n4, n6, n9, cost;
};
void drawer(rs, n)
RS **rs;
int *n;
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, i4, i6, i9;
	*rs = (RS *)malloc(500 * sizeof(RS));
	for(i4=1; i4<=e4; i4++)
	for(i6=1; i6<=e6; i6++)
	for(i9=1; i9<=e9; i9++)
		if(i4*4 + i6*6 + i9*9 == 100)
		{
			(*rs)[*n].n4 = i4;
			(*rs)[*n].n6 = i6;
			(*rs)[*n].n9 = i9;
			(*rs)[(*n)++].cost = i4*c4 + i6*c6 + i9*c9;
		}
}
main()
{
	int c4=20, c6=25, c9=30, n=0, i;  RS *rs;
	drawer(&rs, &n);
	for(i=0; i<n; i++)
		printf("cost = %2d*%2d+%2d*%2d+%2d*%2d = %2d\n",
				rs[i].n4, c4, rs[i].n6, c6, rs[i].n9, c9, rs[i].cost);
	printf("n=%2d\n", n);
	system("pause");
}
/*
cost =  1*20+ 1*25+10*30 = 345
cost =  1*20+ 4*25+ 8*30 = 360
cost =  1*20+ 7*25+ 6*30 = 375
cost =  1*20+10*25+ 4*30 = 390
cost =  1*20+13*25+ 2*30 = 405
cost =  4*20+ 2*25+ 8*30 = 370
cost =  4*20+ 5*25+ 6*30 = 385
cost =  4*20+ 8*25+ 4*30 = 400
cost =  4*20+11*25+ 2*30 = 415
cost =  7*20+ 3*25+ 6*30 = 395
cost =  7*20+ 6*25+ 4*30 = 410
cost =  7*20+ 9*25+ 2*30 = 425
cost = 10*20+ 1*25+ 6*30 = 405
cost = 10*20+ 4*25+ 4*30 = 420
cost = 10*20+ 7*25+ 2*30 = 435
cost = 13*20+ 2*25+ 4*30 = 430
cost = 13*20+ 5*25+ 2*30 = 445
cost = 16*20+ 3*25+ 2*30 = 455
cost = 19*20+ 1*25+ 2*30 = 465
n=19
*/
