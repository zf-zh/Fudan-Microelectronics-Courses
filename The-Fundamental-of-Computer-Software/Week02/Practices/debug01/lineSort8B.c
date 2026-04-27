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
TEXT *head;
FILE *inFp,*outFp;
/* read text from infile		*/
/* store each line as request	*/
void readFile()
{
	TEXT *f;
	char s[LINE];
	head=(TEXT *)malloc(sizeof(TEXT));
	head->next=NULL;
	while (fgets(s,LINE,inFp)!= NULL)
	{
        f=(TEXT*)malloc(sizeof(TEXT));
		puts(s);
        strcpy(f->textline,s);
        f->next=head->next;
        head->next=f;
    }
}

/* write the sorted text to outfile		*/
void writeFile()
{
	TEXT *fp,*fq,*front,*t;
	fp=(TEXT *)malloc(sizeof(TEXT));
	fq=(TEXT *)malloc(sizeof(TEXT));
	front=(TEXT *)malloc(sizeof(TEXT));
	fp=head->next;
	fp->next=NULL;
	head->next=head->next->next;
	fq->next=fp;
	front->next=fp;
	while(head->next!=NULL)
	{
		while (strcmp(fp->textline,head->next->textline)>0)
		{
			fp=fp->next;
			front=front->next;
		}
		t=head->next->next;
		head->next->next=fp;
		front->next=head->next;
		head->next=t;
		fp=fq->next;
		front->next=fp;
	}
	while (fp!=NULL)
	{
		fprintf(outFp,"%s\n",fp->textline);
		fp=fp->next;
	}
}

int main()
{
	char fname1[40],fname2[40];
	printf("input file name: ");
	scanf("%s%*c",fname1);
	printf("output file name: ");
	scanf("%s%*c",fname2);
	inFp=fopen(fname1,"r");
	outFp=fopen(fname2,"w");
	readFile();
	writeFile();
	fclose(inFp);
	fclose(outFp);
}

