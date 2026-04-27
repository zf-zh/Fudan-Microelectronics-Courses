/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<ctype.h>

/* data definition	*/
#define L 80
#define M 100
#define TEXT struct text
TEXT
{
	char *text;
	TEXT *next;
};
typedef char STRING[30];
	FILE *inFp,*outFp;
int compare(char *textA, char *textB)
{
	int cmp;
	while((cmp = *textA - *textB) == 0)
	{
		if(!*textA || !*textB) 
			break;
		textA++;
		textB++;
	}
	return(cmp);
}

void insert(TEXT *head)
{
  TEXT *unsort, *now, *node;
  if(head->next==NULL || head->next->next==NULL)
	  return;
  unsort = head->next->next;
   head->next->next = NULL;
   while(unsort) 
   {  
	   now = unsort;    
	   unsort = now->next;  
	   for(node=head; node->next; node=node->next)  
		   if( compare(now->text, node->next->text) <= 0 )
			   break; 
	   now->next = node->next;      
	   node->next = now; 
   }
}
/* read text from infile		*/
/* store each line as request	*/
TEXT *readFile( )
{
	int k=0,len;
	char string[M];
	STRING inFile;
	TEXT *head,*node;
	if((head = (TEXT *)malloc(sizeof(TEXT))) == NULL)
		exit(0);
	head->next = NULL; 
	printf("input file name: ");
	scanf("%s", inFile);
	if((inFp = fopen(inFile, "r")) == NULL)
	{
		printf("cannot open %s\n", inFile);
		system("pause");
		exit(0);
	}
	for(;k<L;k++)
	{
		if((node = (TEXT *)malloc(sizeof(TEXT)) ) == NULL)
			exit(0);

		if(fgets(string,M,inFp)==NULL)
			break;
		if((len = strlen(string)) <= 0)
			break;
		if( (node->text=(char *)malloc(sizeof(char) * len)) == NULL)
			exit(0); 
	strcpy(node->text,string);
		node->next = head->next;	
		head->next = node;
	}
	insert(head);
	return head;

}

/* write the sorted text to outfile		*/
void writeFile(TEXT *head )
{
	TEXT *node;
	STRING outFile;
	printf("output file name: ");
	scanf("%s", outFile);
	if((outFp= fopen(outFile, "w")) == NULL)
		exit(0);
	for(node=head->next; node; node=node->next)
		fprintf(outFp,"%s", node->text);
}

int main()
{
	TEXT *head;
	head=readFile();
	writeFile(head);
}

