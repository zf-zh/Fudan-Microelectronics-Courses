#!/usr/bin/env python3
"""Patch GUARD_START_PC / GUARD_END_PC in tb.v from a freshly-linked elf.

Reads the elf with objdump, locates symbol `guard_start` and `guard_end`,
rewrites the two `define lines in tb.v. Exits with code:
    0  if tb.v was already correct (no rewrite needed)
    1  if tb.v was patched (caller may want to re-run the just-finished sim)
    2  on error (missing symbols, missing files, etc.)
"""

import sys, re, subprocess, pathlib

def find_symbol(objdump_path, elf, sym):
    """Return integer PC of symbol, or None."""
    out = subprocess.check_output([objdump_path, '-t', str(elf)],
                                   stderr=subprocess.DEVNULL).decode()
    # objdump -t lines look like:
    #   0000000000001840 g     F .text  0000000000000018 guard_start
    pat = re.compile(rf'^([0-9a-fA-F]+)\s+\S+\s+F\s+\S+\s+[0-9a-fA-F]+\s+{sym}\b', re.M)
    m = pat.search(out)
    return int(m.group(1), 16) if m else None

def patch_define(text, name, new_pc):
    """Rewrite `define <name>  40'hXXXX` line. Returns (new_text, old_pc_or_None)."""
    pat = re.compile(rf"(`define\s+{name}\s+)40'h([0-9a-fA-F]+)")
    m = pat.search(text)
    if not m:
        return text, None
    old_pc = int(m.group(2), 16)
    new_text = pat.sub(rf"\g<1>40'h{new_pc:x}", text, count=1)
    return new_text, old_pc

def main():
    if len(sys.argv) < 3:
        print(f"usage: {sys.argv[0]} <conv_test.elf> <tb.v> [<objdump>]", file=sys.stderr)
        sys.exit(2)
    elf = pathlib.Path(sys.argv[1])
    tbv = pathlib.Path(sys.argv[2])
    objdump = sys.argv[3] if len(sys.argv) > 3 else 'riscv64-unknown-elf-objdump'

    if not elf.is_file():
        print(f"[patch_pc] ERROR: elf not found: {elf}", file=sys.stderr); sys.exit(2)
    if not tbv.is_file():
        print(f"[patch_pc] ERROR: tb.v not found: {tbv}", file=sys.stderr); sys.exit(2)

    start_pc = find_symbol(objdump, elf, 'guard_start')
    end_pc   = find_symbol(objdump, elf, 'guard_end')
    if start_pc is None or end_pc is None:
        print(f"[patch_pc] ERROR: guard_start/guard_end not in elf symbol table",
              file=sys.stderr)
        print(f"           did -fno-inline -g get applied? did the call sites exist?",
              file=sys.stderr)
        sys.exit(2)

    text = tbv.read_text()
    text, old_start = patch_define(text, 'GUARD_START_PC', start_pc)
    text, old_end   = patch_define(text, 'GUARD_END_PC',   end_pc)

    changed = (old_start != start_pc) or (old_end != end_pc)
    tbv.write_text(text)

    print(f"[patch_pc] guard_start: 0x{old_start:x} -> 0x{start_pc:x}")
    print(f"[patch_pc] guard_end  : 0x{old_end:x} -> 0x{end_pc:x}")
    if changed:
        print(f"[patch_pc] tb.v patched (rerun sim for valid inst_count)")
        sys.exit(1)
    else:
        print(f"[patch_pc] tb.v already correct")
        sys.exit(0)

if __name__ == '__main__':
    main()
