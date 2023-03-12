#ifdef INCREMENT
#define EXPERIMENT_NAME "Increment experiment:"
#define asmExperiment(val) \
__asm__ volatile( \
        "ldi %0, 0x00"     "\n\t" \
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

#ifdef JUMP
#define EXPERIMENT_NAME "Jump experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "rjmp a%="          "\n\t" \
        "ldi %0, 0xFF"      "\n\t" \
        "a%=:"              "\n\t" \
        "nop"               "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 0
#endif

#ifdef LOAD
#define EXPERIMENT_NAME "Load experiment:"
#define asmExperiment(val) \
__asm__ volatile ( \
        "ldi %0, 0x00"      "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "nop"               "\n\t" \
        "ldi %0, 0x55"      "\n\t" \
        : "=r" (val) \
        : /* No inputs */ \
        : /* No clobbers */ \
)
#define EXPECTED_RESULT 85
#endif