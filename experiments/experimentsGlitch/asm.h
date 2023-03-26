// sets the bit in corresponding port to 1
#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// sets the bit in corresponding port to 0
#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// infinite loop until the corresponding pin and bit is set to 1 (input)
#define waitForSignal(pin, bit) \
__asm__ volatile ( \
    "loop%=:"       "\n\t" \
    "sbis %0, %1"   "\n\t" /* Cycles: 1 */ \
    "rjmp loop%="   "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (pin), "i" (bit) \
    : /* No Clobbers */ \
)

// delays for count iterations
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