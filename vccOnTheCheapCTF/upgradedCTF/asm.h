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