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
FILE *inFp;
FILE *outFp;
void readFile(char inFile[20])
{
	if((inFp=fopen(inFile,"r"))==NULL)
	{
		printf("Cannot open the file %s correctly.",inFile);
		return;
	}
}
void writeFile(char outFile[20])
{
	char cc;
	outFp=fopen(outFile,"w");
	while((outFp=fopen(outFile,"w"))!=NULL)
	{
		while((cc=fgetc(inFp))!=EOF)
			fputc(cc,outFp);
	}
}
void main()
{
	TEXT *head=NULL,*p,*q,*s;
	char inFile[20],outFile[20];
	TEXT L;
	printf("Please input the name of the file: \n");
	scanf("%s%*c",inFile);
	readFile(inFile);
	char c[LINE];
	int i=1;
	while((c[i]=fgetc(inFp))!=EOF)
	{	
		p=head;
	    q=textline->next;
		while(q->textline > p->textline)
		{
			s=q;
			q=q->next;
		}
		if(p==head)
		{head=q;}
		else
		{s->next=q;}
		q->next=p;
	};
	printf("Please input the object file: \n");
	scanf("&s%*c",outFile);
	writeFile(outFile);
	fclose(inFp);
	fclose(outFp);
	system("pause");
}

