3200 #pragma once
3201 
3202 // x86 trap and interrupt constants.
3203 
3204 // Processor-defined:
3205 #define T_DIVIDE         0      // divide error
3206 #define T_DEBUG          1      // debug exception
3207 #define T_NMI            2      // non-maskable interrupt
3208 #define T_BRKPT          3      // breakpoint
3209 #define T_OFLOW          4      // overflow
3210 #define T_BOUND          5      // bounds check
3211 #define T_ILLOP          6      // illegal opcode
3212 #define T_DEVICE         7      // device not available
3213 #define T_DBLFLT         8      // double fault
3214 // #define T_COPROC      9      // reserved (not used since 486)
3215 #define T_TSS           10      // invalid task switch segment
3216 #define T_SEGNP         11      // segment not present
3217 #define T_STACK         12      // stack exception
3218 #define T_GPFLT         13      // general protection fault
3219 #define T_PGFLT         14      // page fault
3220 // #define T_RES        15      // reserved
3221 #define T_FPERR         16      // floating point error
3222 #define T_ALIGN         17      // aligment check
3223 #define T_MCHK          18      // machine check
3224 #define T_SIMDERR       19      // SIMD floating point error
3225 
3226 // These are arbitrarily chosen, but with care not to overlap
3227 // processor defined exceptions or interrupt vectors.
3228 #define T_SYSCALL       64      // system call
3229 #define T_DEFAULT      500      // catchall
3230 
3231 #define T_IRQ0          32      // IRQ 0 corresponds to int T_IRQ
3232 
3233 #define IRQ_TIMER        0
3234 #define IRQ_KBD          1
3235 #define IRQ_COM1         4
3236 #define IRQ_IDE         14
3237 #define IRQ_ERROR       19
3238 #define IRQ_SPURIOUS    31
3239 
3240 
3241 
3242 
3243 
3244 
3245 
3246 
3247 
3248 
3249 
