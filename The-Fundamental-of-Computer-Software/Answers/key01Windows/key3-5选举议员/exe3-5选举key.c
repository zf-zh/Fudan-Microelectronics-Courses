/*	File: 选举key.c
	【习题3-5】选举议员(elect senator)的程序	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define C struct candidate
#define ERROR(S) 	{printf(S); exit(0);}
C
{
	char  name[20];
	int   code, vote;
	C *next	/*   (1)   */; 
};
C  * Head = NULL;
int getCandidate(FILE * fp)
{ 
	C * candidate;
	char name[20];
	int nCandidate = 0, code;
	while(fscanf(fp, "%s%d", name, &code) != EOF)
	{
		if( (candidate = (C *)malloc(sizeof(C))) == NULL	/*   (2)   */ ) 
			ERROR("no space for candidate\n"); 
		strcpy(candidate->name, name);
		candidate->code = code;
		candidate->vote = -1;
		candidate->next = Head;		/*   (3)   */
		Head = candidate;			/*   (3)   */
		nCandidate ++;
	}
	return(nCandidate); 	/*   (4)   */
}
void getVote(FILE * fp, int * nSenator)	/*   (5)   */
{
	C * candidate;
	int code;
	fscanf(fp, "%d", nSenator); 	/*   (6)   */
	while(fscanf(fp, "%d", &code) != EOF)
	{
		for( candidate=Head; candidate; candidate=candidate->next	/*   (7)   */ ) 
		if(code == candidate->code)
		{
			candidate->vote += (candidate->vote < 0) ? 2 : 1	/*   (8)   */ ; 
			break;
		}
	}
}
C * electSenator(candidate)
C * candidate;
{ 
	int maxVote = 0;
	C * senator;
	senator = NULL;
	for( ; candidate; candidate=candidate->next) 	/*   (9)   */
		if(candidate->vote > maxVote)
		{
			senator = candidate;	/*   (10)   */ 
			maxVote = senator->vote;
		}
	if(senator)	/*   (11)   */
		senator->vote = -senator->vote ;
	else
		ERROR("cannot elect senator.\n"); 
	return(senator);
}
main()
{
	int i, nSenator, nCandidate;
	C * senator;
	FILE *fpVote, *fpCandidate;
	if((fpVote = fopen("vote.txt", "r")) == NULL ||
		 !(fpCandidate = fopen("candidate.txt", "r")) )
		ERROR("cannot open files.\n"); 
	nCandidate = getCandidate(fpCandidate);	/*    (12)   */
	getVote(fpVote, &nSenator);	/*   (13)   */
	if(nSenator >= nCandidate)
		ERROR("invalid election\n"); 
	printf("nS=%d nC=%d\n", nSenator, nCandidate);
	for(i=0; i<nSenator; i++)
		if((senator = electSenator(Head)) != NULL)
			printf("NAME=%-20s CODE=%-5d VOTE=%d\n", 
			senator->name, senator->code, -senator->vote);	/*   (14)   */ 
	system("pause");
}
/*
nS=3 nC=25
NAME=wei_xu               CODE=5     VOTE=12
NAME=LingliWang           CODE=10    VOTE=8
NAME=HengliangZhu         CODE=9     VOTE=6

nS=6 nC=25
NAME=wei_xu               CODE=5     VOTE=12
NAME=LingliWang           CODE=10    VOTE=8
NAME=HengliangZhu         CODE=9     VOTE=6
NAME=jmlai                CODE=2     VOTE=5
NAME=yanch                CODE=23    VOTE=4
NAME=Jackson              CODE=20    VOTE=4
*/
