---
title: "第二章 Linux 系统的软件开发工具"
author: "张兆飞"
date: 2026-04-20
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


# 第七周 习题

## 2-5. 请按以下要求写出的 `awk` 程序.

### 2-5-1. 删除第 8 行到最后一行的内容.

```bash
$ awk 'NR < 8' file
```

### 2-5-2. 删除所有的奇数行.

```bash
$ awk 'NR % 2 == 0' file
```

### 2-5-3. 在行首插入一个制表符.

```bash
$ awk '{print "\t", $0}' file
```

### 2-5-4. 在行尾添加字符串 `###`.

```bash
$ awk '{print $0, "###"}' file
```

### 2-5-5. 统计文件中词数大于 3 的行数以及文件的总行数.

```bash
$ awk 'NF > 3 {count++} END {print count, NR}' file
```


## 2-6. 已知文件 `file` 如下:

```text
a.a b.b
cc.c d.dd
ef.f g.hg
```

输出结果如下:

```bash
mv b.b a.a
mv d.dd cc.c
mv g.hg ef.f
```

### 2-6-2. 写出可以产生以上输出结果的 `awk` 命令

```bash
$ awk '{print "mv", $2, $1}' file
```


## 2-7. 已知文件 `file` 如下:

```text
F math
U phy why
D com what func real
A tech how key
N soft run
```

分别写出执行以下 `awk` 程序的输出结果.

### 2-7-1. `awk` 程序为

```bash
awk '
NR % 2 == 0 {print NR, NF, $0; n += 1 }
END  {printf "N = %d\n", n}' < file
```

输出到 `stdout` 的结果是:

```text
2 3 U phy why
4 4 A tech how key
N = 2
```

### 2-7-2. `awk` 程序为

```bash
awk '
NF > 3 {printf "%s -> %s\n", $0, $2;}' < file
```

输出到 `stdout` 的结果是:

```text
D com what func real -> com
A tech how key -> tech
```

