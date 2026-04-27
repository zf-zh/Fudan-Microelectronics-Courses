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
readFile(char*inFile)
{
	char*inFp;
	inFp=fopen(inFile,"r");
	return(inFp);
}


/* write the sorted text to outfile		*/
void writeFile( char*outFile,char*inFp)
{
	char*outFp;
	outFp=fopen(outFile,"w");
	fprintf(outFp,"%s",inFp);
}
int main()
{
	char inFile[10],outFile[10];
	char*inFp;
	printf("input file name:\n");
	scanf("%s",inFile);
	inFp=readFile(inFile);
	printf("output file name:\n");
	scanf("%s",outFile);
	writeFile(outFile,inFp);
}

