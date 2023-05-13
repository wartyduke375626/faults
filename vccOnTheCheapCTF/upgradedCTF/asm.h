/**
* Makra pre C Inline Assembly
*/

// nastavenie logickej 1 na danom porte pomocou instrukcie SBI
#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" /* instrukcia SBI */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// nastavenie logickej 0 na danom porte pomocou instrukcie CBI
#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" /* instrukcia CBI */ \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// procedura oneskorenia
#define asmDelay(count) \
__asm__ volatile( \
    "mov r24, %0"   "\n\t" /* inicializacia r24 na vstupnu hodnotu */ \
    "loop%=:"       "\n\t" \
    "dec r24"       "\n\t" /* dekrement */ \
    "brne loop%="   "\n\t" /* podmieneny skok ak bol vysledok nenulovy */ \
    : /* No Outputs */ \
    : "r" (count) \
    : "r24" \
)