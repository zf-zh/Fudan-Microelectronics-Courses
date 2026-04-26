
CC=riscv64-unknown-elf-gcc
CFLAGS=-g
EXEC=test
EXECOBJ=mul.o fac.o main.o
SRC=mul.s fac.s main.c

all: $(EXEC)

$(EXEC): $(EXECOBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(EXECOBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^


.PHONY: clean

clean:
	rm -rf $(EXECOBJ) $(EXEC)
	
