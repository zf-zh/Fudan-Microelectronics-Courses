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
TEXT *readFile(char inFile[])
{ FILE *inFp;int i=0;int ch;TEXT *p,*tail,*h;char infile[100];
h=tail=NULL;ch=0;
   if((inFp=fopen(inFile,"r"))==NULL)
	{
		   printf("cannot open file.\n");

	}
   else 
   { for(;ch!=EOF;)
    {  p=(TEXT*)malloc(sizeof(TEXT));
	   p->next=NULL;
	   if(h==NULL) { h=tail=p;}
	   else { tail=tail->next=p;}

        while(((ch=fgetc(inFp))!=(int)'\n')&&(ch!=EOF) )  
		{  p->textline[i]=(char)ch;i++;}
		p->textline[i]='\0';
		
       i=0;
	}
  
   }
   fclose(inFp);
   return h;

}

/* write the sorted text to outfile		*/
void writeFile(char outFile[],TEXT *h)
{ FILE *outFp;TEXT *p;
  p=h;
    if((outFp=fopen(outFile,"w"))==NULL)
	{
		   printf("cannot open file.\n");

	}
	while((p)&&(fputs(p->textline,outFp)!=EOF))
	{
		fputc('\n',outFp);
		p=p->next;

	}
}

int main()
{ 	char inFile[100],outFile[100];int i=0,count=0;
  TEXT *head,*q,*p,*w;char chazhao[100];
  printf("input file name£º");
  scanf("%s",inFile);
  printf("output file name£º");
  scanf("%s",outFile);
  head=readFile(inFile);
  
  p=head;
  while(p)
  { 
	  printf("%s",p->textline);
		 printf("\n");
	  p=p->next;  
	  	 count++;

  }/* check all text in chain	*/

  for(i=0;i<count-1;i++)
  { q=head;p=head->next;w=NULL;
     while(p)
	 {
		 if(strcmp(q->textline,p->textline)>0)
			 if(q==head) { head=p;q->next=p->next;p->next=q;w=head;p=q->next;}
			 else { w->next=p;q->next=p->next;p->next=q;w=p;p=q->next;}
		 else
		 {
			 w=q;p=p->next;q=q->next;
		 }
	 }


  } /* sort	*/
  
  p=head;

   while(p)
  { 
	  printf("%s",p->textline);
		 printf("\n");
	  p=p->next;  

  }/* check sorted chain	*/
   

 writeFile(outFile,head);
  system("pause");
}

