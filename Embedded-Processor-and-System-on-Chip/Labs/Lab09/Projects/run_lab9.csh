#!/bin/csh
# Lab 9: SMART simulation of YOLO convolution function
#   3 branch-prediction configs x 1 benchmark (conv_test) = 3 sim runs
#   plus 1 throwaway "calibration" run if the guard PCs in tb.v don't already
#   match the freshly-linked elf. Adaptive: skips re-run when tb.v is correct.
 
# ---- paths ----
if ( ! $?BASE_DIR )   setenv BASE_DIR   "/home/ECDesign/ecd14/zfzhang_24301050026"
if ( ! $?SMART_DIR )  setenv SMART_DIR  "$BASE_DIR/smart9_release"
if ( ! $?LAB_SHARE )  setenv LAB_SHARE  "/home/ECDesign/ECDesign_share/lab9"
if ( ! $?LAB_DIR )    setenv LAB_DIR    "$BASE_DIR/Lab09"
 
set RESULTS_DIR = "$LAB_DIR/results"
set EDIT_PY     = "$LAB_DIR/edit_crt0.py"
set PATCH_PY    = "$LAB_DIR/patch_guard_pcs.py"
set CRT0        = "$SMART_DIR/lib/crt0.s"
set TB_V        = "$SMART_DIR/tb/tb.v"
set WORK_DIR    = "$SMART_DIR/workdir"
set CASE_DIR    = "$SMART_DIR/case/conv_test"
set SRC         = "../case/conv_test/conv_test.c"
set ELF         = "$CASE_DIR/conv_test.elf"
set INST_PROC   = "$CASE_DIR/inst_proc"
set LOG_FILE    = "$WORK_DIR/run.log"
set INST_FILE   = "$WORK_DIR/inst_count"
set OBJDUMP     = "$SMART_DIR/tools/toolchain/RV64GC/bin/riscv64-unknown-elf-objdump"
set POLL_SEC    = 30
set MAX_WAITS   = 1200       # 1200 * 30s = 10h ceiling per sim
 
mkdir -p "$RESULTS_DIR"
echo "[setup] BASE_DIR    = $BASE_DIR"
echo "[setup] SMART_DIR   = $SMART_DIR"
echo "[setup] LAB_SHARE   = $LAB_SHARE"
echo "[setup] RESULTS_DIR = $RESULTS_DIR"
 
# ---- backup pristine crt0.s ----
if ( ! -e "$RESULTS_DIR/crt0.s.orig" ) cp -f "$CRT0" "$RESULTS_DIR/crt0.s.orig"
 
# ---- source SMART env ----
cd "$BASE_DIR"
if ( -e cshrc ) source cshrc >& /dev/null
if ( $?C910_DIR ) then
    cd "$C910_DIR"
    if ( -e setup/setup.csh ) source setup/setup.csh >& /dev/null
endif
cd "$SMART_DIR"
source setup.csh >& /dev/null
 
# ---- 3 configs ----
set CFGS = ( all_off btb_off all_on )
set patched_already = 0
 
foreach cfg ( $CFGS )
    echo ""
    echo "===================================================="
    echo "[cfg ] $cfg"
    echo "===================================================="
    python3 "$EDIT_PY" "$CRT0" "$cfg"
    if ( $status != 0 ) then
        echo "[error] edit_crt0 failed for cfg=$cfg - aborting"
        rm -f "$CRT0" >& /dev/null
        cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"
        exit 1
    endif
 
    cd "$WORK_DIR"
    rm -f "$LOG_FILE" "$INST_FILE" >& /dev/null
    echo "[run ] cfg=$cfg  src=$SRC"
    run "$SRC" >& /dev/null &
 
    # ---- inline wait loop (csh aliases with `end` are broken) ----
    set _waits = 0
    while ( $_waits < $MAX_WAITS )
        if ( -e "$LOG_FILE" ) then
            grep "simulation finished successfully" "$LOG_FILE" >& /dev/null
            if ( $status == 0 ) break
        endif
        sleep $POLL_SEC
        @ _waits ++
        if ( $_waits % 10 == 0 ) echo "[wait] cfg=$cfg  polls=$_waits"
    end
    if ( $_waits >= $MAX_WAITS ) then
        echo "[error] sim for cfg=$cfg timed out after $_waits polls"
        rm -f "$CRT0" >& /dev/null
        cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"
        exit 1
    endif
    echo "[wait] cfg=$cfg  done (polls=$_waits)"
 
    # ---- one-time guard-PC discovery & patch on the very first run ----
    if ( $patched_already == 0 ) then
        if ( -e "$ELF" ) then
            echo "[calib] checking guard PCs against $ELF"
            python3 "$PATCH_PY" "$ELF" "$TB_V" "$OBJDUMP"
            set rc = $status
            set patched_already = 1
            if ( $rc == 1 ) then
                echo "[calib] tb.v was patched; re-running cfg=$cfg with correct PCs"
                cd "$WORK_DIR"
                rm -f "$LOG_FILE" "$INST_FILE" >& /dev/null
                run "$SRC" >& /dev/null &
 
                # inline wait (calibration re-run)
                set _waits = 0
                while ( $_waits < $MAX_WAITS )
                    if ( -e "$LOG_FILE" ) then
                        grep "simulation finished successfully" "$LOG_FILE" >& /dev/null
                        if ( $status == 0 ) break
                    endif
                    sleep $POLL_SEC
                    @ _waits ++
                    if ( $_waits % 10 == 0 ) echo "[wait] cfg=$cfg(recal)  polls=$_waits"
                end
                if ( $_waits >= $MAX_WAITS ) then
                    echo "[error] recal sim timed out"
                    rm -f "$CRT0" >& /dev/null
                    cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"
                    exit 1
                endif
                echo "[wait] cfg=$cfg(recal)  done (polls=$_waits)"
            else if ( $rc == 0 ) then
                echo "[calib] tb.v already matched elf; keeping this run"
            else
                echo "[calib] ERROR rc=$rc; aborting"
                rm -f "$CRT0" >& /dev/null
                cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"
                exit 1
            endif
        else
            echo "[calib] WARN: $ELF not found after run - skipping PC check"
            set patched_already = 1
        endif
    endif
 
    # ---- archive ----
    set out = "$RESULTS_DIR/conv_${cfg}"
    mkdir -p "$out"
    rm -f "$out/run.log" "$out/inst_count" "$out/inst_class" "$out/crt0.s.used" >& /dev/null
    cp -f "$LOG_FILE"  "$out/run.log"
    if ( -e "$INST_FILE" ) cp -f "$INST_FILE" "$out/inst_count"
    cp -f "$CRT0"      "$out/crt0.s.used"
 
    # ---- produce inst_class ----
    if ( -x "$INST_PROC" && -e "$out/inst_count" ) then
        cd "$out"
        rm -f ./inst_proc >& /dev/null
        cp -f "$INST_PROC" ./inst_proc
        ./inst_proc >& /dev/null
        if ( -e inst_class ) then
            echo "[done] $out/run.log + inst_count + inst_class"
        else
            echo "[done] $out/run.log + inst_count (inst_proc produced no inst_class)"
        endif
        rm -f ./inst_proc
    else
        echo "[done] $out/run.log only (inst_proc or inst_count missing)"
    endif
end
 
# ---- restore pristine crt0.s ----
rm -f "$CRT0" >& /dev/null
cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"
 
echo ""
echo "===================================================="
echo "[ok] all 3 runs complete."
echo "    parse:  python3 $LAB_DIR/parse_lab9_results.py $RESULTS_DIR"
echo "    plot :  python3 $LAB_DIR/plot_inst_dist.py    $RESULTS_DIR"
echo "===================================================="
