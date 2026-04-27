/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

/* data definition	*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};
	TEXT *head,*p,*q,*t;
	FILE *infp,*outfp;
	char infile[LINE],outfile[LINE],jud[LINE];

/* read text from infile		*/
/* store each line as request	*/
void readFile( )
{
	printf("input file name: \n");
	scanf("%s%*c",infile);
	printf("output file name: \n");
	scanf("%s%*c",outfile);
	infp=fopen("infile","r+");
	outfp=fopen("outfile","w+");
}

/* write the sorted text to outfile		*/
void writeFile( )
{
	for(p=head->next;p;p=p->next)
		fprintf(outfp,"%s",p->textline);
}

int main()
{
	readFile();
	head=(TEXT*)malloc(sizeof(TEXT));
	head->next=NULL;
	while(!feof(infp)) 
	{
		fgets(jud,LINE,infp);
	    for(p=head,q=head->next;strcmp(q->textline,jud)<0&&q;p=q,q=q->next);
		    t=(TEXT*)malloc(sizeof(TEXT));
		    strcpy(t->textline,jud);
		    t->next=q;
		    p->next=t;
	}
	 writeFile();
     fclose(infp);
	 fclose(outfp);
}

