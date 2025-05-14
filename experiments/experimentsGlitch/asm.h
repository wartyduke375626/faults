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

// wait for signal -- infinite loop till, input bit in I/O register is 1
#define waitForSignal(pin, bit) \
__asm__ volatile ( \
    "loop%=:"       "\n\t" \
    "sbis %0, %1"   "\n\t" /* skips next instruction if bit is set to 1 */ \
    "rjmp loop%="   "\n\t" /* infinite loop jump */ \
    : /* No Outputs */ \
    : "I" (pin), "i" (bit) \
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