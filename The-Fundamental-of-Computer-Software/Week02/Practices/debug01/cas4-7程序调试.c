/*	File: cas4-7程序调试.c
	【例4-7】程序调试示例
	上机辅导四:	C程序调试初步	*/

#include <stdio.h>
#include <stdlib.h>	/* exit需要的头文件	*/
void prt(short n)
{
	short a[10], i, j;
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	for(i=n-1, j=0; i>=0; i--)
		if(a[i] > 0)
		{
			j++;
			printf("%d", a[i]);
			printf("%c", j%3 ? '\n' : '\t');
		}
	if((j % 3) == 0)
		printf("\n");
}
main()
{
	short n;
	while(1)
	{
		printf("Input n[0<n<10]: ");
		scanf("%d", &n);
		if(n <= 0)
			exit(0);
		else if(n < 10)
			prt(n);
	}
}
/*
9
1 0 3 5 6 0 6 3 2
8
0 2 3 5 2 -14 4 9
0

Expected results:
Input n: 9
1 0 3 5 6 0 6 3 2
2       3       6
0       6       5
3       0       1
Input n: 8
0 2 3 5 2 -14 4 9
9       4       2
5       3       2
0
Input n: 0
*/
