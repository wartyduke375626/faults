/**
* Macros for C Inline Assembly
*/

// set logic 1 on on port using SBI instruction
#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// set logic 0 on on port using SBI instruction
#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// delay procedure
#define asmDelay(count) \
__asm__ volatile( \
    "mov r24, %0"   "\n\t" /* move input to r24 */ \
    "loop%=:"       "\n\t" \
    "dec r24"       "\n\t" \
    "brne loop%="   "\n\t" /* jump if non-zero */ \
    : /* No Outputs */ \
    : "r" (count) \
    : "r24" \
)

// delay procedure with 16-bit input
#define asmDelayLong(count) \
__asm__ volatile ( \
    "mov r23, %A0"     "\n\t" /* move least significant byte (LSB) of input to r23 */ \
    "mov r24, %B0"     "\n\t" /* move most significant byte (MSB) of input to r24 */ \
    "tst r23"          "\n\t" /* if LSB == 0, begin with outer loop */ \
    "breq out_loop%="  "\n\t" \
\
    "in_loop%=:"       "\n\t" /* inner loop going through LSB */ \
    "nop"              "\n\t" \
    "dec r23"          "\n\t" /* decrement LSB */ \
    "brne in_loop%="   "\n\t" \
\
    "out_loop%=:"      "\n\t" /* outer loop going through MSB */ \
    "tst r24"          "\n\t" /* if MSB == 0, end (LSB is guaranteed to be 0 here)*/ \
    "breq end%="       "\n\t" \
    "ldi r23, 0xFF"    "\n\t" /* set LSB to 0xFF */ \
    "dec r24"          "\n\t" /* decrement MSB */ \
    "rjmp in_loop%="   "\n\t" /* jump to inner loop */ \
    "end%=:"           "\n\t" \
    : /* No Outputs */ \
    : "r" (count) \
    : "r23", "r24" \
)

// macros for static delay using NOPs instead of loops (alternative to asmDelay()/asmDelayLong())
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

// count<=10, generates x NOP instructions
#define nopDelay(count) rep##count(__asm__ volatile("nop");)