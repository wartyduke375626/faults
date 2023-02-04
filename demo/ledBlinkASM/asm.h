#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

#define asmDelay0(count) \
__asm__ volatile ( \
    "mov r23, %A0"     "\n\t" /* Cycles: 1 */ \
    "mov r24, %B0"     "\n\t" /* Cycles: 1 */ \
    "tst r23"          "\n\t" /* Cycles: 1 */ \
    "breq out_loop%="  "\n\t" /* Cycles: 1 */ \
\
    "in_loop%=:"       "\n\t" \
    "nop"              "\n\t" /* Cycles: 1 */ \
    "nop"              "\n\t" /* Cycles: 1 */ \
    "nop"              "\n\t" /* Cycles: 1 */ \
    "dec r23"          "\n\t" /* Cycles: 1 */ \
    "brne in_loop%="   "\n\t" /* Cycles: 2 */ \
\
    "out_loop%=:"      "\n\t" \
    "tst r24"          "\n\t" /* Cycles: 1 */ \
    "breq end%="       "\n\t" /* Cycles: 1 */ \
    "ldi r23, 0xFF"    "\n\t" /* Cycles: 1 */ \
    "dec r24"          "\n\t" /* Cycles: 1 */ \
    "rjmp in_loop%="   "\n\t" /* Cycles: 2 */ \
    "end%=:"           "\n\t" \
    : /* No Outputs */ \
    : "r" (count) \
    : "r23", "r24" \
)

#define asmDelay1(d0, d1, d2, d3) \
__asm__ volatile ( \
    "ldi r19, %[D3]\n\t" \
    "loop3_%=:\n\t" \
    "ldi r18, %[D2]\n\t" \
    "loop2_%=:\n\t" \
    "ldi r17, %[D1]\n\t" \
    "loop1_%=:\n\t" \
    "ldi r16, %[D0]\n\t" \
    "loop0_%=:\n\t" \
    "nop\n\t" \
    "dec r16\n\t" \
    "brne loop0_%=\n\t" \
    "dec r17\n\t" \
    "brne loop1_%=\n\t" \
    "dec r18\n\t" \
    "brne loop2_%=\n\t" \
    "dec r19\n\t" \
    "brne loop3_%=\n\t" \
    : /* No OUT */ \
    : [D0] "i" (d0), [D1] "i" (d1), [D2] "i" (d2), [D3] "i" (d3) \
    : "r16", "r17", "r18", "r19" \
)

#define asmDelay2(delay) \
__asm__ volatile ( \
     "mov r24, %D0\n\t" \
     "loop3_%=:\n\t" \
     "mov r23, %C0\n\t" \
     "loop2_%=:\n\t" \
     "mov r22, %B0\n\t" \
     "loop1_%=:\n\t" \
     "mov r21, %A0\n\t" \
     "loop0_%=:\n\t" \
     "nop\n\t" \
     "dec r21\n\t" \
     "brne loop0_%=\n\t" \
     "dec r22\n\t" \
     "brne loop1_%=\n\t" \
     "dec r23\n\t" \
     "brne loop2_%=\n\t" \
     "dec r24\n\t" \
     "brne loop3_%=\n\t" \
     : /* No OUT */ \
     : "r" (delay) \
     : "r21", "r22", "r23", "r24" \
)