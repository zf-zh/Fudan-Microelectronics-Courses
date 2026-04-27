#include <stdio.h>

#define C struct candidate
#define ERROR(S) {printf(S); exit(0);}
C
{
    char name[20];
    int code, vote;
    /* (1) */ C *next;
};
C * Head = NULL;

int getCandidate(FILE * fp)
{
    C * candidate;
    char name[20];
    int nCandidate = 0, code;
    while(fscanf(fp, "%s%d", name, &code) != EOF)
    {
        if(/* (2) */ (candidate = (C *)malloc(sizeof(C))) == NULL)
            ERROR("no space for candidate\n");
        strcpy(candidate->name, name);
        candidate->code = code;
        candidate->vote = 0;
        /* (3) */ candidate->next = Head; Head = candidate;
        nCandidate ++;
    }
    return(/* (4) */ nCandidate);
}

void getVote(FILE * fp, /* (5) */ int *nSenator)
{
    C * candidate;
    int code;
    fscanf(fp, "%d", /* (6) */ nSenator);
    while(fscanf(fp, "%d", &code) != EOF)
    {
        for(/* (7) */ candidate = Head; candidate != NULL; candidate = candidate->next)
            if(code == candidate->code)
            {
                candidate->vote += /* (8) */ 1;
                break;
            }
    }
}

C * electSenator(C * candidate)
{
    int maxVote = 0;
    C * senator;
    senator = NULL;
    for(/* (9) */ candidate = Head; candidate != NULL; candidate = candidate->next)
        if(candidate->vote > maxVote)
        {
            /* (10) */ senator = candidate;
            maxVote = senator->vote;
        }
    if(/* (11) */ senator != NULL)
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
        
    nCandidate = /* (12) */ getCandidate(fpCandidate);
    /* (13) */ getVote(fpVote, &nSenator);
    
    if(nSenator >= nCandidate)
        ERROR("invalid election\n");
        
    printf("nS=%d nC=%d\n", nSenator, nCandidate);
    
    for(i=0; i<nSenator; i++)
        if((senator = electSenator(Head)) != NULL)
            printf("NAME=%-20s CODE=%-5d VOTE=%d\n", /* (14) */ senator->name, senator->code, -senator->vote);
}
