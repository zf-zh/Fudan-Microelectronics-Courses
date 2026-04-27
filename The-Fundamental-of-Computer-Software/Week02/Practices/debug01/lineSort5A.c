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
}*head;
void readFile() 
{
	TEXT *p;FILE *fp;
	char inFile[LINE], line[LINE];
	printf("input file name");
	scanf("%s", inFile);
	fp = fopen(inFile, "r");
	do{
		if (line == "") break;
		p=(TEXT *)malloc(sizeof(TEXT));
		strcpy(p->textline, line);
		p->next=head->next;
		head->next=p;}while(fgets(line, LINE, fp));
	
}

void writeFile(TEXT *h) 
{	
	FILE  *fp;
	char outFile[LINE];
	printf("output file name ");
	scanf("%s", outFile);
	fp = fopen(outFile, "w");
	while ((h=h->next) != NULL)
		fprintf(fp, "%s", h->textline);
}

void main()
{	
	int c = 0;
	TEXT *h,*tail,*p,*q,*r,*t;
	head=(TEXT *)malloc(sizeof(TEXT));
	head->next=NULL;
	readFile();
	h=head;
	for(tail=NULL;h->next!=tail;tail=p) 
	{
		for(q=h;q->next->next!=tail;q=q->next) 
		{
			r=q->next;
			if(1==strcmp(r->textline,r->next->textline)) 
			{
				t=r->next;
				r->next=t->next;	
				q->next=t;
				t->next=r;
			}
		}
		p=q->next;
	}
	writeFile(h);
}


