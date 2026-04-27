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
FILE *infp,*outfp;
/* read text from infile		*/
/* store each line as request	*/
TEXT *readFile(FILE *infp)
{
	int i=0;
	TEXT *p,*h=NULL,*s;
	while(1)
	{
		p=(TEXT*)malloc(sizeof(TEXT));
		if(fgets(p->textline,80,infp)==0)
			break;
		p->next=NULL;
		if(h==NULL)
			s=h=p;
		else
		{
			s->next=p;
		    s=p;
		}
	}
	for(p=h;p!=NULL;p=p->next)
		printf("%s\n",p->textline);
	return h;
}

/* write the sorted text to outfile		*/
void writeFile(FILE *outfp,TEXT *fp)
{
	TEXT *p;
	p=fp;
	while(p!=NULL)
	{
		fprintf(outfp,"%s\n",p->textline);
		p=p->next;
		
	}

}

int main()
{
	int i=1;
	char inFile[40],outFile[40];
	TEXT *fp,*p,*s,*t;
	printf("input file name:");
	scanf("%s%*c",inFile);
	infp=fopen(inFile,"r");
	fp=readFile(infp);
	while(i!=0)
	{
		i=0;
		for(p=fp;p->next!=NULL;)
		{
			s=p->next;
			if(strcmp(p->textline,s->textline)>0)
			{
				if(p==fp)
					fp=p->next;
				else
					t->next=p->next;
				p->next=s->next;
				s->next=p;
				t=s;
				i++;
			}
			else
			{
				t=p;
				p=p->next;
			}
		}
	}
	for(p=fp;p!=NULL;p=p->next)
		printf("%s\n",p->textline);
	printf("output file name:");
	scanf("%s%*c",outFile);
	outfp=fopen(outFile,"w");
	writeFile(outfp,fp);
	
	

		

}