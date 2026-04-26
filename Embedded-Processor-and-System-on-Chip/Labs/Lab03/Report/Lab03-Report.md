---
title: "Computer Architecture Lab 03 Report"
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
header-includes:
  - \usepackage{float}
  - \floatplacement{figure}{H}
---


# 实验3 RISC-V QEMU 上运行 Linux 系统

## 1. 实验目的

通过在 RISC-V QEMU 上运行 Linux 操作系统, 进一步掌握 QEMU 系统模式的使用方法, 了解交叉工具链的作用, Buildroot 的主要功能和 Linux 系统的基本原理.


## 2. 实验步骤

### 2.1. 使用 Buildroot 搭建 Linux 系统的配置和编译过程

1. **下载 Buildroot 源代码**

   通过 `git` 克隆 Buildroot 的源代码仓库, 并切换到指定版本.

   ![Clone Buildroot Source Code](./Resources/2.1/2.1-01-Clone-Buildroot-Source-Code.png){width=85%}

2. **配置 Buildroot**

   安装必要依赖后, 进入 Buildroot 的源代码目录, 导入针对 RISC-V 64 的默认配置.

   ![Default Buildroot Configuration](./Resources/2.1/2.1-02-Default-Buildroot-Configuration.png){width=85%}

3. **图形化配置**

   通过 `make menuconfig` 命令进入 Buildroot 的图形化配置界面, 可以按需选择和修改配置选项.

   ![Graphical Configuration](./Resources/2.1/2.1-03-Graphical-Configuration.png){width=85%}

   `Target options` 保持默认.

   ![Target Options](./Resources/2.1/2.1-04-Target-Options.png){width=85%}

   `Build options` 保持默认.

   ![Build Options](./Resources/2.1/2.1-05-Build-Options.png){width=85%}

   `Toolchain` 中额外选择 `Enable C++ support`, 其他保持默认.

   ![Toolchain](./Resources/2.1/2.1-06-Toolchain.png){width=85%}

   `System configuration` 中设置了一些无关紧要的选项.

   ![System Configuration](./Resources/2.1/2.1-07-System-Configuration.png){width=85%}

   `Kernel` 同样保持默认.

   ![Kernel](./Resources/2.1/2.1-08-Kernel.png){width=85%}

   `Target packages` 中选择了 `Networking applications` 下的 `lftp` 等工具.

   ![Target Packages](./Resources/2.1/2.1-09-Target-Packages.png){width=85%}

   `Filesystem images` 中选择了 `ext4` 格式的根文件系统镜像, 并修改大小为 500MB, 其他保持默认.

   ![Filesystem Images](./Resources/2.1/2.1-10-Filesystem-Images.png){width=85%}

   `Bootloaders` 保持默认.

   ![Bootloaders](./Resources/2.1/2.1-11-Bootloaders.png){width=85%}

   `Host utilities` 中取消勾选了 `host qemu` 相关工具.

   ![Host Utilities](./Resources/2.1/2.1-12-Host-Utilities.png){width=85%}

4. **编译 Buildroot**

   配置完成后, 直接运行 `make` 命令进行编译. 编译过程会自动下载和构建交叉工具链, 构建 Linux kernel 和根文件系统镜像等. 编译完成后, 生成的文件位于 `output/images` 目录下.
  
   ![Build Buildroot](./Resources/2.1/2.1-13-Build-Buildroot.png){width=85%}

5. **启动 QEMU**

   编译完成后, 使用如下的 script 启动 QEMU, 加载编译生成的 Linux kernel 和根文件系统镜像.

   ![Start Script](./Resources/2.1/2.1-14-Start-Script.png){width=85%}

   编写 script 并赋予执行权限, 直接运行后系统通过 QEMU system 模式启动, 进入系统的登录界面.

   ![Start QEMU](./Resources/2.1/2.1-15-Start-QEMU.png){width=85%}

### 2.2. 向 QEMU 上的 Linux 系统转移文件

1. **挂载文件系统镜像**

   由于 QEMU 上的 Linux 系统使用了 ext4 格式的根文件系统镜像, 可以在宿主机上直接挂载该镜像文件, 从而访问和修改其中的文件.

   这里直接挂载到 `/mnt` 目录下, 并将目标文件复制到镜像中的 `/root` 目录下.

   ![Mount Filesystem Image](./Resources/2.2/2.2-01-Mount-Filesystem-Image.png){width=85%}

2. **使用 FTP 传输文件**

   也可以通过 FTP 工具将文件传输到 QEMU 上的 Linux 系统中.

   在主机中安装并启动 `vsftpd` 服务.

   ![Install and Start `vsftpd`](./Resources/2.2/2.2-02-Install-and-Start-vsftpd.png){width=85%}

   在 QEMU 上的 Linux 系统中连接 FTP 服务器, 并将目标文件下载到系统中.

   ![FTP Transfer](./Resources/2.2/2.2-03-FTP-Transfer.png){width=64%}

### 2.3. 在 QEMU 上的 Linux 系统运行编译后的 C 程序

1. **运行程序**

   将编译生成的可执行文件复制到 QEMU 上的 Linux 系统中, 赋予执行权限, 直接运行即可.

   ![Run Program](./Resources/2.3/2.3-01-Run-Program.png){width=50%}


## 3. 实验分析与总结

本次实验通过 Buildroot 搭建了 RISC-V 架构的 Linux 系统, 并在 QEMU 上运行. 在实验过程中了解了 Buildroot 的配置和编译流程, 并复习了 QEMU system 模式的使用方式.

在配置 Buildroot 的过程中, 需要根据实际需求选择合适的选项,这对于理解 Linux 系统的构建和定制非常有帮助. 通过挂载文件系统镜像和 FTP 协议两种方式的文件传输, 也熟悉了在模拟环境中管理和操作文件的方法.最后, 通过在 QEMU 运行的操作系统内执行编译后的 C 程序, 验证了整个系统的功能.

总体来说, 这次实验不仅加深了我们对 Linux 系统和 QEMU 模拟器的理解, 还提升了我们在开发中的实际操作能力.


## 4. 实验收获与建议

通过本次实验, 我们不仅学会了如何使用 Buildroot 来构建一个适用于 RISC-V 架构的 Linux 系统, 还掌握了在 QEMU 上运行该系统的方法. 这对于我们理解嵌入式系统的开发流程和 Linux 系统的定制化非常有帮助. 在实验过程中, 我们也遇到了一些挑战, 比如配置 Buildroot 时需要仔细选择选项以满足系统需求, 以及在 QEMU 上管理文件系统和传输文件的不同方法. 这些经历让我们更深入地理解了 Linux 系统的特性和运行机制.

实验中的一个建议是, 在文件传输方面, 可以尝试更符合现代需求的工具和方法, 例如 `scp` 或者 `rsync` 等在效率和安全性方面更优的工具.

总体来说, 这次实验是一次非常有价值的学习经历, 希望未来能够继续深入学习和实践 Linux 系统和体系结构相关的知识.

