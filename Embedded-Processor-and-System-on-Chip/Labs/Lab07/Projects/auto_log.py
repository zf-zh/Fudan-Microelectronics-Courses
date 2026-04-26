#!/usr/bin/python3

import sys
import re

# Get command line arguments
test_type = sys.argv[1]  # "L1" or "L2"
l1_size = sys.argv[2]
l2_size = sys.argv[3]
n_val = sys.argv[4]
log_file = sys.argv[5]

# Read log file
try:
    with open(log_file, 'r') as f:
        log_text = f.read()
except FileNotFoundError:
    print("Error: File not found: " + log_file)
    sys.exit(1)

# Regex helper function to extract values
def get_val(var_name):
    pattern = r'num_' + var_name + r'\s+is\s+(\d+)'
    match = re.search(pattern, log_text)
    return int(match.group(1)) if match else 0

# Extract base data
cycle = get_val("cycle")
insts = get_val("instret")
cpi = cycle / insts if insts > 0 else 0.0

# Extract L1 data
l1_d_r_acc = get_val("L1_Dcache_read_access")
l1_d_r_miss = get_val("L1_Dcache_read_miss")
l1_d_r_mr = l1_d_r_miss / l1_d_r_acc if l1_d_r_acc > 0 else 0.0

if test_type == "L1":
    l1_d_w_acc = get_val("L1_Dcache_write_access")
    l1_d_w_miss = get_val("L1_Dcache_write_miss")
    l1_d_w_mr = l1_d_w_miss / l1_d_w_acc if l1_d_w_acc > 0 else 0.0
    
    print(f"{l1_size},{l2_size},{n_val},{cycle},{insts},{cpi:.4f},{l1_d_r_acc},{l1_d_r_miss},{l1_d_r_mr},{l1_d_w_acc},{l1_d_w_miss},{l1_d_w_mr}")

else:
    l2_d_r_acc = get_val("L2_Dcache_read_access")
    l2_d_r_miss = get_val("L2_Dcache_read_miss")
    l2_d_r_mr = l2_d_r_miss / l2_d_r_acc if l2_d_r_acc > 0 else 0.0
    
    print(f"{l1_size},{l2_size},{n_val},{cycle},{insts},{cpi:.4f},{l1_d_r_acc},{l1_d_r_miss},{l1_d_r_mr},{l2_d_r_acc},{l2_d_r_miss},{l2_d_r_mr}")

