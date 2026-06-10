

VPATH=./src/:./include/:./work
SLIB=libdarknet.so
ALIB=libdarknet.a
EXEC=yolo_test_riscv_d1_cache-opt
OBJDIR=./obj/

#CC=riscv64-unknown-linux-gnu-gcc
#CPP=g++
NVCC=nvcc 
#AR=riscv64-unknown-linux-gnu-ar

tool_chain_base_dir=/home/loasic/experiments/lab11-d1/t-head-linux-toolchain-20210329/bin
tool_chain_base_dir=/opt/riscv-linux/bin
CC=${tool_chain_base_dir}/riscv64-unknown-linux-gnu-gcc
CPP=${tool_chain_base_dir}/riscv64-unknown-linux-gnu-g++
AR=${tool_chain_base_dir}/riscv64-unknown-linux-gnu-ar

ARFLAGS=rcs

OPTS=-Ofast
LDFLAGS= -lm -pthread -static
COMMON= -Iinclude/ -Isrc/ -Iwork/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -O3
# CFLAGS+=-march=rv64imafdcvxtheadc -mabi=lp64dv -mtune=c906 -g
# CFLAGS+=-march=rv64imafdcxtheadc -mabi=lp64d -mtune=c906 -g

#SOBJ = convolutional_layer.o
#SOBJS = $(addprefix $(OBJDIR), $(SOBJ))
#OBJ=gemm.o utils.o  convolutional_layer.o maxpool_layer.o list.o image.o activations.o im2col.o col2im.o blas.o data.o matrix.o network.o parser.o option_list.o route_layer.o upsample_layer.o box.o layer.o shortcut_layer.o tree.o yolo_layer.o detector.o mac_operation.o
OBJ=gemm.o utils.o  convolutional_layer.o maxpool_layer.o list.o image.o activations.o im2col.o col2im.o blas.o data.o matrix.o network.o parser.o option_list.o route_layer.o upsample_layer.o box.o layer.o shortcut_layer.o tree.o yolo_layer.o detector.o
EXECOBJA= yolo_test_riscv.o


EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile include/darknet.h

all: obj backup results $(EXEC)
#all: obj  results $(SLIB) $(ALIB) $(EXEC)


$(EXEC): $(EXECOBJ) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

#$(ALIB): $(OBJS)
#	$(AR) $(ARFLAGS) $@ $^ 

#$(SLIB): $(OBJS)
#	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

#$(OBJDIR)mac_operation.o: mac_operation.s $(DEPS)
#	$(CC) $(COMMON) $(CFLAGS) -c $< -o $(OBJDIR)mac_operation.o

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@


$(OBJDIR)%.o: %.cu $(DEPS)
	$(NVCC) $(ARCH) $(COMMON) --compiler-options "$(CFLAGS)" -c $< -o $@

obj:
	mkdir -p obj
backup:
	mkdir -p backup
results:
	mkdir -p results

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXECOBJ) $(OBJDIR)/*

