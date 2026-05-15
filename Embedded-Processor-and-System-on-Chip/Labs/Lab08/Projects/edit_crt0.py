#!/usr/bin/env python3

"""Toggle which MHCR-write line is active in crt0.s.
Identifies the 4 candidate lines by their unique hex constants."""

import sys, re, pathlib

HEX = {
    'all_on':  '10f7',   # all prediction on
    'all_off': '0007',   # all prediction off
    'btb_off': '00b7',   # BTB,L0BTB off
    'bpe_off': '10d7',   # BPE off (BHT off)
}
path, choice = sys.argv[1], sys.argv[2]
target = HEX[choice]

cand_re = re.compile(r'^(\s*)#?\s*(li\s+x3\s*,\s*0x([0-9a-fA-F]+))(.*)$')
out = []
for ln in pathlib.Path(path).read_text().splitlines():
    m = cand_re.match(ln)
    if m and m.group(3).lower() in HEX.values():
        indent, instr, hexval, rest = m.group(1), m.group(2), m.group(3).lower(), m.group(4)
        prefix = '' if hexval == target else '#'
        out.append(f'{indent}{prefix}{instr}{rest}')
    else:
        out.append(ln)
pathlib.Path(path).write_text('\n'.join(out) + '\n')
print(f"[edit_crt0] {choice}: enabled 0x{target}, others commented")
