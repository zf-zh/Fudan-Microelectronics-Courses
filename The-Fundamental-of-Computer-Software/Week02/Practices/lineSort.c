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
TEXT *readFile(FILE *fp)
{
	char buf[LINE];
	/* ----------complete program----------	*/

	// Dummy head
	TEXT *head = (TEXT *)malloc(sizeof(TEXT));
	head->next = NULL;
	TEXT *current = head;
	TEXT *tmp;

	// Read lines and insert into linked list in sorted order
	while (fgets(buf, LINE, fp)) {
		current = head;
		while (current->next != NULL && strcmp(current->next->textline, buf) < 0) {
			current = current->next;
		}

		tmp = (TEXT *)malloc(sizeof(TEXT));
		strcpy(tmp->textline, buf);
		tmp->next = current->next;
		current->next = tmp;
		
	}

	// Return the head of the sorted linked list
	return head;

	/* ------------------------------------	*/
}

/* write the sorted text to outfile		*/
void writeFile(FILE *fp, TEXT *head)
{
	/* ----------complete program----------	*/

    // Write sorted lines to output file
	for (
		TEXT *current = head->next;
		current != NULL;
		current = current->next
	) {
		fputs(current->textline, fp);
	}

	/* ------------------------------------	*/
}

int main()
{
	FILE *inFp, *outFp;
	TEXT *head=NULL;
	char outFile[20], inFile[20];

	/* ----------complete program----------	*/

	// Get input and output file names from user
	printf("input file name: ");
	scanf("%19s", inFile);
	printf("output file name: ");
	scanf("%19s", outFile);

	// Open input file
	inFp = fopen(inFile, "r");
	if (inFp == NULL) {
		fprintf(stderr, "Error opening input file \"%s.\"\n", inFile);
		return 1;
	}

	// Read lines from input file
	head = readFile(inFp);

	// Open output file
	outFp = fopen(outFile, "w");
	if (outFp == NULL) {
		fprintf(stderr, "Error opening output file \"%s.\"\n", outFile);
		return 1;
	}

	// Write sorted lines to output file
	writeFile(outFp, head);

	// Close the files
	fclose(inFp);
	fclose(outFp);

	return 0;

	/* ------------------------------------	*/

}

/*
inFileA.txt
outFileA.txt

inFileB.txt
outFileB.txt
*/
