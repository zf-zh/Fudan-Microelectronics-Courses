static long int get_cycle()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, cycle\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_instret()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, instret\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Icache_access()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter3\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Icache_miss()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter4\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Dcache_read_access()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter14\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Dcache_read_miss()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter15\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Dcache_write_access()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter16\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}

static long int get_L1_Dcache_write_miss()
{
    long int a;
    a = 0;
    asm volatile (
        "csrr x15, hpmcounter17\n\t"
        "mv %0, x15"
        : "=r"(a)
        :
        : "x15"
    );
    return a;
}