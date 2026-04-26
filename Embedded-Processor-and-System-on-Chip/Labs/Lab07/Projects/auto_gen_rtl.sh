#!/bin/bash

# Directory configuration
BASE_DIR="/home/ECDesign/ecd14/zfzhang_24301050026"
C910_DIR="$BASE_DIR/C910_R1S2P19"
RTL_POOL="$BASE_DIR/Lab07/rtl_pool"

# Ensure script runs in the correct directory
cd $C910_DIR
mkdir -p $RTL_POOL

L1_D_LIST=("32" "64")
L2_LIST=("512" "1024" "2048" "4096")

for L1D in "${L1_D_LIST[@]}"; do
    for L2 in "${L2_LIST[@]}"; do
        
        echo "====================================================="
        echo "Generating config: L1_Dcache=${L1D}K, L2_Cache=${L2}K ..."
        echo "====================================================="

        cat <<EOF > src_rtl/cpu_cfig.h
\`define MULTI_PROCESSING
\`define PROCESSOR_0
\`define ICACHE_32K
\`define DCACHE_${L1D}K
EOF
        
        if [ "$L2" == "512" ]; then echo "\`define L2_CACHE_512K" >> src_rtl/cpu_cfig.h; fi
        if [ "$L2" == "1024" ]; then echo "\`define L2_CACHE_1M" >> src_rtl/cpu_cfig.h; fi
        if [ "$L2" == "2048" ]; then echo "\`define L2_CACHE_2M" >> src_rtl/cpu_cfig.h; fi
        if [ "$L2" == "4096" ]; then echo "\`define L2_CACHE_4M" >> src_rtl/cpu_cfig.h; fi

        echo "\`define FPGA" >> src_rtl/cpu_cfig.h
        cat setup/cpu_cfig.h >> src_rtl/cpu_cfig.h

        bash sc -fpga > /dev/null

        RTL_FILE="gen_rtl/ct_mp_top_merged.v"
        sed -i 's/ct_mp_top/C910MP/g' $RTL_FILE
        sed -i '0,/`endif/ { /`ifdef/,/`endif/d; }' $RTL_FILE

        if [ "$L2" == "1024" ]; then L2_STR="1M"
        elif [ "$L2" == "2048" ]; then L2_STR="2M"
        elif [ "$L2" == "4096" ]; then L2_STR="4M"
        else L2_STR="${L2}K"; fi
        
        TARGET_NAME="C910_${L1D}K_${L2_STR}.v"
        cp $RTL_FILE $RTL_POOL/$TARGET_NAME
        
        echo "--> $TARGET_NAME generated and modified, saved to $RTL_POOL"
        
    done
done

echo "All RTL configuration files generated successfully!"

