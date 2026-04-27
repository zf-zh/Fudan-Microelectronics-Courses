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

TEXT *p,*head;

/* read text from infile		*/
/* store each line as request	*/
void readFile( )
{
	FILE *inFp;
	char inFile[20];
mark1:
	printf("input file name£º");
	scanf("%s",inFile);
	{
		if((inFp=fopen(inFile,"r"))==NULL)
		{	
			printf("file not found\n");
			goto mark1;
		}
	}
	while(!feof(inFp))
	{

		if(head==NULL)
		{
			p=head=(TEXT*)malloc(sizeof(TEXT));
			p->next=NULL;
			fgets(p->textline,80,inFp);
		}
		else
		{
			p=p->next=(TEXT*)malloc(sizeof(TEXT));
			p->next=NULL;
			fgets(p->textline,80,inFp);
		}
	}	
	return;
}

/* write the sorted text to outfile		*/
void doit()
{
	int mark0=0;
	TEXT *pre,*w,*q,*temp;
	mark2:
	w=head,q=head->next;
	while(q->next!=NULL)
	{
		if((w->textline[0]) > (q->textline[0]))
		{
			mark0=1;
			temp=w;
			if(temp==head)
			{
				head=q,temp->next=q->next,head->next=temp;
			}
			else 
			{
				pre=head;
				while(pre->next!=w) pre=pre->next;
				pre->next=q,temp->next=q->next,q->next=temp;
			}

		}
		else
		{
			w=w->next;
			q=w->next;
		}
		q=w->next;
	}
	if(mark0==1)
	{
		mark0=0;
		goto mark2;
	}
	return;
}
void writeFile( )
{
	char outFile[20];
	FILE *outFp;
	TEXT *z=head;
	TEXT *w=head;
	printf("output file name£º");
	scanf("%s",outFile);
	outFp=fopen(outFile,"w");
	while(z->next!=NULL)
	{
		printf("%s",z->textline);
		z=z->next;
	}
	doit();
	while(w->next!=NULL)
	{
		fputs(w->textline,outFp);
		w=w->next;
	}
	return;
}

int main()
{
	readFile();
	writeFile();
	return 0;
}

