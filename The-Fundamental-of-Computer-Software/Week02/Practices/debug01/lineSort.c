/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* data definition	*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};

/* read text from infile		*/
/* store each line as request	*/
TEXT *readFile(FILE *fp)
{
	char buf[LINE];
	/* ----------complete program----------	*/



	/* ------------------------------------	*/
}

/* write the sorted text to outfile		*/
void writeFile(FILE *fp, TEXT *head)
{
	/* ----------complete program----------	*/



	/* ------------------------------------	*/
}

int main()
{
	FILE *inFp, *outFp;
	TEXT *head=NULL;
	char outFile[20], inFile[20];

	/* ----------complete program----------	*/



	/* ------------------------------------	*/

}
/*
inFileA.txt
outFileA.txt

inFileB.txt
outFileB.txt
*/
