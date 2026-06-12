#!/usr/bin/python3

import sys
import getopt
import os.path
import re

help_msg = "elf2mem.py -i <ifile_path> -o <ofile_path> -s <skip_mode>\n"

hex_file_path = "unknown.hex"

class argv_info:
    def __init__(self, argv):
        try:
            opts, args = getopt.getopt(argv, "hi:o:s", ["ifile=", "ofile=", "smode="])
        except getopt.GetoptError:
            print(help_msg)
            sys.exit()

        # === default member vars value ===
        ifile_path = ""
        ofile_path = "output.mem"
        skip_mode = "n"

        # === get member vars ===
        for opt, arg in opts:
            if opt == '-h':
                print(help_msg)
                sys.exit()
            elif opt in ("-i", "--ifile"):
                ifile_path = arg
                if not os.path.isfile(ifile_path):
                    print("%s is not a file!\n" % ifile_path)
                    sys.exit()
            elif opt in ("-o", "--ofile"):
                ofile_path = arg
            elif opt in ("-s", "--smode"):
                skip_mode = arg

        # === init member vars ===
        self.ifile_path = ifile_path
        self.ofile_path = ofile_path
        self.skip_mode = skip_mode

    def __str__(self):
        return "ifile_path:%s\nofile_path:%s\nskip_mode:%s" % (self.ifile_path, self.ofile_path, self.skip_mode)


def hex2mem(o_argv_info):
    ifile_path = hex_file_path
    ofile_path = o_argv_info.ofile_path
    skip_mode = o_argv_info.skip_mode

    ifile_id = open(ifile_path, 'r')
    ofile_id = open(ofile_path, 'w')

    char_bit_num = 4
    byte_char_num = 2
    record_type_chars = 2
    line_byte_chars = 2
    check_sum_chars = 2
    dat_split_unit = 8  # 8 hex chars = 32 bits = 4 bytes
    get_base_addr = False
    base_addr = 0

    cur_line_idx = 0
    prev_mem_addr = -1

    while True:
        cur_line = ifile_id.readline()
        if not cur_line:
            break

        match_obj = re.match(r'^(S\d)(\w{2})', cur_line)
        if not match_obj:
            print("[ERROR][%s][%d] not match file format:%s\n" % (ifile_path, cur_line_idx + 1, cur_line))
            sys.exit()

        record_type = match_obj.group(1)
        line_bytes = int(("0x" + match_obj.group(2)), 16)

        if record_type == "S0":
            continue
        elif record_type == "S1":
            addr_bits = 16
            end_mark = "S9"
        elif record_type == "S2":
            addr_bits = 24
            end_mark = "S8"
        elif record_type == "S3":
            addr_bits = 32
            end_mark = "S7"
        elif record_type in ("S7", "S8", "S9"):
            if record_type != end_mark:
                print("[ERROR] end of file not match, record_type:%s, end_mark:%s\n" % (record_type, end_mark))
                sys.exit()
            ifile_id.close()
            ofile_id.close()
            break
        else:
            # Skip reserved record types S4, S5, S6
            continue

        addr_chars = int(addr_bits / char_bit_num)

        line_addr_idx = record_type_chars + line_byte_chars
        line_addr_end = line_addr_idx + addr_chars

        data_chars = (line_bytes * byte_char_num) - addr_chars - check_sum_chars
        line_data_idx = line_addr_end
        line_data_end = line_data_idx + data_chars

        line_addr = cur_line[line_addr_idx:line_addr_end]
        line_data = cur_line[line_data_idx:line_data_end]

        line_addr = int(("0x" + line_addr), 16)

        if not get_base_addr:
            base_addr = line_addr
            get_base_addr = True

        # Calculate relative byte address and convert to word index (4 bytes per word)
        rel_byte_addr = line_addr - base_addr
        cur_mem_addr = int(rel_byte_addr / 4)

        if prev_mem_addr == -1:
            prev_mem_addr = cur_mem_addr

        # Fill gaps with zeros if skip_mode is "n"
        if skip_mode == "n":
            mem_addr_incr = cur_mem_addr - prev_mem_addr
            #if mem_addr_incr > 1:
            #    for i in range(mem_addr_incr - 1):
            #        ofile_id.write("00000000\n")
            if mem_addr_incr > 0:                   # was: > 1
                for i in range(mem_addr_incr):      # was: mem_addr_incr - 1
                    ofile_id.write("00000000\n")

        # Extract 32-bit words from the data string
        for i in range(0, data_chars, dat_split_unit):
            chunk = line_data[i:i+dat_split_unit]
            # Pad with zeros if the chunk is incomplete (should not happen with aligned data)
            if len(chunk) < dat_split_unit:
                chunk = chunk.ljust(dat_split_unit, '0')
            ofile_id.write("%s\n" % chunk.lower())
            cur_mem_addr += 1

        prev_mem_addr = cur_mem_addr
        cur_line_idx += 1


def main(argv):
    o_argv_info = argv_info(argv)
    if not o_argv_info.ifile_path:
        print("[ERROR] Input file not specified.\n" + help_msg)
        sys.exit()

    # Convert ELF to Motorola S-record format
    print("[INFO] Converting ELF to SREC format...")
    os.system("./riscv64-unknown-elf-objcopy -O srec %s %s" % (o_argv_info.ifile_path, hex_file_path))
    
    print("[INFO] Parsing SREC and generating %readmemh memory file...")
    hex2mem(o_argv_info)
    
    # Clean up temp file
    os.system("rm -rf %s" % hex_file_path)
    print("[INFO] Successfully generated memory file: %s" % o_argv_info.ofile_path)

if __name__ == "__main__":
    main(sys.argv[1:])
