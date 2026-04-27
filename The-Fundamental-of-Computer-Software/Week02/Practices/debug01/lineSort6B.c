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
FILE *readFile()
{
	FILE *fp;
	char inFile[LINE];
	printf("input file name��");
	// gets(inFile);
	// Use fgets instead of gets, and remove the newline character
	fgets(inFile, LINE, stdin);
	if (inFile[strlen(inFile) - 1] == '\n')
		inFile[strlen(inFile) - 1] = '\0';
	fp=fopen(inFile,"r"); 
	return fp;
}

/* write the sorted text to outfile		*/
FILE *writeFile()
{
	FILE *fp;
	char outFile[LINE];
	printf("output file name��");
	// gets(outFile);
	// Use fgets instead of gets, and remove the newline character
	fgets(outFile, LINE, stdin);
	if (outFile[strlen(outFile) - 1] == '\n')
		outFile[strlen(outFile) - 1] = '\0';
	fp=fopen(outFile,"w"); 
	return fp;
}
int main()
{
	FILE *inFp,*outFp;
	TEXT *p=NULL,*q=NULL,*in=NULL,*out=NULL;
	int i,j,n;
	inFp=readFile();
	while (!feof(inFp))
	{
		q=(TEXT*)malloc(sizeof(TEXT));
		q->next=NULL;
		fgets(q->textline,LINE,inFp);
		q->next=in;
		in=q;
		n++;
	}
	n--;
	in=in->next;
	while (n>0)
	{
		n--;
		p=in;q=in;
		while (p!=NULL)
		{
			if (strcmp(p->textline,q->textline)<0) q=p;
			p=p->next;
		}
		if (q==in)
		{
			in=in->next;
			q->next=NULL;
			if (out==NULL) out=q;
			else
			{
				p=out;
				while (p->next!=NULL) p=p->next;
				p->next=q;
			}
		}
		else
		{
			p=in;
			while (p->next!=q) p=p->next;
			p->next=q->next;
			q->next=NULL;
			if (out==NULL) out=q;
			else
			{
				p=out;
				while (p->next!=NULL) p=p->next;
				p->next=q;
			}
		}
	}
	outFp=writeFile();
	p=out;
	while (p!=NULL)
	{
		fputs(p->textline,outFp);
		// puts(p->textline);
		p=p->next;
	}
	// system("pause");
	return 0;
}

