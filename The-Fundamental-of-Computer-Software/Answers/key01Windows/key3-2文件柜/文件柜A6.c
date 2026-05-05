/*	File: 文件柜A6.c
	【习题3-2A6】文件柜: 定义含有n4,n6,n9和cost的结构指针rs,动态分配存储单元	*/

#include <stdio.h>
#include <stdlib.h>
#define RS   struct rs
RS { int n4, n6, n9, cost; };
main()
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, n=0;
	int n4, n6, n9, i=0;
	RS *rs;
	rs = (RS *)malloc(500 * sizeof(RS));
	for(n4=1; n4<=e4; n4++)
	for(n6=1; n6<=e6; n6++)
	for(n9=1; n9<=e9; n9++)
		if(n4*4 + n6*6 + n9*9 == 100)
		{
			rs[i].n4 = n4;
			rs[i].n6 = n6;
			rs[i].n9 = n9;
			rs[i++].cost = n4*c4 + n6*c6 + n9*c9;
		}
	for(n=i, i=0; i<n; i++)
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
