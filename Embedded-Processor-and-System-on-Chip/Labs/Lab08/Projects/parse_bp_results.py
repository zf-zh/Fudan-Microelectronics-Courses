#!/usr/bin/env python3

"""Parse bp_results/<bench>_<cfg>/run.log into the two Lab 8 tables."""

import sys, re, pathlib, csv

RESULTS = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "bp_results")
CONFIGS = ["all_on", "all_off", "btb_off", "bpe_off"]
LABEL = {
    "all_on":  "all prediction on",
    "all_off": "all prediction off",
    "btb_off": "BTB,L0BTB off",
    "bpe_off": "BPE off",
}

def gv(text, var):
    m = re.search(rf'num_{var}\s+is\s+(-?\d+)', text)
    return int(m.group(1)) if m else None

def parse(log_path):
    if not log_path.exists():
        return {}
    txt = log_path.read_text(errors="ignore")
    cycle = gv(txt, "cycle")
    insts = gv(txt, "instret")
    row = {
        "cycle":      cycle,
        "insts":      insts,
        "cpi":        (cycle / insts) if (cycle and insts) else None,
        "cond_miss":  gv(txt, "conditional_branch_mis"),
        "indir_miss": gv(txt, "indirect_branch_mis"),
        "indir_inst": gv(txt, "indirect_branch_inst"),
    }
    m = re.search(r'dhrystone\s+is\s+([\d.]+)\s+dmips/MHz', txt, re.I)
    if m: row["dmips_per_mhz"] = float(m.group(1))
    m = re.search(r'CoreMark\s*1\.0\s*:\s*([\d.]+)\s*CoreMark/MHz', txt, re.I)
    if not m:
        m = re.search(r'CoreMark/MHz\s*:\s*([\d.]+)', txt)
    if m: row["coremark_per_mhz"] = float(m.group(1))
    return row

def fmt(v):
    if v is None: return "-"
    if isinstance(v, float): return f"{v:.4f}"
    return str(v)

def build(bench, score_key, score_label, csv_name):
    rows = {c: parse(RESULTS / f"{bench}_{c}" / "run.log") for c in CONFIGS}
    metrics = [
        ("cycle", "cycle"), ("insts", "insts"), ("cpi", "CPI"),
        ("cond_miss",  "conditional branch miss"),
        ("indir_miss", "indirect branch miss"),
        ("indir_inst", "indirect branch inst"),
        (score_key, score_label),
    ]
    print(f"\n## {bench}\n")
    print("| metric | " + " | ".join(LABEL[c] for c in CONFIGS) + " |")
    print("|---" * (len(CONFIGS) + 1) + "|")
    for k, lbl in metrics:
        print(f"| {lbl} | " + " | ".join(fmt(rows[c].get(k)) for c in CONFIGS) + " |")
    csv_path = RESULTS / csv_name
    with csv_path.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["metric"] + [LABEL[c] for c in CONFIGS])
        for k, lbl in metrics:
            w.writerow([lbl] + [fmt(rows[c].get(k)) for c in CONFIGS])
    print(f"\n  csv -> {csv_path}")

build("dhrystone", "dmips_per_mhz",    "DMPIS (dmips/MHz)",  "table1_dhrystone.csv")
build("coremark",  "coremark_per_mhz", "CoreMark/MHz",        "table2_coremark.csv")
