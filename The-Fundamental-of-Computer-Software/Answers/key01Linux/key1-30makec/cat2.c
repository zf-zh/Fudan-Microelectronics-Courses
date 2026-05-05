/*	File: my_cat.c	*/

#include <stdio.h>
main()
{
	int c;
	while( (c = getchar() ) != EOF)
		putchar(c);
}
