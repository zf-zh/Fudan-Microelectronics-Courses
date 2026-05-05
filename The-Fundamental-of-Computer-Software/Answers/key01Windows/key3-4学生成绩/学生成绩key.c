/*	File: 学生成绩key.c
	【习题3-4】统计学生成绩的程序	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define S struct student
S 
{
	char * name;
	float  math, phys;
	S *  next;
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
	fp = fopen(file, "r");	/*   (1)    */
	if(fp == NULL)
		error("cannot open file %s\n", file);
	while(fscanf(fp, "%s%f%f", name, &math, &phys) == 3)
	{
		student = (S *)malloc(sizeof(S));	/*   (2)   */
		if(student == NULL)
			error("no space for student\n", NULL);
		student->name = (char *)malloc(strlen(name)+1);	/*   (3)   */
		if(student->name == NULL)
			error("no space for name\n", NULL);
		strcpy(student->name, name);
		student->math = math;
		student->phys = phys;
		student->next = First; First = student;	/*   (4)   */
	}
}
int getscore(char *name, float *sum, float *average)	/*   (5)  */
{
	S *student;
	for(student=First; student!=NULL; student=student->next)
	if(strcmp(name, student->name) == 0)
	{
		*sum = student->math + student->phys;	/*   (6)   */
		*average = *sum * 0.5;	/*   (7)   */
		return(0);
	}
	return(-1);
}
int getnum()
{
	int number = 0;
	S *s;
	for(s=First; s; s=s->next)	/*	(8)   */
		number++;
	return(number);
}
main(int argc, char *argv[])
{
	char name[20], task[10];
	int number, found;
	float sum, average;
	input("student.txt");
	printf("what task [number or student]? ");
	while(scanf("%s", task) > 0)
	{
		switch(task[0])
		{
			case 'n': number = getnum();	 /*  (9)   */
				printf("total student number = %d\n", number);
				break;
			case 's': printf("who? ");
				scanf("%s", name);
				found = getscore(name, &sum, &average);	/*  (10)   */
				if(found == 0)
				{
					printf("student: %s  ",name);
					printf("sum= %8.3f  ", sum);
					printf("average= %8.3f\n", average);
				}
				else
					printf("not found %s\n", name);
				break;
			default:  printf("invalid task\n");
		}
		printf("what task [number or student]? ");
	}
}
/*
what task [number or student]? n
total student number = 32
what task [number or student]? s
who? 丁毅岭
student: 丁毅岭  sum=  165.500  average=   82.750
what task [number or student]? s
who? 孙慧盈
student: 孙慧盈  sum=  160.500  average=   80.250
what task [number or student]? ^Z
*/
