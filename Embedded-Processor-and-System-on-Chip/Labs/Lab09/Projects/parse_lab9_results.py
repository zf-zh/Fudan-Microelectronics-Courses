#!/usr/bin/env python3
"""Aggregate Lab 9 results into the report-template table.

Reads results/conv_<cfg>/run.log for cfg in {all_off, btb_off, all_on},
extracts PMU counters, and emits a Markdown table + CSV matching the
column layout in the lab report template:

    metric                       | all prediction off | BPE on, BTB off | all prediction on
    cycle                        | ...
    insts                        | ...
    CPI                          | ...
    conditional branch miss      | ...
    L1_Dread access              | ...
    L1_Dread miss                | ...
    L1_Dread miss_rate           | ...
    L1_Dwrite access             | ...
    L1_Dwrite miss               | ...
    L1_Dwrite miss_rate          | ...
    L2_Dread access              | ...
    L2_Dread miss                | ...
    L2_Dread miss_rate           | ...
    L2_Dwrite access             | ...
    L2_Dwrite miss               | ...
    L2_Dwrite miss_rate          | ...
"""

import sys, re, pathlib, csv

CONFIGS = ["all_off", "btb_off", "all_on"]
LABEL = {
    "all_off": "all prediction off",
    "btb_off": "BPE on, BTB off",
    "all_on":  "all prediction on",
}

# PMU variable name -> our internal key
PMU_VARS = {
    "cycle":                    "cycle",
    "instret":                  "insts",
    "conditional_branch_mis":   "cond_miss",
    "L1_Dcache_read_access":    "l1_dr_acc",
    "L1_Dcache_read_miss":      "l1_dr_miss",
    "L1_Dcache_write_access":   "l1_dw_acc",
    "L1_Dcache_write_miss":     "l1_dw_miss",
    "L2_Dcache_read_access":    "l2_dr_acc",
    "L2_Dcache_read_miss":      "l2_dr_miss",
    "L2_Dcache_write_access":   "l2_dw_acc",
    "L2_Dcache_write_miss":     "l2_dw_miss",
}

def parse_log(p: pathlib.Path) -> dict:
    if not p.is_file():
        return {}
    txt = p.read_text(errors="ignore")
    row = {}
    for var, key in PMU_VARS.items():
        matches = re.findall(rf'num_{var}\s+is\s+(-?\d+)', txt)
        row[key] = int(matches[-1]) if matches else None
    # derived
    if row.get("cycle") and row.get("insts"):
        row["cpi"] = row["cycle"] / row["insts"]
    for prefix in ("l1_dr", "l1_dw", "l2_dr", "l2_dw"):
        acc, miss = row.get(f"{prefix}_acc"), row.get(f"{prefix}_miss")
        if acc and miss is not None:
            row[f"{prefix}_mr"] = miss / acc if acc else 0.0
    return row

def fmt(v):
    if v is None:        return "-"
    if isinstance(v, float):
        return f"{v:.4f}" if abs(v) < 1 else f"{v:.3f}"
    return str(v)

# (display label, key)  - order matches report template
METRICS = [
    ("cycle",                   "cycle"),
    ("insts",                   "insts"),
    ("CPI",                     "cpi"),
    ("conditional branch miss", "cond_miss"),
    ("L1_Dread access",         "l1_dr_acc"),
    ("L1_Dread miss",           "l1_dr_miss"),
    ("L1_Dread miss_rate",      "l1_dr_mr"),
    ("L1_Dwrite access",        "l1_dw_acc"),
    ("L1_Dwrite miss",          "l1_dw_miss"),
    ("L1_Dwrite miss_rate",     "l1_dw_mr"),
    ("L2_Dread access",         "l2_dr_acc"),
    ("L2_Dread miss",           "l2_dr_miss"),
    ("L2_Dread miss_rate",      "l2_dr_mr"),
    ("L2_Dwrite access",        "l2_dw_acc"),
    ("L2_Dwrite miss",          "l2_dw_miss"),
    ("L2_Dwrite miss_rate",     "l2_dw_mr"),
]

def main():
    root = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "results")
    rows = {c: parse_log(root / f"conv_{c}" / "run.log") for c in CONFIGS}

    # ---- markdown ----
    md = []
    md.append("| metric | " + " | ".join(LABEL[c] for c in CONFIGS) + " |")
    md.append("|" + "---|" * (len(CONFIGS) + 1))
    for lbl, key in METRICS:
        md.append(f"| {lbl} | " + " | ".join(fmt(rows[c].get(key)) for c in CONFIGS) + " |")
    md_text = "\n".join(md)

    print("\n## Lab 9 - CPI / Cache / Branch-Prediction Statistics\n")
    print(md_text)

    md_path = root / "table_bp.md"
    md_path.write_text(md_text + "\n")
    print(f"\n  md  -> {md_path}")

    # ---- csv ----
    csv_path = root / "table_bp.csv"
    with csv_path.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["metric"] + [LABEL[c] for c in CONFIGS])
        for lbl, key in METRICS:
            w.writerow([lbl] + [fmt(rows[c].get(key)) for c in CONFIGS])
    print(f"  csv -> {csv_path}")

if __name__ == '__main__':
    main()
