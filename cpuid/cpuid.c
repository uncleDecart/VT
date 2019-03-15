// [in] _uEax - аргумент 0 CPUID
// [in] _uEcx - агрумент 1 CPUID
#include <stdio.h>


union Data
{
    unsigned int regs[3];
    char str[12];
};


void run_cpuid(unsigned int *_uEax,
               unsigned int *_uEbx,
               unsigned int *_uEcx,
               unsigned int *_uEdx)
{
        asm volatile("cpuid"
        : "=a"(*_uEax), "=b"(*_uEbx), "=c"(*_uEcx), "=d"(*_uEdx)
        : "0"(*_uEax), "2"(*_uEcx));
}


int main()
{
    unsigned int eax;
    union Data s;
    eax = 0x0;
    printf("before\neax = %d\nebx = %d\necx = %d\nedx = %d\n", eax, s.regs[0], s.regs[1], s.regs[2]);
    run_cpuid(&eax, &s.regs[0], &s.regs[2], &s.regs[1]);
    printf("after\neax = %u\nebx = %u\necx = %u\nedx = %u\n", eax, s.regs[0], s.regs[1], s.regs[2]);
    for (int i = 0; i < 12; i++)
        printf("%c", s.str[i]);
    printf("\n");
}

