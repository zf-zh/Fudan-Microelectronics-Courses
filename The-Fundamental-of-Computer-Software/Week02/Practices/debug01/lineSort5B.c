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
int main(int argc, char* argv[])
{
text *head=NULL,*p,*q,*w;
printf("input file name:");
char inFile[LINE];
scanf("%s",inFile);
FILE *inFp=fopen(inFile,"r"),*outFp;
if(inFp==NULL)	
	{		
	printf("cannot found file\n");		
	return;	
	}	
p=(struct text*)malloc(sizeof(struct text));
w=(struct text*)malloc(sizeof(struct text));
fgets(p->textline,LINE,inFp);
p->next=head;w->next=p;head=w;
p=(struct text*)malloc(sizeof(struct text));
while(fgets(p->textline,LINE,inFp))
{
 w=head;
 q=head->next;
 while(q)
 {
  if(p->textline[0]>=q->textline[0])
  {
   if(q->next==NULL)
   {
    p->next=q->next;
	q->next=p;
	break;
   }
   else
   {q=q->next;w=w->next;}
  }
  else
  {
  w->next=p;p->next=q;
  break;
  }
 }
 p=(struct text*)malloc(sizeof(struct text));
}
q=head->next;
printf("output file name:");
char outFile[LINE];
scanf("%s",outFile);
outFp=fopen(outFile,"w+");
while(q)
{
 fprintf(outFp,"%s",q->textline);
 q=q->next;
}
fclose(inFp);
}
