---
title: "Computer Architecture Lab 04 Report"
author: "张兆飞"
date: 2026-04-03
lang: zh-CN
mainfont: "Times New Roman"
CJKmainfont: "Songti SC"
monofont: "Roboto Mono"
geometry:
  - top=2cm
  - bottom=2cm
  - left=2cm
  - right=2cm
header-includes:
  - \usepackage{float}
  - \floatplacement{figure}{H}
---


# 实验4 RISC-V 汇编程序编程练习

## 1. 实验目的

通过编写和运行 RISC-V 汇编程序, 熟悉 RISC-V 基本指令集中的指令, RISC-V 汇编的编程规范, 了解递归函数的调用过程.


## 2. 实验步骤

### 2.1. 使用 RV64I 指令集编写 32 位整数乘法函数 `mymul`

使用循环, 通过不断移位和加法来实现乘法运算. 该函数接受两个参数, 分别存储在 `a0` 和 `a1` 寄存器中, 返回结果存储在 `a0` 寄存器中.

![Source Code of `mymul`](./Resources/2.1/2.1-01-Source-Code-of-mymul.png){width=70%}

### 2.2. 使用 RV64I 指令集和 `mymul` 函数实现自然数阶乘函数 `myfac`

使用递归的方式实现阶乘函数, 输入为 0 时为 base case. 当输入大于 0 时, 通过递归调用 `myfac` 来计算阶乘, 并使用 `mymul` 来计算当前数与递归结果的乘积.

![Source Code of `myfac`](./Resources/2.2/2.2-01-Source-Code-of-myfac.png){width=70%}

### 2.3. 编译和测试结果

编译后直接运行, 与预期结果完全一致.

![Output of `mymul` and `myfac`](./Resources/2.3/2.3-01-Output-of-mymul-and-myfac.png){width=72%}

## 3. 实验分析与总结

通过本次实验, 熟悉了 RISC-V 汇编语言的基本语法和指令使用, 了解了递归函数的调用过程以及如何在汇编中实现递归. 在编写 `mymul` 函数时, 通过不断移位和加法来实现乘法运算, 加深了对位运算的理解. 在实现 `myfac` 函数时, 通过递归调用来计算阶乘, 加深了对递归算法的理解. 实验结果与预期完全一致, 验证了代码的正确性.

## 4. 实验收获与建议

本次实验锻炼了使用 RISC-V 汇编语言进行编程的能力, 加深了对 RISC-V 指令集和计算机体系结构的理解, 这对于软件开发和硬件设计都有重要的意义. 在编写汇编代码时, 熟悉了寄存器的使用和函数调用约定, 有利于确保代码的正确性和可维护性.

源代码中 `mymul` 作为 leaf function, 并不需要保存 `ra` 寄存器, 也不一定使用 `s0` 寄存器, 因此可以去除其代码中相关的保存和恢复指令. 此外, 也可以考虑在源代码中采用空格而非制表符进行缩进, 以确保在不同编辑器中保持一致的格式, 也更符合现代编程实践.

