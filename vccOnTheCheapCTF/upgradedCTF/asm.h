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