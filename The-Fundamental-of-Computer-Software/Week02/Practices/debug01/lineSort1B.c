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
FILE *inFP,*outFP;
/* read text from infile		*/
/* store each line as request	*/
TEXT* readFile( )
{
	TEXT *p=NULL,*q=NULL,*fp=NULL;
	int i;
	while(fgetc(inFP)!=-1)
	{
		p=(TEXT*)malloc(sizeof(TEXT));
		if(fp==NULL)
			fp=p;
		for(i=0;i<LINE;i++)
		if((p->textline[i]=fgetc(inFP))=='\n')
			break;
		p->next=NULL;
		if(q==NULL)q=p;
		else{
			q->next=p;
		    q=p;
		}
	}
	return fp;
}

/* write the sorted text to outfile		*/
void writeFile( TEXT *fp,FILE *outFP)
{
	TEXT *p;
	for(p=fp;p;p=p->next)
	{int i;
		for(i=0;p->textline[i]!='\n';i++)
			fputc(p->textline[i],outFP);
		fputc('\n',outFP);
	}
	printf("over");
	return;


}

int main()
{
	TEXT *fp,*fp1,*fp2,*fp3,*fp4;
	char inFile[40],outFile[40];
	printf("input file name\n");
	scanf("%s%*c",inFile);
    printf("output file name\n");
	scanf("%s%*c",outFile);
	if((inFP=fopen(inFile,"r"))==NULL)
	{
		printf("cannot open file %s!\n",inFile);
		return 0;
	}
	fp=readFile();
	for(fp1=fp,fp2=NULL;fp1;)
	{
		for(fp3=fp,fp4=NULL;fp3->textline[0]<fp1->textline[0];fp4=fp3,fp3=fp3->next);
		if(fp3==fp1){
			fp2=fp1;
			fp1=fp1->next;
			continue;
		}
		else
		{fp2->next=fp1->next;
		if(fp4==NULL){
			fp=fp1;
			fp->next=fp3;
			fp1=fp2->next;
			continue;
		}
		else
		{fp4->next=fp1;
		fp1->next=fp3;
		fp1=fp2->next;
		continue;
		}
		}
	}
	outFP=fopen(outFile,"w");
	writeFile(fp,outFP);
}



