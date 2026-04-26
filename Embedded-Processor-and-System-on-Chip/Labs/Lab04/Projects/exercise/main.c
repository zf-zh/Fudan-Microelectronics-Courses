#include <stdio.h>
#include <stdlib.h>

int mymul(int,int);
int myfac(int);

int main()
{

	//Test for mymul
	printf("Test for mymul:\n");
	printf("0*5=%d\n",mymul(0,5));
	printf("(-3)*0=%d\n",mymul(-3,0));
	printf("3*5=%d\n",mymul(3,5));
	printf("(-3)*5=%d\n",mymul(-3,5));
	printf("3*(-5)=%d\n",mymul(3,-5));
	printf("(-3)*(-5)=%d\n",mymul(-3,-5));

	//Test for myfac
	printf("\nTest for myfac:\n");
	for(int i=0; i<10; i++)
	{
		printf("%d!=%d\n",i,myfac(i));
	}

	return 0;

}


