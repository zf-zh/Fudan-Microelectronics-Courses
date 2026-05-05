---
title: "第二章 Linux 系统的软件开发工具"
author: "张兆飞"
date: 2026-05-05
lang: zh-CN
mainfont: "Times New Roman"
CJKmainfont: "Songti SC"
monofont: "Roboto Mono"
geometry:
  - top=2cm
  - bottom=2cm
  - left=2cm
  - right=2cm
---


# 第八周 习题

## 3-1. 数组, 指针和地址. 已知变量定义语句为

```C
int a[10], *p, *q, **pp;
```

假设已有数组元素 `a[i]=10*i`, 每个元素占内存单元 4 个字节, 并有语句

```C
p = a + 1;
q = a + 8;
pp = &p;
```

试回答下列表达式的值

| **题目** | **答案** | **题目** | **答案** | **题目** | **答案** |
| :--- | :--- | :--- | :--- | :--- | :--- |
| (1) `a[0]` | 0 | (6) `*q` | 80 | (11) `*(p+2*3)` | 70 |
| (2) `*(a+3)` | 30 | (7) `a[q-p]` | 70 | (12) `*(p+4)*(*(q-2))` | 3000 |
| (3) `a[3]` | 30 | (8) `a[(q-p)/3]` | 20 | (13) `*((*pp)+5)` | 60 |
| (4) `q-p` | 7 | (9) `a[(q-p)/4]` | 10 | (14) `**pp+5` | 15 |
| (5) `*p` | 10 | (10) `*(q-2)` | 60 | (15) `&a[3]-&a[0]` | 3 |


## 3-6. 以下是计算逆波兰表达式的程序. 若在程序运行中键入的逆波兰表达式为:

```
4 8 9 7 - + x #     表示 4 * (8 + (9 - 7))
```

其中 `#` 是结束符. 试读该程序, 并在_______处填写适当的内容.

```C
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define maxlen 50

int pointer=0, stack[maxlen], c[10];

void push(int value)
{
    stack[++pointer] = value;
}

int pop()
{
    return(stack[pointer--]);
}

main()
{
    int ch, i=0, j, result, data1, data2;
    printf("expression: ");
    while((ch = getchar()) != '#')
    {
        if(isdigit(ch))
            push(ch - '0');
        else if(isspace(ch))
            continue;
        else
        {
            data1 = pop();
            data2 = pop();
            switch(ch)
            {
                case '+': result = data2 + data1; break;
                case '-': result = data2 - data1; break;
                case 'x': result = data2 * data1; break;
            }
            c[i] = result;
            i++;
            push(result);
        }
    }
    for(j=0; j<i; j++)
        printf("c[%d] = %d\n", j+1, c[j]);
}
```

程序运行的信息为

```
expression: 4 8 9 7 1 4 5 7 2 8 - + x + - x + - + #
c[1] = -6
c[2] = 1
c[3] = 5
c[4] = 9
c[5] = -8
c[6] = -56
c[7] = -47
c[8] = 55
c[9] = 59
```

