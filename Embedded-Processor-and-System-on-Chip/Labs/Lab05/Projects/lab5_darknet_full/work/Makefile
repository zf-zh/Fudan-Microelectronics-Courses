
CC_x86=gcc
CC_riscv=riscv64-unknown-linux-gnu-gcc

SLIB_x86=libwork_x86.so
SLIB_riscv=libwork_riscv.so
SRC=work.c work.h

CFLAGS=-shared -fPIC

all: $(SLIB_x86) $(SLIB_riscv)

$(SLIB_x86): $(SRC)
	$(CC_x86) $(CFLAGS) -o ../$@ $<

$(SLIB_riscv): $(SRC)
	$(CC_riscv) $(CFLAGS) -o ../$@ $<

.PHONY: clean

clean:
	rm -rf *.so 
	rm -rf ../*.so



