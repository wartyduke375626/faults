#define LED_REG(reg) reg ## B
#define LED_BIT 5


#define powerOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

#define powerOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" /* Cycles: 2 */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

#define asmDelay(delay) \
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
    "breq end%="         "\n\t" /* Cycles: 1 */ \
    "ldi r23, 0xFF"    "\n\t" /* Cycles: 1 */ \
    "dec r24"          "\n\t" /* Cycles: 1 */ \
    "rjmp in_loop%="   "\n\t" /* Cycles: 2 */ \
    "end%=:"           "\n\t" \
    : /* No Outputs */ \
    : "r" (delay) \
    : "r23", "r24" \
)


void setup() {
    LED_REG(DDR) |= (1u << LED_BIT);
}

void loop() {
    uint16_t delay = 0xFFFF;
    powerOn(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    asmDelay(delay);
    powerOff(_SFR_IO_ADDR(LED_REG(PORT)), LED_BIT);
    asmDelay(delay);
}
