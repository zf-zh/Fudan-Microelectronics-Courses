#include <stdio.h>

#define S struct student
S
{
    char * name;
    float math, phys;
    S * next;
};
S *First = NULL;

void error(char *format, char *string)
{
    fprintf(stderr, format, string);
    exit(0);
}

void input(char *file)
{
    FILE *fopen(), *fp;
    S *student;
    char name[20];
    float math, phys;
    
    /* (1) */ fp = fopen(file, "r");
    if(fp == NULL)
        error("cannot open file %s\n", file);
        
    while(fscanf(fp, "%s%f%f", name, &math, &phys) == 3)
    {
        /* (2) */ student = (S *)malloc(sizeof(S));
        if(student == NULL)
            error("no space for student\n", NULL);
            
        /* (3) */ student->name = (char *)malloc(strlen(name)+1);
        if(student->name == NULL)
            error("no space for name\n", NULL);
            
        strcpy(student->name, name);
        student->math = math;
        student->phys = phys;
        
        /* (4) */ student->next = First; First = student;
    }
}

int getscore(char *name, /* (5) */ float *sum, float *average)
{
    S *student;
    for(student=First; student!=NULL; student=student->next)
        if(strcmp(name, student->name) == 0)
        {
            /* (6) */ *sum = student->math + student->phys;
            /* (7) */ *average = *sum / 2.0;
            return(0);
        }
    return(-1);
}

int getnum()
{
    int number = 0;
    S *s;
    for( /* (8) */ s=First; s!=NULL; s=s->next)
        number++;
    return(number);
}

main()
{
    char name[20], task[10];
    int number, found;
    float sum, average;
    
    input("student.txt");
    printf("what task [n|s(number or student)]? ");
    
    while(scanf("%s", task) > 0)
    {
        switch(task[0])
        {
            case 'n': 
                /* (9) */ number = getnum();
                printf("total student number = %d\n", number);
                break;
            case 's': 
                printf("who? ");
                scanf("%s", name);
                /* (10) */ found = getscore(name, &sum, &average);
                if(found == 0)
                {
                    printf("student: %s   ",name);
                    printf("sum= %8.3f   ", sum);
                    printf("average= %8.3f\n", average);
                }
                else
                    printf("not found %s\n", name);
                break;
            default:    
                printf("invalid task\n"); exit(0);
        }
        printf("what task [n|s(number or student)]? ");
    }
}
