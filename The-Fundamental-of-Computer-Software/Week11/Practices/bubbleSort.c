/*  File: bubbleSort.c
    【习题4-45】顺序存储冒泡排序(降序) */

#include <stdio.h>
#include <stdlib.h>
void swap2(int *x, int *y)
{    
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void prt(int a[], int n, int k)
{
    int i;
    for(i=0; i<n; i++)
        printf("%c%d%c", i==0 ? '[' : ' ', a[i], i==k ? ']' : ' ');
    printf("\n");
}
void bubble(int a[], int n)
{
    int i, j, tmp, s;
    for(i=0; i<n-1; i=s)
    {
        /* complete the follwing code */
        for (s = j = n - 1; j > i; j--) {
            if (a[j] > a[j - 1]) {
                swap2(&a[j], &a[j - 1]);
                s = j;
            }
        }
        prt(a, n, s-1);
    }
    prt(a, n, s);
}
void main()
{
    int a[20], n, i;
    scanf("%d", &n);
    for(i=0; i<n; i++)
        scanf("%d", &a[i]);
    printf("冒泡排序\n");
    bubble(a, n);
    system("pause");
}
/*
输入数据1
6
5 2 1 8 3 7
冒泡排序
[8] 5  2  1  7  3
[8  7] 5  2  1  3
[8  7  5  3] 2  1
[8  7  5  3  2] 1
[8  7  5  3  2  1]

输入数据2
5
6 2 8 4 5
冒泡排序
[8] 6  2  5  4
[8  6  5] 2  4
[8  6  5  4] 2
[8  6  5  4  2]

输入数据3
9
2 3 4 1 5 6 7 8 9
冒泡排序
[9] 2  3  4  1  5  6  7  8
[9  8] 2  3  4  1  5  6  7
[9  8  7] 2  3  4  1  5  6
[9  8  7  6] 2  3  4  1  5
[9  8  7  6  5] 2  3  4  1
[9  8  7  6  5  4] 2  3  1
[9  8  7  6  5  4  3] 2  1
[9  8  7  6  5  4  3  2] 1
[9  8  7  6  5  4  3  2  1]
*/