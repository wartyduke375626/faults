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

// procedura oneskorenia s 16-bitovym vstupom
#define asmDelayLong(count) \
__asm__ volatile ( \
    "mov r23, %A0"     "\n\t" /* inicializacia r23 na spodny bajt vstupu */ \
    "mov r24, %B0"     "\n\t" /* inicializacia r24 na vrchny bajt vstupu */ \
    "tst r23"          "\n\t" /* ak je spodny bajt 0, zaciname vonkajsim cyklom */ \
    "breq out_loop%="  "\n\t" \
\
    "in_loop%=:"       "\n\t" /* vnutorny cyklus podla spodneho bajtu */ \
    "nop"              "\n\t" \
    "dec r23"          "\n\t" \
    "brne in_loop%="   "\n\t" \
\
    "out_loop%=:"      "\n\t" /* vonkajsi cyklus podla spodneho bajtu */ \
    "tst r24"          "\n\t" /* ak je vrchny bajt 0, koncime (spodny je urcite 0, lebo sa predtym vykonal vnutorny cyklus)*/ \
    "breq end%="       "\n\t" \
    "ldi r23, 0xFF"    "\n\t" /* nastavime spodny bajt na 0xFF */ \
    "dec r24"          "\n\t" /* dekrementujeme vrchny bajt */ \
    "rjmp in_loop%="   "\n\t" /* skok na vnutorny cyklus */ \
    "end%=:"           "\n\t" \
    : /* No Outputs */ \
    : "r" (count) \
    : "r23", "r24" \
)

// makra pre staticku deklaraciu nop instrukcii (alternativa k procedure oneskorenia)
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

// nopDelay(x), x<=10 vyrobi x nop instrukcii
#define nopDelay(count) rep##count(__asm__ volatile("nop");)