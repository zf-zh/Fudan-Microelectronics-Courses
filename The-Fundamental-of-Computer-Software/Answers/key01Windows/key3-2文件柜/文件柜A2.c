/*	File: 文件柜A2.c
	【习题 3-2A2】文件柜: 定义含有n4,n6,n9和cost的结构变量rs	*/

#include <stdio.h>
#include <stdlib.h>
#define RS   struct rs
RS
{
	int n4, n6, n9, cost;
};
main()
{
	int c4=20, c6=25, c9=30, e4=100/4, e6=100/6, e9=100/9, n=0;
	RS rs;
	for(rs.n4=1; rs.n4<=e4; rs.n4++)
	for(rs.n6=1; rs.n6<=e6; rs.n6++)
	for(rs.n9=1; rs.n9<=e9; rs.n9++)
		if(rs.n4*4 + rs.n6*6 + rs.n9*9 == 100)
		{
			rs.cost = rs.n4*c4 + rs.n6*c6 + rs.n9*c9;
			printf("cost= %2d*%2d+%2d*%2d+%2d*%2d= %2d\n",
					rs.n4, c4, rs.n6, c6, rs.n9, c9, rs.cost);
			n++;
		}
	printf("n=%2d\n", n);
	system("pause");
}
/*
cost=  1*20+ 1*25+10*30= 345
cost=  1*20+ 4*25+ 8*30= 360
cost=  1*20+ 7*25+ 6*30= 375
cost=  1*20+10*25+ 4*30= 390
cost=  1*20+13*25+ 2*30= 405
cost=  4*20+ 2*25+ 8*30= 370
cost=  4*20+ 5*25+ 6*30= 385
cost=  4*20+ 8*25+ 4*30= 400
cost=  4*20+11*25+ 2*30= 415
cost=  7*20+ 3*25+ 6*30= 395
cost=  7*20+ 6*25+ 4*30= 410
cost=  7*20+ 9*25+ 2*30= 425
cost= 10*20+ 1*25+ 6*30= 405
cost= 10*20+ 4*25+ 4*30= 420
cost= 10*20+ 7*25+ 2*30= 435
cost= 13*20+ 2*25+ 4*30= 430
cost= 13*20+ 5*25+ 2*30= 445
cost= 16*20+ 3*25+ 2*30= 455
cost= 19*20+ 1*25+ 2*30= 465
n=19
*/
