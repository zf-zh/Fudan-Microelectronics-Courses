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
char inputfilename[LINE],outputfilename[LINE];
int choose(TEXT *p,TEXT *q)
{
	    int i=0;
		while((p->textline[i]!='\0')&&(q->textline[i]!='\0'))
		{
			if(p->textline[i]>q->textline[i])return 1;
			if(p->textline[i]<q->textline[i])return 0;
			i++;
		}
		return 0;
}
void print()
{
	   	TEXT *p=head;
	while (p!=NULL)
	{
		puts(p->textline);
		p=p->next;
	}

}
/* read text from infile		*/
/* store each line as request	*/
void readFile( )
{TEXT *p,*q;
 char inputfilename[LINE];
 int len=0,flag=0;
 printf("input file name£º");
 gets(inputfilename);
 freopen(inputfilename,"r",stdin);
 (TEXT*)p=(TEXT*)malloc(sizeof(TEXT));
 while(1)
 {
	 gets(p->textline);
	 if(p->textline[0]<65)  break;
	 if(flag==0)
	 {
		   head=p;
	 }
	 if(flag!=0)q->next=p;
	 q=p;
	 flag=1;
	 (TEXT*)p=(TEXT*)malloc(sizeof(TEXT));
 }
 q->next=NULL;
 //print();


}

/* write the sorted text to outfile		*/
void writeFile( )
{TEXT *q;
 int i;
 freopen(outputfilename,"w",stdout);
 q=head;
 while(q!=NULL)
 {
	 puts(q->textline);
	 q=q->next;
 }
}

void paixu()
{
	    TEXT *q,*p,*last,*last1;
		int i;
		char w[LINE];
		q=head;
		while(q->next!=NULL)
		{
			   p=q->next;
			   while (p!=NULL)
			   {
			   if(!choose(p,q))
			   {
				    for(i=0;i<=LINE;i++)
					{
						w[i]=p->textline[i];
						if(p->textline[i]=='\0')break;
					}
				for(i=0;i<=strlen(q->textline);i++)
					    p->textline[i]=q->textline[i];
				for(i=0;i<=strlen(w);i++)
					    q->textline[i]=w[i];
			   }
			   p=p->next;
			   }
			  q=q->next; 
		}
}


int main()
{
	readFile();
	paixu();
	writeFile();

}

