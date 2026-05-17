#!/bin/bash
# Lab 9: stage lab-provided files into the SMART tree. Idempotent — backs up
# originals to <file>.lab9.bak on first run; subsequent runs re-copy fresh
# lab9 versions over the (possibly modified) working files.

set -e

BASE_DIR="${BASE_DIR:-/home/ECDesign/ecd14/zfzhang_24301050026}"
SMART_DIR="${SMART_DIR:-$BASE_DIR/smart9_release}"
LAB_SHARE="${LAB_SHARE:-/home/ECDesign/ECDesign_share/lab9}"

backup_then_copy() {
    local src="$1" dst="$2"
    if [ ! -f "$src" ]; then
        echo "[stage] WARN: lab9 source missing: $src"
        return
    fi
    if [ -f "$dst" ] && [ ! -f "$dst.lab9.bak" ]; then
        cp -f "$dst" "$dst.lab9.bak"
        echo "[stage] backup: $dst -> $dst.lab9.bak"
    fi
    cp -f "$src" "$dst"
    echo "[stage] copy : $src -> $dst"
}

echo "[stage] BASE_DIR  = $BASE_DIR"
echo "[stage] SMART_DIR = $SMART_DIR"
echo "[stage] LAB_SHARE = $LAB_SHARE"

# 1) new AXI slave (maps memory at 0x02000000 for input data init)
mkdir -p "$SMART_DIR/rtl/platform/amba/axi"
backup_then_copy "$LAB_SHARE/axi_slave128_copy.v" \
                 "$SMART_DIR/rtl/platform/amba/axi/axi_slave128_copy.v"

# 2) top-level soc.v wiring in the new slave
backup_then_copy "$LAB_SHARE/soc.v" \
                 "$SMART_DIR/rtl/platform/common/soc.v"

# 3) Makefile with -fno-inline -g
backup_then_copy "$LAB_SHARE/Makefile" \
                 "$SMART_DIR/lib/Makefile"

# 4) tb.v with retire-PC opcode counters
backup_then_copy "$LAB_SHARE/tb.v" \
                 "$SMART_DIR/tb/tb.v"

# 5) crt0.s and pmu.h — only if user hasn't already migrated them in lab 6-8
if ! grep -q "csrs mhcr,x3" "$SMART_DIR/lib/crt0.s" 2>/dev/null; then
    backup_then_copy "$LAB_SHARE/crt0.s" "$SMART_DIR/lib/crt0.s"
else
    echo "[stage] keep : existing crt0.s already has mhcr write — not replaced"
fi
if [ -f "$LAB_SHARE/pmu.h" ]; then
    backup_then_copy "$LAB_SHARE/pmu.h" "$SMART_DIR/lib/clib/pmu.h"
fi

# 6) conv_test case dir (conv_test.c, .h, work.h, data_in, inst_proc)
mkdir -p "$SMART_DIR/case/conv_test"
cp -rf "$LAB_SHARE/conv_test/." "$SMART_DIR/case/conv_test/"
chmod +x "$SMART_DIR/case/conv_test/inst_proc" 2>/dev/null || true
echo "[stage] copy : $LAB_SHARE/conv_test/* -> $SMART_DIR/case/conv_test/"

# 7) sanity check: Core Num must be 1
core_v="$SMART_DIR/rtl/cpu/C910MP.v"
if [ -f "$core_v" ]; then
    # count DISTINCT PROCESSOR_N values that are actually `defined
    n=$(grep -oE '^\s*`define\s+PROCESSOR_[0-9]+' "$core_v" \
        | grep -oE 'PROCESSOR_[0-9]+' \
        | sort -u | wc -l)
    echo "[stage] C910MP.v has $n distinct PROCESSOR_N define(s)"
    if [ "$n" -gt 1 ]; then
        echo "[stage] ERROR: regenerate single-core RTL via C910_R1S2P19 (lab section 4.1)"
        exit 1
    fi
else
    echo "[stage] WARN: $core_v missing — make sure RTL is in place before running sim"
fi

echo "[stage] done."
