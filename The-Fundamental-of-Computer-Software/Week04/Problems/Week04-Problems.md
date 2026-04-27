---
title: "第一章 操作系统及 Linux Shell"
author: "张兆飞"
date: 2026-03-27
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


# 第四周 习题

## 1-19. 在___处填入正确内容.

```Shell
# Shell 文件 sh1-19:

echo N = $#
n=3
for i in "$@"               # (1)
do
    if [ $n -lt $# ]
    then
        n=`expr $n + 1`     # (2)
        echo key= $i $n
    else
        echo end: $i        # (3)
        break # (4)
    fi
done

```

```Shell
# 执行
$ sh sh1-19 x y z a b
N = 5                       # (5)
key= x 4
key= y 5                    # (6)
end: z                      # (7)

```


## 1-20. 工作目录栈. 在___处填入正确内容.

```Shell
% pwd
/mnt/home/user1
% pushd /usr/man
# (1)
/usr/man /mnt/home/user1

% pushd /tmp
# (2)
/tmp /usr/man /mnt/home/user1

% popd
# (3)
/usr/man /mnt/home/user1

% cd /bin
% pushd
# (4)
/mnt/home/user /bin

```


## 1-21. 工作目录栈. 在___处填入正确内容.

```Shell
% cd /etc
% pushd /usr/man
# (1)
/usr/man /etc

% pushd /tmp
# (2)
/tmp /usr/man /etc

% pushd
# (3)
/usr/man /tmp /etc

% popd
# (4)
/tmp /etc

% cd /bin
% pushd
# (5)
/etc /bin

```

