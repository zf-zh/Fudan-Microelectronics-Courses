---
title: "第二章 Linux 系统的软件开发工具"
author: "张兆飞"
date: 2026-04-27
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

## 2-8. 已知单元文件的后缀为 `.cell`, 器件文件的后缀为 `.dev`.

由单元文件生成器件文件的命令形式为:

```bash
$ getCell name.cell
```

请按照 `makefile` 的后缀规则表述它们的依赖关系和生成命令.

```makefile
%.dev: %.cell
  getCell $<
```

```makefile
.SUFFIXES: .cell .dev
.dev.cell:
  getCell $<
```

