#!/bin/csh

# Directory configuration
set BASE_DIR   = "/home/ECDesign/ecd14/zfzhang_24301050026"
set SMART_DIR  = "$BASE_DIR/smart9_release"
set C910_DIR   = "$BASE_DIR/C910_R1S2P19"
set OUT_DIR    = "$BASE_DIR/Lab07"
set RTL_POOL   = "$OUT_DIR/rtl_pool"
set RESULT_DIR = "$OUT_DIR/csv_results"
set TEST_FILE  = "$SMART_DIR/case/cache_test/cache_test.c"
set WORK_DIR   = "$SMART_DIR/workdir"
set LOG_FILE   = "$WORK_DIR/run.log"


# Initialize CSV files with headers
if ( -d "$RESULT_DIR" ) then
    rm -rf "$RESULT_DIR"/*
else
    mkdir -p "$RESULT_DIR"
endif
echo "L1_Dcache,L2_Dcache,N,cycle,insts,CPI,L1_Dread access,L1_Dread miss,L1_Dread miss_rate,L1_Dwrite access,L1_Dwrite miss,L1_Dwrite miss_rate" > "$RESULT_DIR"/result_L1.csv
echo "L1_Dcache,L2_Dcache,N,cycle,insts,CPI,L1_Dread access,L1_Dread miss,L1_Dread miss_rate,L2_Dread access,L2_Dread miss,L2_Dread miss_rate" > "$RESULT_DIR"/result_L2.csv

# Setup the environment
cd $BASE_DIR
source cshrc >& /dev/null
cd "$C910_DIR"
source setup/setup.csh >& /dev/null
cd "$SMART_DIR"
source setup.csh >& /dev/null


# Phase 1: L1 Cache Test
echo ""
echo "======================================="
echo "        Starting L1 Cache Test         "
echo "======================================="
echo ""

# Enable L1_TEST macro, disable L2_TEST macro
sed -i 's/^\/\/ #define L1_TEST/#define L1_TEST/g' "$TEST_FILE"
sed -i 's/^#define L2_TEST/\/\/ #define L2_TEST/g' "$TEST_FILE"

foreach l1 (32K 64K)
    foreach l2 (512K 1M)
        echo ""
        echo "[Load RTL] Preparing config: L1=${l1}, L2=${l2}"
        rm -rf "$SMART_DIR"/rtl/cpu/C910MP.v
        cp -rf "$RTL_POOL"/C910_${l1}_${l2}.v "$SMART_DIR"/rtl/cpu/C910MP.v
        
        foreach n (1 2 3 4)
            echo "   -> Testing N = $n ..."
            sed -i "s/int N = [0-9]*;/int N = $n;/g" "$TEST_FILE"
            
            # Remove old log to prevent false positives
            if ( -e "$LOG_FILE" ) rm -f "$LOG_FILE"
            cd "$WORK_DIR"
            run ../case/cache_test/cache_test.c >& /dev/null
            
            # Polling loop to wait for job completion
            set is_done = 0
            while ( $is_done == 0 )
                sleep 3
                if ( -e "$LOG_FILE" ) then
                    grep "simulation finished successfully" "$LOG_FILE" >& /dev/null
                    if ( $status == 0 ) set is_done = 1
                endif
            end
            
            python3 $OUT_DIR/auto_log.py "L1" $l1 $l2 $n $LOG_FILE >> "$RESULT_DIR"/result_L1.csv
            echo "      Done! Data recorded."
        end
    end
end

# Phase 2: L2 Cache Test
echo ""
echo "======================================="
echo "        Starting L2 Cache Test         "
echo "======================================="
echo ""

# Enable L2_TEST macro, disable L1_TEST macro
sed -i 's/^\/\/ #define L2_TEST/#define L2_TEST/g' "$TEST_FILE"
sed -i 's/^#define L1_TEST/\/\/ #define L1_TEST/g' "$TEST_FILE"

foreach l1 (32K 64K)
    foreach l2 (512K 1M 2M 4M)
        echo ""
        echo "[Load RTL] Preparing config: L1=${l1}, L2=${l2}"
        rm -rf "$SMART_DIR"/rtl/cpu/C910MP.v
        cp -rf "$RTL_POOL"/C910_${l1}_${l2}.v "$SMART_DIR"/rtl/cpu/C910MP.v
        
        foreach n (1 2)
            echo "   -> Testing N = $n ..."
            sed -i "s/int N = [0-9]*;/int N = $n;/g" "$TEST_FILE"
            
            if ( -e "$LOG_FILE" ) rm -f "$LOG_FILE"
            cd "$WORK_DIR"
            run ../case/cache_test/cache_test.c >& /dev/null
            
            set is_done = 0
            while ( $is_done == 0 )
                sleep 3
                if ( -e "$LOG_FILE" ) then
                    grep "simulation finished successfully" "$LOG_FILE" >& /dev/null
                    if ( $status == 0 ) set is_done = 1
                endif
            end
            
            python3 $OUT_DIR/auto_log.py "L2" $l1 $l2 $n $LOG_FILE >> "$RESULT_DIR"/result_L2.csv
            echo "      Done! Data recorded."
        end
    end
end

echo ""
echo "======================================="
echo "All simulation tasks completed!"
echo "Please check result_L1.csv and result_L2.csv in $RESULT_DIR"
echo "======================================="
echo ""

