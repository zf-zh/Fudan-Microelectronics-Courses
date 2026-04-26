#include <stdio.h>
#include <stdlib.h>

int gcd_1(int,int);
int gcd_2(int,int);

int main(int argc, char **argv)
{   
    if(argc != 3)
    {
        printf("Two args needed.\n");
        return 1;
    }
    int input_a = atoi(argv[1]);	//atoi：字符串转int
    int input_b = atoi(argv[2]);

    int res_1 = gcd_1(input_a,input_b);
    printf("gcd(%d,%d) using algorithm 1 is: %d\n",input_a,input_b,res_1);

    int res_2 = gcd_2(input_a,input_b);
    printf("gcd(%d,%d) using algorithm 2 is: %d\n",input_a,input_b,res_2);
        
    return 0;   
}

int gcd_1(int a, int b) 	//辗转相除法
{
    if(a==0) return b;
    else if(b==0) return a;
    else if(a>b) return gcd_1(a%b,b);
    else return gcd_1(b%a,a);
}

int gcd_2(int a, int b) 	//更相减损法
{
    while(a!=b)
    {
        if(a>b) a = a - b;
        else b = b-a;
    }
    return a;
}

