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

#define glitch(delay) \
    __asm__ volatile ("cbi 0x0B, 2"); \
    delayMicroseconds(delay); \
    __asm__ volatile ("sbi 0x0B, 2");


#define LED_REG(reg) reg ## B
#define LED_BIT 5
LED_REG(DDR) |= (1u << LED_BIT); // set output
LED_REG(PORT) |= (1u << LED_BIT); // digital write 1
LED_REG(PORT) &= ~(1u << LED_BIT); // digital write 0
