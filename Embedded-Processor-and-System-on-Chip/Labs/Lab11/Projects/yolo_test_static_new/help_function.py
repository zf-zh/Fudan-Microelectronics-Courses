import argparse
import os
parser = argparse.ArgumentParser()
parser.add_argument("--qemu", action="store_true", default=False, help="")
parser.add_argument("--d1", action="store_true", default=False, help="")
parser.add_argument("--base", action="store_true", default=False, help="")
parser.add_argument("--gemm", action="store_true", default=False, help="")
parser.add_argument("--opt", action="store_true", default=False, help="")

"""
help to build the yolo
"""

def process_text_replacement(_use_qemu:bool, _case_num:int):
    cur_dir = os.getcwd()
    origin_path = cur_dir
    des_path    = cur_dir +  "/src/convolutional_layer.c"
    exe_name = "yolo_test_riscv"

    if _use_qemu:
        origin_path += "/backup_qemu/"
        exe_name += "_qemu"
    else:
        origin_path += "/backup_d1/"
        exe_name += "_d1"

    if _case_num == 0:
        origin_path += "base/convolutional_layer.c"
        exe_name += "_base"
    elif _case_num == 1:
        origin_path += "gemm/convolutional_layer.c"
        exe_name += "_gemm"
    else:
        origin_path += "cache-opt/convolutional_layer.c"
        exe_name += "_cache-opt"

    print("origin_path = ", origin_path)
    print("des_path = ", des_path)
    cp_cmd = "cp {} {}".format(origin_path, des_path)
    print("cp_cmd : ", cp_cmd)
    os.system(cp_cmd)
    rename_exe = "sed -i \"/EXEC=/c\EXEC={}\" Makefile".format(exe_name)
    print("rename_exe : ", rename_exe)
    os.system(rename_exe)

if __name__ == "__main__":
    args = parser.parse_args()
    use_qemu = args.qemu
    use_d1   = args.d1
    case_num = 0
    print("use_qemu : {}, use_d1 : {} \n".format(use_qemu, use_d1))
    if (use_d1 and use_qemu) or (not use_qemu and not use_d1):
        print("You must specify one platform and only one platform")
        exit(1)
    if args.base:
        case_num = 0;
    elif args.gemm:
        case_num = 1;
    elif args.opt:
        case_num = 2;
    process_text_replacement(use_qemu, case_num)
    os.system("make clean")
    os.system("make")
    
