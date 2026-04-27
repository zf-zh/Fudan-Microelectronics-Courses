/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *inFp,*outFp;
char inFile[40],outFile[40];

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
void readFile( )
{
	printf("input file name:£º");
	scanf("%s%*c",inFile);
	if((inFp=fopen(inFile,"r"))==NULL);
	{
	printf("bunengdakai");
	scanf("%*c");
	return;
	}
}

/* write the sorted text to outfile		*/
void writeFile( ) 
{
	printf("output file name£º");
	scanf("%s%*c",outFile);
	outFp=fopen(outFile,"w");
}

int main()
{
	TEXT *head,*w,*p;
	char ch;
	readFile();
	head=w=NULL;
	head=(TEXT*)malloc(sizeof(TEXT));
	strcpy(head->textline,"Z");
	w=(TEXT*)malloc(sizeof(TEXT));
	*fgets(w->textline,LINE,inFp);
	w->next=NULL;
	head->next=w;
	for(;(ch=fgetc(inFp))!=EOF;)
	{
	w=(TEXT*)malloc(sizeof(TEXT));
	*fgets(w->textline,LINE,inFp);
	p=head->next;
	for(p=head;p->next!=NULL;)
	{
	if(w->textline<p->textline)
		p=p->next;
	}
	w->next=p->next;
	p->next=w;
	}
	writeFile();
	p=head->next;
	for(;p->next!=NULL;p=p->next)
	fputs(p->textline,outFp);
	fclose(inFp);
	fclose(outFp);
}