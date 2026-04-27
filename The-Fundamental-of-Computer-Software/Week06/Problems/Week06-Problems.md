---
title: "第二章 Linux 系统的软件开发工具"
author: "张兆飞"
date: 2026-04-10
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


# 第六周 习题

## 2-3. 运行 `sed` 命令, 写出运行效果.

### 2-3-1. 已知文件 `file` 如下:

```text
if more, if better
```

写出执行以下命令的结果

```bash
$ sed 's/if/the/g' file
```

输出到 `stdout` 的结果是:

```text
the more, the better
```

### 2-3-2. 已知文件 `file` 如下:

```text
a
bcd
ef
```

写出执行以下命令的结果

```bash
$ sed 's/.*/mv & &.old/' file
```

输出到 `stdout` 的结果是:

```bash
mv a a.old
mv bcd bcd.old
mv ef ef.old
```

### 2-3-3. 已知文件 `file` 如下:

```C
S *First = NULL;
void error(format, string)
char *format, *string;
```

如需输出以下信息:

```C
S *First = NULL;
void error(format, str)
char *format, *str;
```

请写出 `sed` 命令.

```bash
$ sed 's/string/str/g' file
```

### 2-3-4. 已知文件 `file` 如下:

```text
0. print 1 line
10. input 10 file
2. output 1 file
1. input 1 file
```

如执行一条 sed 命令后输出以下信息:

```text
0. print 1 line
2. output 1 file
```

请写出 `sed` 命令.

```bash
$ sed '/input/d' file
```


## 2-4. 请按以下要求写出 `sed` 命令.

### 2-4-1. 删除第 8 行到最后一行的内容.

```bash
$ sed '8,$d' file
```

### 2-4-2. 将所有的字符 `A` 替换为 `B`, 并且删除所有行首的字符串 `xyz`.

```bash
$ sed 's/A/B/g; s/^xyz//' file
```

### 2-4-3. 在行首插入一个制表符.

```bash
$ sed 's/^/\t/' file
```

### 2-4-4. 在行尾添加字符串 `###`.

```bash
$ sed 's/$/###/' file
```

### 2-4-5. 删除行尾的反斜杠. 

```bash
$ sed 's/\\$//' file
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

### 2-6-1. 写出可以产生以上输出结果的 `sed` 命令

```bash
$ sed 's/\(.*\) \(.*\)/mv \2 \1/' file
```

