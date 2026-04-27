/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

/* data definition	*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};
/* write the sorted text to outfile		*/
void writeFile(text *head,char of1[LINE])
{
	struct text  *p;
	FILE *outFp;
	outFp=fopen(of1,"w");
	p=head;
    while(p->next!=NULL){
	fputs (p->textline, outFp);
	p=p->next;
    }
}
/* read text from infile		*/
/* store each line as request	*/
void readFile(FILE *fp1,char of1[LINE])
{
  struct text *head, *p, *p2, *p3,*p4;
  int temp1,row1=1,i1,i2,i3;
  char temp2[LINE],temp3[LINE]; 
  while((temp1 = fgetc(fp1)) != EOF){  
	  if(temp1 == '\n')row1++; }
  rewind(fp1);
  head=NULL;

  for(i1=0;i1<row1;i1++){
    fgets (temp2, LINE, fp1);
    p=(text *)malloc(sizeof(text));
	strcpy(p->textline,temp2);
    if(i1==0){head=p;}else{p2->next=p;}
    p2=p;
	p->next=NULL;
  }
	
	p2=head;
    while(p2->next!=NULL){
	printf("%s \n",p2->textline);
	p2=p2->next;
    }

	for(p3=head;p3!=NULL;p3=p3->next){
		for(p4=p3->next;p4!=NULL;p4=p4->next){
			if(p3->textline[0]>p4->textline[0]){
				strcpy(temp3,p4->textline);
				strcpy(p4->textline,p3->textline);
				strcpy(p3->textline,temp3);
				}
		}
	}
	fclose(fp1);
	writeFile(head,of1);
}

void wait_1(long wait_time){
	for(long i_1=0;i_1<(wait_time*10000000);i_1++){
		if(i_1%10000000){
		}else{
		printf(">");
		}
	}

}
int main()
{
	char inFile[LINE],outFile[LINE];
	FILE *inFp;
	text *head1;
	printf("input file name: ");
	scanf("%s",&inFile);
	while(!(inFp=fopen(inFile,"r"))){
		printf("file not exist");
		wait_1(20);
		system("CLS");
	    printf("input file name£º");
	    scanf("%s",&inFile);
	}
	    printf("output file name£º");
	    scanf("%s",&outFile);
	readFile(inFp,outFile);
	
	system("pause");//for VC2012 set
	
}





