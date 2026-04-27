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
printf("input fname:");
char a[LINE];
scanf("%s",a);
FILE *fp=fopen(a,"r"),*fq;
if(fp==NULL)	
	{		
	printf("cannot find the file\n");		
	return;	
	}	
p=(struct text*)malloc(sizeof(struct text));
w=(struct text*)malloc(sizeof(struct text));
fgets(p->textline,LINE,fp);
p->next=head;w->next=p;head=w;
p=(struct text*)malloc(sizeof(struct text));
while(fgets(p->textline,LINE,fp))
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
printf("input outputfname:");
char b[LINE];
scanf("%s",b);
fq=fopen(b,"w+");
while(q)
{
 fprintf(fq,"%s",q->textline);
 q=q->next;
}
fclose(fp);
}
