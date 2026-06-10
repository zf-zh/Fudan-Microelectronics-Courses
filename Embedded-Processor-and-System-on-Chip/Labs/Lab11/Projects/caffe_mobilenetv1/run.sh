#!/bin/bash -x

qemu-riscv64 -cpu c906fdv c_runtime model.params data.0.bin
