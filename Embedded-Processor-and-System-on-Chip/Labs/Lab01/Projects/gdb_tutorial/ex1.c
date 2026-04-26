#include <stdio.h>
#include <stdlib.h>

#define N (123)
#define INT_MAX (0x7fffffff)

int main(int argc, char **argv)
{
    srand(1);
    int sum = 0;
    for(int i=1;i<INT_MAX;i++)
    {
        sum+=rand()%1000;
        if(argc>=2 && i==N && sum==atoi(argv[1]))   //atoi:字符串转int
        {
            printf("Test Pass!\n"); 
            return 0;
        }
    }
    
    printf("Test Fail!\n"); 
    return 1;
}
