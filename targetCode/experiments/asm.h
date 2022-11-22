#define powerOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

#define powerOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)