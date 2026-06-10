# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

LIB_DIR=/home/lib
INCLUDE += -I${LIB_DIR}/install_nn2/include
INCLUDE += -I${LIB_DIR}/decode/install/include
LDFLAGS = -L${LIB_DIR}/install_nn2/lib
LDFLAGS += -L${LIB_DIR}/decode/install/lib/rv

CC = riscv64-unknown-linux-gnu-gcc

CFLAGS += -O0 -g3 -march=rv64gcv0p7_zfh_xtheadc -mabi=lp64d ${INCLUDE}

LDFLAGS += -ljpeg -lpng -lz -lstdc++ -lshl_ref -lm -static -Wl,--gc-sections

NET_PATH = .
DATA_PATH = .

PYTHON_FLAGS = -C --model-file ${NET_PATH}/mobilenetv1.prototxt ${NET_PATH}/mobilenetv1.caffemodel --data-scale 0.017 --data-mean '104 117 124' --calibrate-dataset cat.jpg --output . --board c906 --pixel-format BGR #--dynamic-cb-reg

.PHONY: clean all

all: c_runtime

main.c model.c:
	hhb $(PYTHON_FLAGS)

c_runtime: main.c model.c io.c process.c #bc_reg.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS)

clean:
	-rm c_runtime -rf
	-rm main.c model.c model.params process.c process.h io.c io.h bc_reg.c hhb.bm -rf
	-rm *.tensor *.bin hhb_out -rf
