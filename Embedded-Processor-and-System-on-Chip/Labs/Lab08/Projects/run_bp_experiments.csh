#!/bin/csh

# Lab 8: C910 branch-prediction sweep — 4 MHCR configs x 2 benchmarks = 8 sims.

# Paths
if ( ! $?SMART_DIR )   setenv SMART_DIR   "$HOME/zfzhang_24301050026/smart9_release"
if ( ! $?LAB_SHARE )   setenv LAB_SHARE   "/home/ECDesign/ECDesign_share/lab8"
set RESULTS_DIR = "$cwd/bp_results"
set EDIT_PY     = "$cwd/edit_crt0.py"
set CRT0        = "$SMART_DIR/lib/crt0.s"
set WORK_DIR    = "$SMART_DIR/workdir"
set LOG_FILE    = "$WORK_DIR/run.log"
set POLL_SEC    = 30

mkdir -p "$RESULTS_DIR"
echo "[setup] SMART_DIR = $SMART_DIR"
echo "[setup] RESULTS   = $RESULTS_DIR"

# Step 1: install lab-provided files (idempotent)
rm -f "$SMART_DIR/lib/crt0.s" "$SMART_DIR/case/dhry/Main.c" "$SMART_DIR/case/coremark/core_main.c"
cp -f "$LAB_SHARE/crt0.s"      "$SMART_DIR/lib/crt0.s"
cp -f "$LAB_SHARE/Main.c"      "$SMART_DIR/case/dhry/Main.c"
cp -f "$LAB_SHARE/core_main.c" "$SMART_DIR/case/coremark/core_main.c"
rm -f "$RESULTS_DIR/crt0.s.orig" >& /dev/null
cp -f "$CRT0" "$RESULTS_DIR/crt0.s.orig"   # backup pristine

# Step 2: source SMART env
cd "$SMART_DIR"/..
source cshrc >& /dev/null
cd "$SMART_DIR"
source setup.csh >& /dev/null

# Step 3: 4 configs x 2 benchmarks
foreach cfg ( all_on all_off btb_off bpe_off )
    echo ""
    echo "===================================================="
    echo "[cfg ] $cfg"
    echo "===================================================="
    python3 "$EDIT_PY" "$CRT0" "$cfg"

    foreach bench ( dhrystone coremark )
        if ( "$bench" == "dhrystone" ) then
            set src = "../case/dhry/Main.c"
        else
            set src = "../case/coremark/core_main.c"
        endif
        set out_dir = "$RESULTS_DIR/${bench}_${cfg}"
        mkdir -p "$out_dir"
        echo "[run ] cfg=$cfg  bench=$bench"

        cd "$WORK_DIR"
        if ( -e "$LOG_FILE" ) rm -f "$LOG_FILE"
        run "$src" >& /dev/null

        # poll for completion marker
        set is_done = 0
        while ( $is_done == 0 )
            sleep $POLL_SEC
            if ( -e "$LOG_FILE" ) then
                grep "simulation finished successfully" "$LOG_FILE" >& /dev/null
                if ( $status == 0 ) set is_done = 1
            endif
        end

        rm -f "$out_dir/run.log" "$out_dir/crt0.s.used" >& /dev/null
        cp -f "$LOG_FILE" "$out_dir/run.log"
        cp -f "$CRT0"     "$out_dir/crt0.s.used"
        echo "[done] -> $out_dir/run.log"
    end
end

# Step 4: restore pristine crt0.s
rm -f "$CRT0" >& /dev/null
cp -f "$RESULTS_DIR/crt0.s.orig" "$CRT0"

echo ""
echo "===================================================="
echo "[ok] all 8 runs complete."
echo "    parse:  python3 parse_bp_results.py $RESULTS_DIR"
echo "===================================================="
