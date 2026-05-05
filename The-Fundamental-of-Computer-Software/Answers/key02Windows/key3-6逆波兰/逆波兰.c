/*	File: 逆波兰.c
	【习题3-6】计算逆波兰表达式的程序	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define maxlen 50
int pointer=0, stack[maxlen], c[10];
push(value)
int value;
{
	stack[++pointer] = value;
}
int pop()
{
	return(stack[pointer--]);
}
main()
{
	int ch, i=0, j, result, oprd1, oprd2;
	printf("expression: ");
	while((ch = getchar()) != '#')
	{
		if(isspace(ch))
			continue;
		if(isdigit(ch))
			push(ch - '0');
		else
		{
			oprd1 = pop();
			oprd2 = pop();
			switch(ch)
			{
				case '+': result = oprd2 + oprd1; break;
				case '-': result = oprd2 - oprd1; break;
				case 'X': result = oprd2 * oprd1; break;
			}
			c[i] = result;
			i++;
			push(result);
		}
	}
	for(j=0; j<i; j++)
		printf("c[%d] = %d\n", j+1, c[j]);
	printf("the result is %d\n", pop());
	system("pause");
}

/*
expression: 4 8 9 7 1 4 5 7 2 8 - + X + - X + - + #
c[1] = -6
c[2] = 1
c[3] = 5
c[4] = 9
c[5] = -8
c[6] = -56
c[7] = -47
c[8] = 55
c[9] = 59
the result is 59
*/
