#!/usr/bin/env python3
"""Lab 9 crt0.s editor - toggle-by-comment within the MHCR vicinity.

The lab9 crt0.s ships with four labeled MHCR-write candidates, of which
exactly one should be uncommented at a time. The MHCR bits (per the
comment in crt0.s itself: `mhcr 4-RS, 5-BPE, 6-BTB, 7-IBPE, 12-L0BTB`) are:

    0x10f7  all prediction on           bits 0,1,2,4,5,6,7,12
    0x0007  all prediction off          bits 0,1,2
    0x00b7  BTB,L0BTB off  (== "BPE on, BTB off" in the report template)
    0x10d7  BPE off                     (not selected by Lab 9 report)

Strategy: find the MHCR write (`csrs mhcr,x3` OR the numeric-CSR form
`csrs 0x7c1,x3`), define a window of VICINITY lines around it, and within
that window:
  - uncomment exactly the one `li x3, 0xVAL` line whose VAL matches our cfg
  - comment out every other `li x3, 0xVAL` line whose VAL is one we know about

Line count is preserved across edits, so post-link addresses (and therefore
the GUARD_*_PC values in tb.v) stay stable across configs.
"""

import sys, re, pathlib

# cfg name -> hex value (lowercase, no 0x prefix)
HEX = {
    'all_on':  '10f7',
    'all_off': '0007',
    'btb_off': '00b7',
}
# every candidate we expect to find in the vicinity - toggled as a group
KNOWN_HEXES = {'10f7', '0007', '00b7', '10d7', '0017'}
VICINITY = 12   # lines either side of the csrs-mhcr line

def find_csrs_mhcr(lines):
    """Return index of the active `csrs mhcr,x3` (or `csrs 0x7c1,x3`) line.

    Prefers an uncommented match; falls back to a commented one so we can
    still locate the vicinity even if the user pre-commented everything.
    """
    csrs_re = re.compile(r'^\s*(#\s*)?csrs\s+(mhcr|0x7c1)\s*,\s*x3\b',
                         re.IGNORECASE)
    live_idx, any_idx = None, None
    for i, ln in enumerate(lines):
        m = csrs_re.match(ln)
        if not m: continue
        if any_idx is None: any_idx = i
        if not ln.lstrip().startswith('#'):
            live_idx = i; break
    return live_idx if live_idx is not None else any_idx

def main():
    if len(sys.argv) != 3 or sys.argv[2] not in HEX:
        print(f"usage: {sys.argv[0]} <crt0.s> <{'|'.join(HEX)}>", file=sys.stderr)
        sys.exit(2)

    path = pathlib.Path(sys.argv[1])
    cfg_name = sys.argv[2]
    target_hex = HEX[cfg_name]

    lines = path.read_text().splitlines()
    csrs_idx = find_csrs_mhcr(lines)
    if csrs_idx is None:
        print(f"[edit_crt0] ERROR: could not find csrs (mhcr|0x7c1) in {path}",
              file=sys.stderr)
        sys.exit(1)

    lo = max(0, csrs_idx - VICINITY)
    hi = min(len(lines), csrs_idx + VICINITY + 1)

    # match li x3, 0xVAL whether commented or not
    li_re = re.compile(
        r'^(\s*)(#\s*)?(li\s+x3\s*,\s*)0x([0-9a-fA-F]+)(.*)$',
        re.IGNORECASE,
    )

    selected = None
    toggled_off = []
    for i in range(lo, hi):
        m = li_re.match(lines[i])
        if not m: continue
        indent, comment, instr, hexval, rest = m.groups()
        hex_low = hexval.lower()
        if hex_low not in KNOWN_HEXES:
            continue   # not one of ours, leave it alone

        if hex_low == target_hex:
            # ensure uncommented (preserve indent + rest including trailing comment)
            lines[i] = f"{indent}{instr}0x{hex_low}{rest}"
            selected = (i, hex_low)
        else:
            # ensure commented
            if comment is None:
                lines[i] = f"{indent}#{instr}0x{hex_low}{rest}"
                toggled_off.append(hex_low)

    if selected is None:
        print(f"[edit_crt0] ERROR: target 0x{target_hex} ({cfg_name}) not found "
              f"in window lines {lo+1}-{hi} around csrs-mhcr at line {csrs_idx+1}",
              file=sys.stderr)
        sys.exit(1)

    path.write_text('\n'.join(lines) + '\n')
    sel_i, sel_h = selected
    msg = f"[edit_crt0] {cfg_name}: enabled 0x{sel_h} (line {sel_i+1})"
    if toggled_off:
        msg += f"; commented: {', '.join('0x'+h for h in toggled_off)}"
    print(msg)

if __name__ == '__main__':
    main()
