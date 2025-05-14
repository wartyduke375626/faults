/**
* Macros for C Inline Assembly
*/

// set logic 1 on on port using SBI instruction
#define setPortOn(port, bit) \
__asm__ volatile ( \
    "sbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// set logic 0 on on port using SBI instruction
#define setPortOff(port, bit) \
__asm__ volatile ( \
    "cbi %0, %1"    "\n\t" \
    : /* No Outputs */ \
    : "I" (port), "i" (bit) \
    : /* No Clobbers */ \
)

// vulnerable part in Assembly -- the decision whether to grant access is made here
#define asmCheckAccess(result, \
    uidLength, uidByte0, uidByte1, uidByte2, uidByte3, \
    correctUidLength, correctUidByte0, correctUidByte1, correctUidByte2, correctUidByte3) \
__asm__ volatile ( \
    "clr %0"            "\n\t" \
    "eor r0, r0"        "\n\t" \
    "cpi %1, %2"        "\n\t" \
    "breq skip_1"       "\n\t" \
    "inc r0"            "\n\t" \
    "skip_1:"           "\n\t" \
    "cpi %3, %4"        "\n\t" \
    "breq skip_2"       "\n\t" \
    "inc r0"            "\n\t" \
    "skip_2:"           "\n\t" \
    "cpi %5, %6"        "\n\t" \
    "breq skip_3"       "\n\t" \
    "inc r0"            "\n\t" \
    "skip_3:"           "\n\t" \
    "cpi %7, %8"        "\n\t" \
    "breq skip_4"       "\n\t" \
    "inc r0"            "\n\t" \
    "skip_4:"           "\n\t" \
    "cpi %9, %10"       "\n\t" \
    "breq skip_5"       "\n\t" \
    "inc r0"            "\n\t" \
    "skip_5:"           "\n\t" \
    "tst r0"            "\n\t" \
    "brne fail"         "\n\t" \
    "ldi %0, 0x01"      "\n\t" \
    "fail:"             "\n\t" \
    "nop"               "\n\t" \
    : "+d" (result) \
    : "d" (uidLength), "M" (correctUidLength), \
        "d" (uidByte0), "M" (correctUidByte0), \
        "d" (uidByte1), "M" (correctUidByte1), \
        "d" (uidByte2), "M" (correctUidByte2), \
        "d" (uidByte3), "M" (correctUidByte3) \
    : "r0" \
)