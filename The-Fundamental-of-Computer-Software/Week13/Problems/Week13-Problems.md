---
title: "第四章 数据结构"
author: "张兆飞"
date: 2026-06-06
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


# 第十三周 习题

## 4-5. 已知一棵三次树按前序遍历的层号表示为:

1A, 2B, 3C, 3D, 2E, 3F, 4G, 4H, 4I, 3J

画出该树的图形, 写出该树的后序遍历.

```
       A
     /   \
    B     E
   / \   / \
  C   D F   J
       /|\
      G H I
```

后序遍历为 C, D, B, G, H, I, F, J, E, A.


## 4-6. 已知一棵三次树按后序遍历的层号表示为:

3C, 3F, 3D, 2B, 4G, 4H, 4I, 3J, 2E, 1A

画出该树的图形, 写出该树的前序遍历.

```
        A
      /   \
     B     E
   / | \    \
  C  F  D    J
           / | \
          G  H  I
```

前序遍历为 A, B, C, F, D, E, J, G, H, I.


## 4-7. 已知一棵二叉树按中序遍历的层号表示为:

2A, 4B, 3C, 1D, 3E, 4F, 2G, 3H, 4J

画出该树的图形, 写出该树的前序遍历和后序遍历.

```
     D
   /   \
  A     G
   \   / \
    C E   H
   /   \   \
  B     F   J
```

前序遍历为 D, A, C, B, G, E, F, H, J; 后序遍历为 B, C, A, F, E, J, H, G, D.


## 4-10. 已知一棵二叉树的前序表示和中序表示, 写出它的后序表示.

### 4-10-2. 前序表示为 DACBEFGJH, 中序表示为 CAEBDFJGH.

```
       D
     /   \
    A     F
   / \     \
  C   B     G
     /     / \
    E     J   H
```

后序表示为 C, E, B, A, J, H, G, F, D.


## 4-11. 已知一棵二叉树的中序表示和后序表示, 写出它的前序表示.

### 4-11-2. 中序表示为 HGFEBDAC, 后序表示为 HFGEDCAB.

```
         B
       /   \
      E     A
     /     / \
    G     D   C
   / \
  H   F
```

前序表示为 B, E, G, H, F, A, D, C.


## 4-12. 已知一棵每个结点的子结点数或者为 0 或者为 2 的二叉树的前序表示和后序表示, 写出它的中序表示.

### 4-12-2. 前序表示为 AFDBGCEHJ, 后序表示为 DBFEHCJGA.

```
       A
     /   \
    F     G
   / \   / \
  D   B C   J
       / \
      E   H
```

中序表示为 D, F, B, A, E, C, H, G, J.

