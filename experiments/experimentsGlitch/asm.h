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

// cakanie na prijatie signalu -- nekonecny cyklus, kym dany bit vstupneho pinu nie je nastaveny na 1
#define waitForSignal(pin, bit) \
__asm__ volatile ( \
    "loop%=:"       "\n\t" \
    "sbis %0, %1"   "\n\t" /* preskoci nasledujucu instrukciu ak bit I/O registra je nastaveny na 1 */ \
    "rjmp loop%="   "\n\t" /* skok sposobujuci nekonecny cyklus */ \
    : /* No Outputs */ \
    : "I" (pin), "i" (bit) \
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