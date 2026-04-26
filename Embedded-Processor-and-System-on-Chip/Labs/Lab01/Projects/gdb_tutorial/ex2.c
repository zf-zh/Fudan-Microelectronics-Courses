#include <stdio.h>
#include <stdlib.h>
#define N (5)

struct Node
{
    int value;
    struct Node *next;
};

int main()
{
    srand(1);
    struct Node *head=NULL,*tail=NULL;
    for(int i=0; i<N; i++)
    {
        struct Node *ptr = (struct Node*)malloc(sizeof(struct Node));
        ptr->value = rand()%100;
        ptr->next = NULL;
        if(head==NULL)
        {
            head=tail=ptr;
        }
        else
        {
            tail=tail->next=ptr;
        }
        printf("Node %d established.\n",i);
    }
    return 0;
}
