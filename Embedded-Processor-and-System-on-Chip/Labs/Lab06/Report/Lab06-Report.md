---
title: "Computer Architecture Lab 06 Report"
author: "张兆飞"
date: 2026-04-18
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


# 实验6 SMART 平台介绍与仿真

## 1. 实验目的

通过在 SMART 平台上进行程序仿真, 了解和掌握 SMART 平台的主要功能和使用方式.


## 2. 实验步骤

### 2.1. 配置好 SMART 平台环境

1. **VNC 客户端连接**

    采用 Linux 平台下的开源软件 Remmina 连接到 SMART 平台的 VNC 服务器, 输入正确的 IP 地址和端口号, 成功连接后即可进入 SMART 平台的图形界面.

    ![VNC Client Configuration](./Resources/2.1/2.1-01-VNC-Client-Configuration.png){width=80%}

    ![VNC Connection Success](./Resources/2.1/2.1-02-VNC-Connection-Success.png){width=80%}

2. **SMART 图形界面**

    配置环境变量并切换到指定目录后, 打开图形界面.

    ![SMART Graphical Interface](./Resources/2.1/2.1-03-SMART-Graphical-Interface.png){width=80%}

3. **命令行 `ssh` 连接**

    为方便操作, 同时通过 `ssh` 连接到跳板机, 再通过 `telnet` 连接到 SMART 平台所在的服务器.

    ![SSH Connection](./Resources/2.1/2.1-04-SSH-Connection.png){width=80%}

### 2.2. 仿真各例程

1. **仿真 Dhrystone 程序**

    在图形界面处点击 `run_dhry`, 相当于在 `workdir/` 目录下执行 `../tools/run_case ../case/dhry/Main.c -dump` 命令.

    ![Run Dhrystone Program](./Resources/2.2/2.2-01-Run-Dhrystone-Program.png){width=80%}

    等待十余分钟后查看 `run.log` 文件中的结果.

    ![Dhrystone Program Result 1](./Resources/2.2/2.2-02-Dhrystone-Program-Result-1.png){width=80%}

    ![Dhrystone Program Result 2](./Resources/2.2/2.2-03-Dhrystone-Program-Result-2.png){width=80%}

2. **仿真 memory 读写调试程序**

    在图形界面处点击 `run debug mem test`, 相当于在 `workdir/` 目录下执行 `../tools/run_case ../case/dhry/Main.c -dump -debug_mem` 命令.

    ![Run Memory Debug Program](./Resources/2.2/2.2-04-Run-Memory-Debug-Program.png){width=80%}

    等待数十秒后查看 `run.log` 文件中的结果.

    ![Memory Debug Program Result 1](./Resources/2.2/2.2-05-Memory-Debug-Program-Result-1.png){width=80%}

    ![Memory Debug Program Result 2](./Resources/2.2/2.2-06-Memory-Debug-Program-Result-2.png){width=80%}

3. **仿真 gpr 读写调试程序**

    在图形界面处点击 `run debug gpr test`, 相当于在 `workdir/` 目录下执行 `../tools/run_case ../case/dhry/Main.c -dump -debug_gpr` 命令.

    ![Run GPR Debug Program](./Resources/2.2/2.2-07-Run-GPR-Debug-Program.png){width=80%}

    等待数十秒后查看 `run.log` 文件中的结果.

    ![GPR Debug Program Result 1](./Resources/2.2/2.2-08-GPR-Debug-Program-Result-1.png){width=80%}

    ![GPR Debug Program Result 2](./Resources/2.2/2.2-09-GPR-Debug-Program-Result-2.png){width=80%}

4. **仿真 PLIC 的中断测试程序**

    在图形界面处点击 `run_int_case`, 相当于在 `workdir/` 目录下执行 `../tools/run_case ../case/Interrupt/ct_plic_int_smoke.s -dump` 命令.

    ![Run Interrupt Test Program](./Resources/2.2/2.2-10-Run-Interrupt-Test-Program.png){width=80%}

    等待数十秒后查看 `run.log` 文件中的结果.

    ![Interrupt Test Program Result 1](./Resources/2.2/2.2-11-Interrupt-Test-Program-Result-1.png){width=80%}

    ![Interrupt Test Program Result 2](./Resources/2.2/2.2-12-Interrupt-Test-Program-Result-2.png){width=80%}


### 2.3. 自行编写 C 程序并执行

1. **编写快速排序程序**

    编写 `case/quick_sort/quick_sort.c` 程序, 实现快速排序算法.

    ```C
    #include <stdio.h>
    
    void Swap(int* a, int* b) {
      int temp = *a;
      *a = *b;
      *b = temp;
    }
    
    int Partition(int* arr, int low, int high) {
      int pivot = arr[high];
      int i = low - 1;
    
      for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
          ++i;
          Swap(&arr[i], &arr[j]);
        }
      }
      
      Swap(&arr[i + 1], &arr[high]);
      return i + 1;
    }
    
    void QuickSort(int* arr, int low, int high) {
      if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
      }
    }
    
    void PrintArray(const int* arr, int size) {
      for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
      }
      printf("\n");
    }
    
    int main() {
      int data[] = {8, 7, 2, 1, 0, 9, 6};
      int size = sizeof(data) / sizeof(data[0]);
    
      printf("Unsorted: ");
      PrintArray(data, size);
    
      if (size > 0) {
        QuickSort(data, 0, size - 1);
      }
    
      printf("Sorted:   ");
      PrintArray(data, size);
    
      return 0;
    }
    
    ```

2. **仿真快速排序程序**

    在 `workdir/` 目录下执行 `../tools/run_case ../case/quick_sort/quick_sort.c` 命令.

    ![Run Quick Sort Program](./Resources/2.3/2.3-01-Run-Quick-Sort-Program.png){width=80%}

    等待数十秒后查看 `run.log` 文件中的结果.

    ![Quick Sort Program Result 1](./Resources/2.3/2.3-02-Quick-Sort-Program-Result-1.png){width=80%}

    ![Quick Sort Program Result 2](./Resources/2.3/2.3-03-Quick-Sort-Program-Result-2.png){width=80%}


## 3. 实验分析与总结

本次实验通过在 SMART 平台上进行程序仿真, 深入了解了该平台的主要功能和使用方式.

通过仿真 Dhrystone 程序, 了解了 SMART 平台的性能指标和运行效率. 通过仿真 memory 和 gpr 读写调试程序, 熟悉了 SMART 平台的调试功能和内存访问机制. 通过仿真 PLIC 的中断测试程序, 掌握了 SMART 平台的中断处理机制. 最后, 通过自行编写并仿真快速排序程序, 加深了对 SMART 平台的理解和应用能力.


## 4. 实验收获与建议

通过本次实验, 不仅掌握了 SMART 平台的使用方法, 还加深了对计算机体系结构和程序仿真的理解.

建议完善实验提供的源代码和 C Shell 配置文件, 减少各种报错带来的困扰.

