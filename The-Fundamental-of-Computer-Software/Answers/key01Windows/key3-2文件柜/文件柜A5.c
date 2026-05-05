/*	File: 文件柜A5.c
	【习题3-2A5】文件柜: 定义指针n4,n6,n9和cost,动态分配存储单元	*/

#include <stdio.h>
#include <stdlib.h>
main()
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, n=0;
	int *n4, *n6, *n9, *cost, i4, i6, i9;
	n4 = (int *)malloc(sizeof(int));
	n6 = (int *)malloc(sizeof(int));
	n9 = (int *)malloc(sizeof(int));
	cost = (int *)malloc(sizeof(int));
	for(i4=1; i4<=e4; i4++)
	for(i6=1; i6<=e6; i6++)
	for(i9=1; i9<=e9; i9++)
		if(i4*4 + i6*6 + i9*9 == 100)
		{
			*n4 = i4;
			*n6 = i6;
			*n9 = i9;
			*cost = i4*c4 + i6*c6 + i9*c9;
			printf("cost= %2d*%2d+%2d*%2d+%2d*%2d= %2d\n",
					*n4, c4, *n6, c6, *n9, c9, *cost);
			n ++;
		}
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
