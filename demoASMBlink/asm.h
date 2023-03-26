// sets bit in corresponding port to 1
#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// sets bit in corresponding port to 0
#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// delays for count iterations (8-bit value)
#define asmDelay(count) \
__asm__ volatile( \
    "mov r24, %0"   "\n\t" /* Cycles 1 */ \
    "loop%=:"       "\n\t" \
    "dec r24"       "\n\t" /* Cycles 1 */ \
    "brne loop%="   "\n\t" /* Cycles 2 */ \
    : /* No Outputs */ \
    : "r" (count) \
    : "r24" \
)

// delays for count iterations (16-bit value)
#define asmDelayLong(count) \
__asm__ volatile ( \
    "mov r23, %A0"     "\n\t" /* Cycles: 1 */ \
    "mov r24, %B0"     "\n\t" /* Cycles: 1 */ \
    "tst r23"          "\n\t" /* Cycles: 1 */ \
    "breq out_loop%="  "\n\t" /* Cycles: 1 */ \
\
    "in_loop%=:"       "\n\t" \
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

// recursive macro to generate static count of nop instructions
#define rep0(expr)
#define rep1(expr) expr rep0(expr)
#define rep2(expr) expr rep1(expr)
#define rep3(expr) expr rep2(expr)
#define rep4(expr) expr rep3(expr)
#define rep5(expr) expr rep4(expr)
#define rep6(expr) expr rep5(expr)
#define rep7(expr) expr rep6(expr)
#define rep8(expr) expr rep7(expr)
#define rep9(expr) expr rep8(expr)
#define rep10(expr) expr rep9(expr)
#define nopDelay(count) rep##count(__asm__ volatile("nop");)