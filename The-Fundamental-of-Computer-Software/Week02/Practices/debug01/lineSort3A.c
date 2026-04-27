/*	lineSort.c	*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* data definition	*/
#define LINE 80
#define TEXT struct text
TEXT {
	char textline[LINE];
	TEXT *next;
};

TEXT *head;

/* read text from infile		*/
/* store each line as request	*/
void readFile() {
	char inFile[LINE], line[LINE];
	TEXT *p;
	printf("input file name: ");
	scanf("%s", inFile);
	FILE *inFp;
	inFp = fopen(inFile, "r");
	while (fgets(line, LINE, inFp)) {
		if (line == "") break;
		p = (TEXT *)malloc(sizeof(TEXT));
		strcpy(p -> textline, line);
		p -> next = head -> next;
		head -> next = p;
	}
}

/* write the sorted text to outfile		*/
void writeFile(TEXT *h) {
	char outFile[LINE];
	printf("output file name: ");
	scanf("%s", outFile);
	FILE  *outFp;
	outFp = fopen(outFile, "w");
	while ((h = h -> next) != NULL)
		fprintf(outFp, "%s", h -> textline);
}

int main() {
	head = (TEXT *)malloc(sizeof(TEXT));
	head -> next = NULL;
	readFile();
	int c = 0;
	TEXT *h = head, *tail, *p, *q, *r, *t;
	for (tail = NULL; h -> next != tail; tail = p) {
		for (q = h; q -> next -> next != tail; q = q -> next) {
			r = q -> next;
			//printf("#%d: %s\n%s\n%s\n==========\n", ++ c, t -> textline, r -> textline, r -> next -> textline);
			if (strcmp(r -> textline, r -> next -> textline) == 1) {
				t = r -> next;
				r -> next = t -> next;
				t -> next = r;
				q -> next = t;
			}
		}
		p = q -> next;
	}
	writeFile(h);
	return 0;
}
