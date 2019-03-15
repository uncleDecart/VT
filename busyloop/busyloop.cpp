#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>


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
    long startMs, endMs;
    time_t startS, endS;
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    startS  = spec.tv_sec;
    startMs = round(spec.tv_nsec / 1.0e6);

    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;

    for(int i = 0; i < 10000; i++)
        run_cpuid(&eax, &ebx, &ecx, &edx);


    clock_gettime(CLOCK_REALTIME, &spec);
    endS = spec.tv_sec;
    endMs = round(spec.tv_nsec / 1.0e6);

    printf("Program executed for: %"PRIdMAX".%03ld seconds\n",
           (intmax_t)(endS - startS), endMs - startMs);
}

