#!/usr/bin/env python3
"""Parse inst_class (output of inst_proc) and plot the instruction
distribution as a bar chart.
"""

import sys, re, pathlib, csv

LEAF_RE   = re.compile(r'^\s+([^:]+?):\s+(\d+)\s*$')
HEAD_RE   = re.compile(r'^(\S[^:]*?):\s*$')                  # header only, no count
DIRECT_RE = re.compile(r'^(\S[^:]*?):\s+(\d+)\s*$')          # header + count on one line

def parse_inst_class(path: pathlib.Path):
    """Return dict: { 'top': [(cat, count)], 'leaf': [(name, count)] }."""
    top, leaf = [], []
    current_header = None
    current_header_sum = 0
    for raw in path.read_text().splitlines():
        if not raw.strip():
            if current_header is not None and current_header_sum > 0:
                top.append((current_header, current_header_sum))
            current_header, current_header_sum = None, 0
            continue
        # tab-indented leaf
        m = LEAF_RE.match(raw)
        if m:
            name, n = m.group(1).strip(), int(m.group(2))
            leaf.append((name, n))
            current_header_sum += n
            continue
        # header + count on same line (e.g. "atomic instructions: 0")
        m = DIRECT_RE.match(raw)
        if m:
            name, n = m.group(1).strip(), int(m.group(2))
            if name.lower() == "total":
                continue
            top.append((name, n))
            leaf.append((name, n))
            current_header, current_header_sum = None, 0
            continue
        # bare header
        m = HEAD_RE.match(raw)
        if m:
            if current_header is not None and current_header_sum > 0:
                top.append((current_header, current_header_sum))
            current_header, current_header_sum = m.group(1).strip(), 0
            continue
    # flush trailing header
    if current_header is not None and current_header_sum > 0:
        top.append((current_header, current_header_sum))
    return {"top": top, "leaf": leaf}

def plot_groups(per_cfg: dict, kind: str, out_png: pathlib.Path):
    """per_cfg = {cfg_label: [(name, count), ...]}. Bars grouped by name."""
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import numpy as np

    # union of names, preserve first-seen order
    names = []
    for items in per_cfg.values():
        for n, _ in items:
            if n not in names:
                names.append(n)

    cfgs = list(per_cfg.keys())
    n_cfg = len(cfgs)
    width = 0.8 / max(n_cfg, 1)
    x = np.arange(len(names))

    fig, ax = plt.subplots(figsize=(max(8, 0.9 * len(names) * n_cfg), 5))
    for i, cfg in enumerate(cfgs):
        d = dict(per_cfg[cfg])
        vals = [d.get(n, 0) for n in names]
        ax.bar(x + i * width - 0.4 + width / 2, vals, width, label=cfg)

    ax.set_yscale("log")
    ax.set_xticks(x)
    ax.set_xticklabels([n.replace(" instructions", "").strip() for n in names],
                       rotation=30, ha='right')
    ax.set_ylabel("instruction count (log scale)")
    ax.set_title(f"Lab 9 instruction distribution ({kind})")
    ax.legend(loc="best")
    ax.grid(axis="y", which="both", linestyle=":", alpha=0.5)
    fig.tight_layout()
    fig.savefig(out_png, dpi=150)
    print(f"  png -> {out_png}")

def main():
    root = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "results")
    # gather all configs that produced inst_class
    per_cfg_leaf, per_cfg_top = {}, {}
    for sub in sorted(root.glob("conv_*")):
        ic = sub / "inst_class"
        if not ic.is_file():
            print(f"  skip {sub.name}: no inst_class")
            continue
        parsed = parse_inst_class(ic)
        cfg = sub.name.replace("conv_", "")
        per_cfg_leaf[cfg] = parsed["leaf"]
        per_cfg_top[cfg]  = parsed["top"]
        print(f"  parsed {sub.name}: {len(parsed['leaf'])} leaves, "
              f"{len(parsed['top'])} top-level cats")

    if not per_cfg_leaf:
        print("no inst_class files found; nothing to plot")
        sys.exit(1)

    # CSV of leaf-level (per cfg as columns)
    leaf_names = []
    for items in per_cfg_leaf.values():
        for n, _ in items:
            if n not in leaf_names:
                leaf_names.append(n)
    csv_path = root / "inst_dist.csv"
    with csv_path.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["instruction"] + list(per_cfg_leaf.keys()))
        for n in leaf_names:
            row = [n]
            for cfg, items in per_cfg_leaf.items():
                d = dict(items)
                row.append(d.get(n, 0))
            w.writerow(row)
    print(f"  csv -> {csv_path}")

    # Plots
    plot_groups(per_cfg_leaf, "leaf-level", root / "inst_dist.png")
    plot_groups(per_cfg_top,  "top-level",  root / "inst_dist_top.png")

if __name__ == '__main__':
    main()
