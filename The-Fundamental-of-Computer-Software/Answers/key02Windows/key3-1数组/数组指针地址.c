/* File: 数组指针地址.c
	【习题3-1】数组指针地址
*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
	int a[10], *p, *q, **pp, i;
	for(i=0; i<10; i++)
		a[i] = 10 * i;
	p = a + 1;
	q = a + 8;
	pp = &p;
	printf("(1) a[0] = %d\n", a[0]);
	printf("(2) *(a+3) = %d\n", *(a+3));
	printf("(3) a[3] = %d\n", a[3]);
	printf("(4) q-p = %d\n", q-p);
	printf("(5) *p = %d\n", *p);
	printf("(6) *q = %d\n", *q);
	printf("(7) a[q-p] = %d\n", a[q-p]);
	printf("(8) a[(q-p)/3] = %d\n", a[(q-p)/3]);
	printf("(9) a[(q-p)/4] = %d\n", a[(q-p)/4]);
	printf("(10) *(q-2) = %d\n", *(q-2));
	printf("(11) *(p+2*3) = %d\n", *(p+2*3));
	printf("(12) *(p+4)*(*(q-2)) = %d\n", *(p+4)*(*(q-2)));
	printf("(13) *((*pp)+5) = %d\n", *((*pp)+5));
	printf("(14) **pp+5 = %d\n", **pp+5);
	printf("(15) &a[3]-&a[0] = %d\n", &a[3]-&a[0]);
	system("pause");
}
/*
(1) a[0] = 0
(2) *(a+3) = 30
(3) a[3] = 30
(4) q-p = 7
(5) *p = 10
(6) *q = 80
(7) a[q-p] = 70
(8) a[(q-p)/3] = 20
(9) a[(q-p)/4] = 10
(10) *(q-2) = 60
(11) *(p+2*3) = 70
(12) *(p+4)*(*(q-2)) = 3000
(13) *((*pp)+5) = 60
(14) **pp+5 = 15
(15) &a[3]-&a[0] = 3
*/