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

// 'krypticka' cast kodu v asembleri, vystup tejto casti je vzdy konstanta 0 v registri status
// cielom utoku je, aby vystup tejto casti (status) nebol 0
#define asmCheckStatus(status) \
__asm__ volatile ( \ 
    "ldi %0, 0xFF"      "\n\t" \
    "ldi r24, 0x20"     "\n\t" \
    "ldi r25, 0x0F"     "\n\t" \
    "ldi r26, 0xAA"     "\n\t" \
    "mov r3, r26"       "\n\t" \
    "dec %0"            "\n\t" \
    "add %0, r24"       "\n\t" \
    "sub %0, r25"       "\n\t" \
    "or %0, r26"        "\n\t" \
    "add r26, r25"      "\n\t" \
    "add %0, r26"       "\n\t" \
    "clr r26"           "\n\t" \
    "sub r26, r24"      "\n\t" \
    "eor %0, r3"        "\n\t" \
    "inc %0"            "\n\t" \        
    "sub r24, r26"      "\n\t" \
    "add %0, r24"       "\n\t" \
    "and r24, %0"       "\n\t" \
    "or r26, r24"       "\n\t" \
    "add r24, r26"      "\n\t" \
    "and r3, r24"       "\n\t" \
    "eor %0, r3"        "\n\t" \
    "sub %0, r24"       "\n\t" \
    "add r26, r25"      "\n\t" \
    "or r26, r24"       "\n\t" \
    "inc r26"           "\n\t" \
    "sub %0, r26"       "\n\t" \
    "eor r3, r3"        "\n\t" \
    "mov r25, r3"       "\n\t" \
    "ldi r25, 0x2F"     "\n\t" \
    "or %0, r25"        "\n\t" \
    "inc %0"            "\n\t" \
    : "=r" (status) \
    : /* No inputs */ \
    : "r3", "r24", "r25", "r26" \
)