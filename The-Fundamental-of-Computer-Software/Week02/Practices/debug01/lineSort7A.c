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
struct text *readFile(char inFile[])
{
	FILE *inFp;
	struct text *head;
	fopen_s(&inFp, inFile, "r");
	head = NULL;
	struct text *q = NULL;
	struct text *p = NULL;
	char temp[100];
	while (fgets(temp, LINE, inFp) != NULL){
		p = (text *)malloc(sizeof(text));
		strcpy_s(p->textline, temp);
		if (head == NULL)
			head = p;
		else
			q->next = p;
		q = p;
	}
	p->next = NULL;


	return head;
}

int strtcmp(char str1[], char str2[])
{
	int wn = 0;
	while (1){
		if (str1[wn] == str2[wn] && str1[wn] != '\0'&&str2[wn] != '\0')
			wn++;
		else{
			if (str1[wn] != '\0'&&str2[wn] != '\0')
				return str1[wn] > str2[wn] ? 1 : -1;
			else{
				if (str1[wn] == '\0'&&str2[wn] != '\0')
					return -1;
				if (str1[wn] != '\0'&&str2[wn] == '\0')
					return 1;
				if (str1[wn] == '\0'&&str2[wn] == '\0')
					return 0;
			}
		}
	}
}
void sort(struct text *head)
{
	struct text *f, *p, *a, *b;
	f = NULL;
	if (head->next == NULL || head->next->next == NULL)
	{
		return;
	}
	while (f != head->next->next)
	{
		for (p = head; p->next->next != f; p = p->next)
		{
			if (strtcmp(p->next->textline, p->next->next->textline) == 1)
			{
				a = p->next;
				b = p->next->next;
				p->next = b;
				a->next = b->next;
				b->next = a;
			}
		}
		f = p->next;
	}
}
/* write the sorted text to outfile		*/
void writeFile(text *head, char outFile[])
{
	FILE *outFp;
	fopen_s(&outFp, outFile, "w");
	sort(head);
	text *l = head->next;
	while (l){
		printf("%s", l->textline);
		fputs(l->textline, outFp);
		l = l->next;
	}

}

int main()
{
	char inFile[50];
	char outFile[50];
	printf_s("input file name£º");
	scanf_s("%s", inFile, 50);
	printf_s("output file name£º");
	scanf_s("%s", outFile, 50);
	FILE *inFp;
	text *head = NULL;
	head = readFile(inFile);
	writeFile(head, outFile);
	return 0;
}

