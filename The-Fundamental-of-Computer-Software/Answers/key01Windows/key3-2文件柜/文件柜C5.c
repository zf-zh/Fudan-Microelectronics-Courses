/*	File: 文件柜C5.c
	【习题 3-2C5】文件柜:定义指针n4,n6,n9和cost为外部变量,动态分配单元。
		用int drawer()返回n	*/

#include <stdio.h>
#include <stdlib.h>
int *n4, *n6, *n9, *cost;
int drawer()
{
	int c4=20, c6=25, c9=30;
	int e4=100/4, e6=100/6, e9=100/9, n=0, i4, i6, i9;
	n4 = (int *)malloc(500 * sizeof(int));
	n6 = (int *)malloc(500 * sizeof(int));
	n9 = (int *)malloc(500 * sizeof(int));
	cost = (int *)malloc(500 * sizeof(int));
	for(i4=1; i4<=e4; i4++)
	for(i6=1; i6<=e6; i6++)
	for(i9=1; i9<=e9; i9++)
		if(i4*4 + i6*6 + i9*9 == 100)
		{
			n4[n] = i4;
			n6[n] = i6;
			n9[n] = i9;
			cost[n++] = i4*c4 + i6*c6 + i9*c9;
		}
	return(n);
}
main()
{
	int c4=20, c6=25, c9=30, n, i;
	n = drawer();
	for(i=0; i<n; i++)
		printf("cost = %2d*%2d+%2d*%2d+%2d*%2d = %2d\n",
				n4[i], c4, n6[i], c6, n9[i], c9, cost[i]);
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
