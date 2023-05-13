/**
* Makra pre definovanie experimentov
*/

// experiment 1 -- seria inkrementov (32)
#ifdef INCREMENT
#define EXPERIMENT_NAME "Increment experiment:"
#define asmExperiment(val) \
__asm__ volatile( \
        "ldi %0, 0x00"     "\n\t" /* nacitame konstantu 0 do vystupneho registra */ \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        "inc %0"           "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 32
#endif

// experiment 2 -- priamy skok na adresu
#ifdef JUMP
#define EXPERIMENT_NAME "Jump experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" /* nacitame konstantu 0 do vystupneho registra */ \
        "nop"               "\n\t" /* niekolko nopov (potrebny pocet sa moze lisit v zavislosti od oneskorenia riadiaceho HW) */ \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "rjmp a%="          "\n\t" /* instrukcia, na ktoru cielime */ \
        "ldi %0, 0xFF"      "\n\t" /* ak sa instrukciu podari vynechat -- prepise sa vystupny register na 0xFF */ \
        "a%=:"              "\n\t" \
        "nop"               "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 0
#endif

// experiment 2 -- nacitanie konstanty do registra
#ifdef LOAD
#define EXPERIMENT_NAME "Load experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" /* nacitame konstantu 0 do vystupneho registra */ \
        "nop"               "\n\t" /* niekolko nopov (potrebny pocet sa moze lisit v zavislosti od oneskorenia riadiaceho HW) */ \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "ldi %0, 0x55"      "\n\t" /* instrukcia, na ktoru cielime -- ak sa ju podari vynechat, vystupna hodnota sa neprepise (zostane 0x00) */ \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 85
#endif