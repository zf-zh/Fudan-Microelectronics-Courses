#
# void mac_operation(const long int input_addr, const long int weight_addr, const float* conv_tmp, const int kernel_conv_end);

    .text
    .globl mac_operation
    .type mac_operation,@function


    # a0  #input addr
    # a1  #weight addr
    # a2  #conv_tmp
    # a3  #kernel_conv_end


mac_operation:
    vsetvli x0, x0, e32
    flw f0, (a0)
    vlw.v v0, (a1)
    vfmacc.vf v1, f0, v0  #mac operation
    bnez a3, mac_end
    vsw.v v1, (a2)
    # vssw.v v1, (a4), a5
    vmv.v.x v1, x0

mac_end:


    ret
